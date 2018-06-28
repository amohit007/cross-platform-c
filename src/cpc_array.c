#include "cpc_array.h"

#include "cpc_heap.h"
#include "cpc_mem.h"
#include "cpc_math.h"

void cpc_array_init(CPCArray *array) {
	CPC_ASSERT(array != NULL);
	*array = CPC_ARRAY_EMPTY;
}

void cpc_array_destroy(CPCArray *array) {
	CPC_ASSERT(array != NULL);
	cpc_heap_dealloc(array->vals);
}

void cpc_array_clear(CPCArray *array) {
	CPC_ASSERT(array != NULL);
	cpc_array_destroy(array);
	cpc_array_init(array);
}

size_t cpc_array_len(const CPCArray *array) {
	CPC_ASSERT(array != NULL);
	return array->len;
}

void *cpc_array_get(const CPCArray *array, size_t index, size_t val_size, size_t val_alignment) {
	CPC_ASSERT(array != NULL);
	#ifdef CPC_DEBUG
		size_t len = cpc_array_len(array);
		CPC_ASSERT(0 < len && index < len);
	#endif
	CPC_ASSERT(val_size % val_alignment == 0);
	CPC_ASSERT(CPC_IS_POWER_OF_TWO(val_alignment));

	val_size += val_size % val_alignment;
	return (char *)array->vals + index * val_size;
}

CPC_CHECK_RETURN bool cpc_array_append(CPCArray *array, const void *val, size_t val_size, size_t val_alignment) {
	CPC_ASSERT(array != NULL);
	CPC_ASSERT(val != NULL);
	CPC_ASSERT(CPC_IS_ALIGNED(val, val_alignment));
	CPC_ASSERT(val_size % val_alignment == 0);
	CPC_ASSERT(CPC_IS_POWER_OF_TWO(val_alignment));

	size_t len = cpc_array_len(array);
	if (len == 0 || CPC_IS_POWER_OF_TWO(len)) {
		void *vals = cpc_heap_realloc(array->vals, len, (!len + len * 2) * val_size, val_alignment);
		if (CPC_UNLIKELY(!vals)) return false;
		CPC_ASSERT(CPC_IS_ALIGNED(vals, val_alignment));
		array->vals = vals;
	}
	
	cpc_mem_copy((char *)array->vals + len * val_size, val, val_size, val_alignment);
	array->len++;
	return true;
}
