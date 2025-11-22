#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdint.h>

void dragon_mem_init(void);
void* dragon_malloc(uint32_t size);
void dragon_free(void *p);

#endif
