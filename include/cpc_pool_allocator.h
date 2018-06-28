#ifndef CPC_POOL_ALLOCATOR_ALLOCATOR_H
#define CPC_POOL_ALLOCATOR_ALLOCATOR_H

#include "cpc_base.h"
#include <stddef.h>

#define CPC_POOL_ALLOCATOR_GROWTH_RATE 2

typedef struct {
	void *free_ptr;
	size_t next_chunk_count;
	char *active_chunk;
	size_t active_chunk_rem;
} CPCPoolAllocator;

#define CPC_POOL_ALLOCATOR_EMPTY(initial_count) ((CPCPoolAllocator){ NULL, (initial_count), NULL, 0 })

void cpc_pool_allocator_init(CPCPoolAllocator *allocator, size_t initial_count);
CPC_CHECK_RETURN void *cpc_pool_allocator_alloc(CPCPoolAllocator *allocator, size_t size, size_t alignment);
void cpc_pool_allocator_dealloc(CPCPoolAllocator *allocator, void *ptr);

#endif
