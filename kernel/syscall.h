#ifndef __SYSCALL_H
#define __SYSCALL_H

#include <dragon_types.h>

typedef int (*dragon_write)(void *handle, uint8_t *data, uint32_t size);
typedef int (*dragon_read)(void *handle, uint8_t *data, uint32_t size, uint32_t timeout);
typedef int (*dragon_open)(void *handle);
typedef int (*dragon_close)(void *handle);

typedef struct
{
	dragon_write write;
	dragon_read read;
	dragon_open open;
	dragon_close close;
}syscall_t;

#endif
