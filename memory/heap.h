#ifndef __HEAP_H
#define __HEAP_H

#include <stdint.h>

// 内存块头结构（双向链表）
typedef struct block_header_t {
    size_t size;
    struct block_header_t* next;
    struct block_header_t* prev;
    uint8_t is_free : 1;
    uint8_t bin_id  : 3;    // 所属分离链表的ID
} block_header_t;

// 内存统计结构
typedef struct {
    size_t total_allocated;
    size_t total_free;
    size_t alloc_count;
    size_t free_count;
    size_t heap_size;
} mem_stats_t;

void heap_init(void);
void* mm_malloc(size_t size);
void mm_free(void* ptr);
void* mm_realloc(void* ptr, size_t new_size);
void* mm_calloc(size_t num, size_t size);
mem_stats_t mm_get_stats(void);
// 碎片检测函数
float mm_calculate_fragmentation(void);

#endif
