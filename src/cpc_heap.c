#include "cpc_heap.h"

#include "cpc_math.h"
#include "cpc_mem.h"
#include <malloc.h>

#ifdef CPC_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#undef WIN32_LEAN_AND_MEAN
	
	CPC_CHECK_RETURN void *cpc_heap_alloc(size_t size, size_t alignment) {
		CPC_ASSERT(size % alignment == 0);
		CPC_ASSERT(CPC_IS_POWER_OF_TWO(alignment));
		void *ptr = _aligned_malloc(size, alignment);
		CPC_ASSERT(CPC_IS_ALIGNED(ptr, alignment));
		return ptr;
	}
	
	CPC_CHECK_RETURN void *cpc_heap_realloc(void *ptr, size_t old_size, size_t new_size, size_t alignment) {
		CPC_ASSERT(CPC_IS_ALIGNED(ptr, alignment));
		CPC_ASSERT(ptr || old_size == 0);
		CPC_ASSERT(old_size % alignment == 0);
		CPC_ASSERT(new_size % alignment == 0);
		CPC_ASSERT(CPC_IS_POWER_OF_TWO(alignment));
		if (!ptr) return cpc_heap_alloc(new_size, alignment);
		ptr = _aligned_realloc(ptr, new_size, alignment);
		CPC_ASSERT(CPC_IS_ALIGNED(ptr, alignment));
		return ptr;
	}
	
	void cpc_heap_dealloc(void *ptr) {
		_aligned_free(ptr);
	}
#else
	#define CPC_HEAP_DEFAULT_ALIGNMENT 8

	CPC_CHECK_RETURN void *cpc_heap_alloc(size_t size, size_t alignment) {
		CPC_ASSERT(size % alignment == 0);
		CPC_ASSERT(CPC_IS_POWER_OF_TWO(alignment));
		void *ptr = alignment <= CPC_HEAP_DEFAULT_ALIGNMENT ? malloc(size) : aligned_alloc(alignment, size);
		CPC_ASSERT(CPC_IS_ALIGNED(ptr, alignment));
		return ptr;
	}
	
	CPC_CHECK_RETURN void *cpc_heap_realloc(void *ptr, size_t old_size, size_t new_size, size_t alignment) {
		CPC_ASSERT(CPC_IS_ALIGNED(ptr, alignment));
		CPC_ASSERT(ptr || old_size == 0);
		CPC_ASSERT(old_size % alignment == 0);
		CPC_ASSERT(new_size % alignment == 0);
		CPC_ASSERT(CPC_IS_POWER_OF_TWO(alignment));

		if (alignment <= CPC_HEAP_DEFAULT_ALIGNMENT) {
			ptr = realloc(ptr, new_size);
		} else {
			if (new_size == old_size) return ptr;
			size_t usable = malloc_usable_size(ptr);
			if ((new_size > old_size) & (usable >= new_size)) return ptr;
			void *new_ptr = aligned_alloc(alignment, size);
			if (CPC_LIKELY(new_ptr)) cpc_mem_copy(new_ptr, ptr, old_size, alignment);
			free(ptr);
			ptr = new_ptr;
		}
		CPC_ASSERT(CPC_IS_ALIGNED(ptr, alignment));
		return ptr;
	}
	
	void cpc_heap_dealloc(void *ptr) {
		free(ptr);
	}
#endif
