#ifndef __UART_H
#define __UART_H

#include <dragon_types.h>
#include <syscall.h>

typedef enum
{
	UART_DATA_BITS_7 = 7,
	UART_DATA_BITS_8 = 8,
}uart_data_bits_t;

typedef enum
{
	UART_STOP_BITS_1 = 1,
	UART_STOP_BITS_2 = 2,
}uart_stop_bits_t;

typedef enum
{
	UART_PARITY_NONE = 0,
	UART_PARITY_EVEN = 1,
	UART_PARITY_ODD  = 2,
}uart_parity_t;

typedef struct
{
	uint32_t tx;
	uint32_t rx;
}uart_pins_t;

typedef struct
{
	uint32_t baud;
	uart_data_bits_t data_bits;
	uart_stop_bits_t stop_bits;
	uart_parity_t parity;
	uart_pins_t uart_pins;
}uart_config_t;

typedef struct
{
	syscall_t syscall;
	uart_config_t uart_config;
}uart_t;

uart_t* create_uart(uart_config_t uart_config);

#endif
