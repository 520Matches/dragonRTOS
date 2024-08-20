#include <uart.h>
#include <dragon_memory.h>


extern uint32_t _app_bss_end;

static void os_init(void)
{
	mem_init();
}

typedef struct
{
	int a;
	char b;
	short c;
	int d;
	long long e;
}test_t;
typedef struct
{
	int a;
	short c;
	long long e;
}test2_t;
typedef struct
{
	int a;
	short c;
	long long e;
	char d;
}test3_t;

void app_main(void)
{
	//set app stack
	asm volatile("la sp, 0x80008000");
	os_init();
	test_t *tt  = (test_t*)memalloc(sizeof(test_t));
	test2_t *tt2 = (test2_t*)memalloc(sizeof(test2_t));
	test3_t *tt3 = (test3_t*)memalloc(sizeof(test3_t));
	tt->a = 1;
	tt2->c = 3;
	tt3->d = 'a';
	//TODO something
	// uint8_t test_data[3] = {0x01, 0x02, 0x03};
	// uart_config_t config;
	// uart_t *uart = create_uart(config);
	// uart->opt.open();
	// uart->opt.write(test_data, 3);
	// asm volatile("ecall");
	while(1);
}
