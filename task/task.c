/*
#include <register.h>
#include <mcu.h>
#include <task.h>
#include <attributes.h>
#include <dragon_memory.h>
#include <stdint.h>
#include <dragon_types.h>

#define MIE_MTIE     (1 << 7)

#define TASK_MAX_NUM	(64)

// mtime	0x200BFF8	64位计时器当前值（低32位在0x200BFF8，高32位在0x200BFFC）
// mtimecmp	0x2004000	Hart 0的64位计时器比较值（每个Hart间隔8字节，Hart 1在0x2004008等）
// volatile uint64_t* mtime    = (volatile uint64_t*)(0x200BFF8);
volatile uint32_t* mtime_lo = (volatile uint32_t*)0x200BFF8;
volatile uint32_t* mtime_hi = (volatile uint32_t*)0x200BFF8 + 1;
volatile uint64_t* mtimecmp = (volatile uint64_t*)(0x2004000);

static task_handle_t* task_array[TASK_MAX_NUM] = {NULL};
static int task_index = 0;
static int current_task_index = 0;

static task_handle_t *current_task = NULL;

task_handle_t* task_create(const char* const name, uint32_t stack_size, task_func entry, void *args, task_prority_t prority)
{
	task_handle_t *task = NULL;
	if(stack_size == 0)
	{
		return NULL;
	}
	if(task_index >= TASK_MAX_NUM)
	{
		return NULL;
	}
	if((prority > TASK_PRORITY_MAX) || (prority < TASK_PRORITY_MIN))
	{
		return NULL;
	}
	task = memalloc(sizeof(task_handle_t));
	if(task == NULL)
	{
		return NULL;
	}
	task->stack = (uint32_t *)memalloc(stack_size);
	if(task->stack == NULL)
	{
		return NULL;
	}
	task->stack_size = stack_size;
	task->func = entry;
	task->args = args;
	task->prority = prority;
	task->status = TASK_STATUS_READY;

	if(task_index < TASK_MAX_NUM)
	{
		task_array[task_index++] = task;
	}

	if(current_task == NULL)
	{
		current_task = task;
	}

	return task;
}

void task_scheduler(void)
{
	int find_flag = 0;
	task_handle_t *handle = task_array[current_task_index];
	task_handle_t *current_handle = task_array[current_task_index];
	if(task_index <= 1)
	{
		return;	
	}
	for(int i = current_task_index + 1; i < task_index; i++)
	{
		if((task_array[i] != NULL) && (task_array[i]->status == TASK_STATUS_READY) && (task_array[i]->prority >= handle->prority))
		{
			handle = task_array[i];
			current_task_index = i;
			find_flag = 1;
		}
	}
	for(int i = 0; i < current_task_index; i++)
	{
		if((task_array[i] != NULL) && (task_array[i]->status == TASK_STATUS_READY) && (task_array[i]->prority >= handle->prority))
		{
			handle = task_array[i];
			current_task_index = i;
			find_flag = 1;
		}
	}
	if(find_flag == 0)
	{
		return;
	}
	current_handle->status = TASK_STATUS_READY;
	handle->status = TASK_STATUS_RUNNING;
	//汇编切换任务
	//TODO
}

void task_scheduler_start(void)
{
	task_handle_t *handle;
	if((current_task == NULL) && (task_index == 0))
	{
		return;
	}
	//计算优先级最高的就绪态任务
	if((current_task != NULL) && (task_index == 1))
	{
		//布置堆栈
		current_task->status = TASK_STATUS_RUNNING;
		current_task->func(current_task->args);
		return;
	}
	for(int i = 0; i < task_index; i++)
	{
		handle = task_array[i];
		if((handle->status == TASK_STATUS_READY) && (handle->prority > current_task->prority))
		{
			current_task = handle;
			current_task_index = i;
		}
	}
	//
	//执行任务
	if(current_task != NULL)
	{
		//布置堆栈
		//跳转到任务函数
		current_task->status = TASK_STATUS_RUNNING;
		current_task->func(current_task->args);
	}
}


static uint64_t safe_read_mtime(void) {
    uint32_t hi1, hi2, lo;
    do {
        hi1 = *mtime_hi;
        lo = *mtime_lo;
        hi2 = *mtime_hi;
    } while (hi1 != hi2); // 确保高位在读取过程中未变化
    return ((uint64_t)hi1 << 32) | lo;
}

// 32位系统需分两次写入（注意顺序）
__NO_OPTIMIZE static void set_mtimecmp_safe(uint64_t value)
{
    volatile uint32_t* mtimecmp_lo = (uint32_t*)(0x2004000);
    volatile uint32_t* mtimecmp_hi = (uint32_t*)(0x2004000 + 4);
    
    *mtimecmp_hi = 0xFFFFFFFF;          // 禁用比较
    *mtimecmp_lo = (uint32_t)value;     // 写低32位
    *mtimecmp_hi = (uint32_t)(value >> 32); // 写高32位
}

// C语言中断处理逻辑
static void task_timer_handler(void) {
    // 更新下一个中断时间（防溢出写法）
    uint64_t now = safe_read_mtime();
	set_mtimecmp_safe(now + 1000000);
    
    // 触发任务调度
    // schedule();
}

// 中断处理函数声明（使用naked属性手动处理上下文）
__attribute__((naked)) void task_timer_isr() {
    uint64_t now = safe_read_mtime();
	set_mtimecmp_safe(now + 1000000);
    // 汇编入口（自动保存上下文）
    // asm volatile (
    //     "addi sp, sp, -128\n"
    //     "sw ra,  0(sp)\n"
    //     "sw t0,  4(sp)\n"
    //     "sw t1,  8(sp)\n"
    //     // ... 保存所有必要寄存器（根据ABI调整）
    //     "call task_timer_handler\n"   // 调用C处理函数
    //     // 恢复寄存器
    //     "lw ra,  0(sp)\n"
    //     "lw t0,  4(sp)\n"
    //     "lw t1,  8(sp)\n"
    //     // ... 恢复所有寄存器
    //     "addi sp, sp, 128\n"
    //     "mret\n"
    // );
}

// task timer
void task_timer_init(uint64_t interval) {
#if(QEMU_VIR32 == 1)
    // 设置中断向量（直接模式）
    write_csr(mtvec, (uint32_t)task_timer_isr);
    
    // 设置初始定时器比较值
    uint64_t now = safe_read_mtime();
	set_mtimecmp_safe(now + interval);
    
    // 使能机器模式定时器中断
    set_csr(mie, MIE_MTIE);
    
    // 全局中断使能
    set_csr(mstatus, 0x8); // 设置MIE位
#endif
}
*/
