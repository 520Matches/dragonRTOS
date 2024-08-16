#include <uart.h>
#include <dragon_memory.h>
// #include <stdlib.h>

#define UART_BASE        0x10000000
#define UART_SIZE   4096

/* THR:transmitter holding register */
#define UART_DAT    (UART_BASE+0x00) /* 数据寄存器*/
#define UART_IER    (UART_BASE+0x01) /* 中断使能寄存器*/
#define UART_IIR    (UART_BASE+0x02) /* 中断标识寄存器 (read only)*/
#define UART_FCR    (UART_BASE+0x02) /* FIFO控制寄存器 (write only)*/
#define UART_LCR    (UART_BASE+0x03) /* 线路控制寄存器*/
#define UART_MCR    (UART_BASE+0x04) /* MODEN控制寄存器*/
#define UART_LSR    (UART_BASE+0x05) /* 线路状态寄存器*/
#define UART_MSR    (UART_BASE+0x06) /* MODEN状态寄存器*/

#define UART_DLL (UART_BASE+0x00)  /*预分频寄存器低8位*/
#define UART_DLM (UART_BASE+0x01)  /*预分频寄存器高8位*/

#define UART_LSR_ERROR   0x80  /* 出错 */
#define UART_LSR_EMPTY    0x40  /* 传输FIFO和移位寄存器为空 */
#define UART_LSR_TFE	    0x20  /* 传输FIFO为空 */
#define UART_LSR_BI	    0x10  /* 传输被打断 */
#define UART_LSR_FE	    0x08  /* 接收到没有停止位的帧 */
#define UART_LSR_PE	    0x04  /* 奇偶校验错误位 */
#define UART_LSR_OE	    0x02  /* 数据溢出 */
#define UART_LSR_DR	    0x01  /* FIFO有数据 */

static uart_t uart = {0};

static int uart_write(void *handle, uint8_t *data, uint32_t size)
{
	if((handle == NULL) || (data == NULL) || (size == 0))
	{
		return -E_UART_WRITE;
	}
	// if(data == NULL)
	// {
	// 	return -1;
	// }
	// for(int i = 0; i < size; i++)
	// {
	// 	while((read_byte(UART_LSR) & UART_LSR_EMPTY) == 0);
	// 	write_byte(data[i], UART_DAT);
	// }
	return size;
}

static int uart_read(void *handle, uint8_t *data, uint32_t max_size, uint32_t timeout)
{
	if((handle == NULL) || (data == NULL) || (max_size == 0))
	{
		return -E_UART_READ;
	}
	return 0;

}

// static unsigned int uart16550_clock = 1843200;   // a common base clock
// #define UART_DEFAULT_BAUD  115200

static int uart_open(void *handle)
{
	if(handle == NULL)
	{
		return -E_UART_OPEN;
	}
	// unsigned int divisor = uart16550_clock / (16 * UART_DEFAULT_BAUD);
	//
	// /* disable interrupt */
	// write_byte(0, UART_IER);
	//
	// /* Enable DLAB (set baud rate divisor)*/
	// write_byte(0x80, UART_LCR);
	// write_byte((unsigned char)divisor, UART_DLL);
	// write_byte((unsigned char)(divisor >> 8), UART_DLM);
	//
	// /*8 bits, no parity, one stop bit*/
	// write_byte(0x3, UART_LCR);
	//
	// /* 使能FIFO，清空FIFO，设置14字节threshold*/
	// write_byte(0xc7, UART_FCR);
	// 

	return E_UART_OK;
}

static int uart_close(void *handle)
{
	if(handle == NULL)
	{
		return -E_UART_CLOSE;
	}

	return E_UART_OK;
}

uart_t* create_uart(uart_config_t uart_config)
{
	uart.status = UART_CLOSE;
	uart.opt.write = uart_write;
	uart.opt.read  = uart_read;
	uart.opt.open  = uart_open;
	uart.opt.close = uart_close;
	// memcpy(&(uart.uart_config), &uart_config, sizeof(uart_config_t));
	return &uart;
}
