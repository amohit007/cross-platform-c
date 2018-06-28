#ifndef CPC_HEAP_H
#define CPC_HEAP_H

#include "cpc_base.h"
#include <stddef.h>

CPC_CHECK_RETURN void *cpc_heap_alloc(size_t size, size_t alignment);
CPC_CHECK_RETURN void *cpc_heap_realloc(void *ptr, size_t old_size, size_t new_size, size_t alignment);
void cpc_heap_dealloc(void *ptr);

#endif
