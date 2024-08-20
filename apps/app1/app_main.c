#include <uart.h>

#define APP_HEAP_START	_app_bss_end

extern uint32_t _app_bss_end;



void app_main(void)
{
	//set app stack
	asm volatile("la sp, 0x80008000");
	//TODO something
	// uint8_t test_data[3] = {0x01, 0x02, 0x03};
	// uart_config_t config;
	// uart_t *uart = create_uart(config);
	// uart->opt.open();
	// uart->opt.write(test_data, 3);
	// asm volatile("ecall");
	while(1);
}
