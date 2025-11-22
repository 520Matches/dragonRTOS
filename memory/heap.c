#include <stdint.h>
#include <stddef.h>
#include <dragon_config.h>
#include <spinlock.h>
#include <irq.h>
#include <string.h>

// 配置参数
#define MEM_ALIGNMENT       8
#define NUM_SEGREGATED_BINS 8  // 分离链表数量(按2的幂次方)
#define SPLIT_THRESHOLD     (sizeof(block_header_t) + MEM_ALIGNMENT)

static spinlock_t heap_lock = 0;


// 锁控制宏（支持嵌套）
#define LOCK() do { \
    disable_irq(); \
    spin_lock(&heap_lock); \
} while(0)

#define UNLOCK() do { \
    spin_unlock(&heap_lock); \
    enable_irq(); \
} while(0)

static uint8_t heap[] __attribute__((section(".heap")));
// static uint8_t heap[HEAP_SIZE] __attribute__((aligned(MEM_ALIGNMENT)));
static mem_stats_t statistics = {0};
static block_header_t* segregated_bins[NUM_SEGREGATED_BINS] = {0};

// 工具宏
#define ALIGN_SIZE(size) (((size) + (MEM_ALIGNMENT - 1)) & ~(MEM_ALIGNMENT - 1))
#define GET_BIN_INDEX(size) (31 - __builtin_clz((size)/MEM_ALIGNMENT + 1))

/* 声明链接脚本中的符号 */
extern uint8_t _heap_start[];
extern uint8_t _heap_end[];

/* 计算堆大小 */
uint32_t heap_size = 0;

// 初始化堆内存管理系统
void heap_init(void) {
	heap_size = _heap_end - _heap_start;
	if(heap_size > 0)
	{
		block_header_t* init_block = (block_header_t*)heap;
		init_block->size = heap_size - sizeof(block_header_t);
		init_block->is_free = 1;
		init_block->bin_id = GET_BIN_INDEX(init_block->size);
		init_block->next = init_block->prev = NULL;
		
		statistics.heap_size = heap_size;
		statistics.total_free = init_block->size;
		
		// 初始化分离链表
		for(int i=0; i<NUM_SEGREGATED_BINS; i++){
			segregated_bins[i] = NULL;
		}
		segregated_bins[init_block->bin_id] = init_block;
	}
}

// 链表操作宏
#define LIST_INSERT(head, node) do { \
    (node)->next = (head); \
    (node)->prev = NULL; \
    if ((head)) (head)->prev = (node); \
    (head) = (node); \
} while(0)

#define LIST_REMOVE(head, node) do { \
    if ((node)->prev) (node)->prev->next = (node)->next; \
    if ((node)->next) (node)->next->prev = (node)->prev; \
    if ((head) == (node)) (head) = (node)->next; \
} while(0)

void* mm_malloc(size_t size) {
    LOCK();
    if (size == 0 || size > heap_size) { UNLOCK(); return NULL; }

    size_t req_size = ALIGN_SIZE(size);
    int bin_index = GET_BIN_INDEX(req_size);
    
    // 在对应分离链表中查找
    for(; bin_index < NUM_SEGREGATED_BINS; bin_index++) {
        block_header_t* curr = segregated_bins[bin_index];
        while(curr) {
            if(curr->is_free && curr->size >= req_size) {
                LIST_REMOVE(segregated_bins[curr->bin_id], curr);
                
                // 内存分割处理
                if((curr->size - req_size) > SPLIT_THRESHOLD) {
                    block_header_t* new_block = (block_header_t*)((uint8_t*)curr + sizeof(block_header_t) + req_size);
                    new_block->size = curr->size - req_size - sizeof(block_header_t);
                    new_block->is_free = 1;
                    new_block->bin_id = GET_BIN_INDEX(new_block->size);
                    
                    // 插入新块到分离链表
                    LIST_INSERT(segregated_bins[new_block->bin_id], new_block);
                    
                    curr->size = req_size;
                }
                
                curr->is_free = 0;
                curr->bin_id = bin_index;
                statistics.total_allocated += curr->size;
                statistics.total_free -= curr->size + sizeof(block_header_t);
                statistics.alloc_count++;
                
                UNLOCK();
                return (void*)((uint8_t*)curr + sizeof(block_header_t));
            }
            curr = curr->next;
        }
    }
    
    UNLOCK();
    return NULL; // 内存不足
}

