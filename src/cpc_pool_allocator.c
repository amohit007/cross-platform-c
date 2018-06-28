#include "cpc_pool_allocator.h"

#include "cpc_heap.h"

void cpc_pool_allocator_init(CPCPoolAllocator *allocator, size_t initial_count) {
	*allocator = CPC_POOL_ALLOCATOR_EMPTY(initial_count);
}

CPC_CHECK_RETURN void *cpc_pool_allocator_alloc(CPCPoolAllocator *allocator, size_t size, size_t alignment) {
	CPC_ASSERT(allocator != NULL);

	if (allocator->free_ptr != NULL) {
		void *ptr = allocator->free_ptr;
		allocator->free_ptr = *(void **)ptr;
		return ptr;
	}

	if (CPC_UNLIKELY(allocator->active_chunk_rem == 0)) {
		void *chunk = cpc_heap_alloc(allocator->next_chunk_count * size, alignment);
		CPC_ASSERT(CPC_IS_ALIGNED(chunk, alignment));
		if (CPC_UNLIKELY(chunk == NULL)) return cpc_heap_alloc(size, alignment);

		allocator->active_chunk_rem = allocator->next_chunk_count;
		allocator->active_chunk = chunk;
		allocator->next_chunk_count *= CPC_POOL_ALLOCATOR_GROWTH_RATE;
	}

	CPC_ASSERT(allocator->active_chunk_rem > 0);
	void *ptr = allocator->active_chunk;
	allocator->active_chunk += size;
	allocator->active_chunk_rem--;
	return ptr;
}

void cpc_pool_allocator_dealloc(CPCPoolAllocator *allocator, void *ptr) {
	CPC_ASSERT(allocator != NULL);

	*(void **)ptr = allocator->free_ptr;
	allocator->free_ptr = ptr;
}
