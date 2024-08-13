#ifndef __SYSCALL_H
#define __SYSCALL_H

#include <dragon_types.h>

int (*dragon_write)(uint8_t *data, uint32_t size);
int (*dragon_read)(uint8_t *data, uint32_t size, uint32_t timeout);
int (*dragon_open)(void *dev);
int (*dragon_close)(void *dev);

typedef struct
{
	dragon_write syscall_write;
	dragon_read syscall_read;
	dragon_open syscall_open;
	dragon_close syscall_close;
}syscall_t;

#endif