void mm_free(void* ptr) {
    if (!ptr) return;
    LOCK();
    
    block_header_t* curr = (block_header_t*)((uint8_t*)ptr - sizeof(block_header_t));
    curr->is_free = 1;
    statistics.total_allocated -= curr->size;
    statistics.total_free += curr->size;
    statistics.free_count++;
    
    // 后向合并
    block_header_t* next_block = (block_header_t*)((uint8_t*)curr + sizeof(block_header_t) + curr->size);
    if((uint8_t*)next_block < heap + heap_size && next_block->is_free) {
        LIST_REMOVE(segregated_bins[next_block->bin_id], next_block);
        curr->size += sizeof(block_header_t) + next_block->size;
    }
    
    // 前向合并
    block_header_t* prev_block = curr->prev;
    if(prev_block && prev_block->is_free) {
        LIST_REMOVE(segregated_bins[prev_block->bin_id], prev_block);
        prev_block->size += sizeof(block_header_t) + curr->size;
        curr = prev_block;
    }
    
    // 更新分离链表
    curr->bin_id = GET_BIN_INDEX(curr->size);
    LIST_INSERT(segregated_bins[curr->bin_id], curr);
    statistics.total_free += sizeof(block_header_t); // 合并产生的空间
    
    UNLOCK();
}

// realloc实现
void* mm_realloc(void* ptr, size_t new_size) {
    if (!ptr) return mm_malloc(new_size);
    if (new_size == 0) { mm_free(ptr); return NULL; }

    block_header_t* curr = (block_header_t*)((uint8_t*)ptr - sizeof(block_header_t));
    size_t aligned_size = ALIGN_SIZE(new_size);
    
    // 尝试就地扩展
    if(aligned_size <= curr->size) return ptr;
    
    // 检查后续块是否空闲
    block_header_t* next = (block_header_t*)((uint8_t*)curr + sizeof(block_header_t) + curr->size);
    if((uint8_t*)next < heap + heap_size && next->is_free && 
      (curr->size + sizeof(block_header_t) + next->size) >= aligned_size) {
        LOCK();
        LIST_REMOVE(segregated_bins[next->bin_id], next);
        curr->size += sizeof(block_header_t) + next->size;
        statistics.total_free -= sizeof(block_header_t);
        UNLOCK();
        return ptr;
    }
    
    // 需要重新分配
    void* new_ptr = mm_malloc(new_size);
    if(new_ptr) {
        memcpy(new_ptr, ptr, curr->size);
        mm_free(ptr);
    }
    return new_ptr;
}

// calloc实现
void* mm_calloc(size_t num, size_t size) {
    size_t total = num * size;
    void* ptr = mm_malloc(total);
    if(ptr) memset(ptr, 0, total);
    return ptr;
}

// 获取内存统计信息
mem_stats_t mm_get_stats(void) {
	return statistics;
}

// 碎片检测函数
float mm_calculate_fragmentation(void) {
    LOCK();
    size_t max_free = 0;
    size_t total_free = 0;
    
    for(int i=0; i<NUM_SEGREGATED_BINS; i++){
        block_header_t* curr = segregated_bins[i];
        while(curr) {
            if(curr->is_free) {
                total_free += curr->size;
                if(curr->size > max_free) max_free = curr->size;
            }
            curr = curr->next;
        }
    }
    
    UNLOCK();
    return (total_free == 0) ? 0.0f : 
        1.0f - (float)max_free / total_free;
}

