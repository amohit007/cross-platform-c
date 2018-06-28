#ifndef CPC_ARRAY_H
#define CPC_ARRAY_H

#include "cpc_base.h"
#include "cpc_bool.h"
#include <stddef.h>

#define CPC_ARRAY_EMPTY ((CPCArray){ 0, NULL })

typedef struct {
	size_t len;
	void *vals;
} CPCArray;

void cpc_array_init(CPCArray *array);
void cpc_array_destroy(CPCArray *array);
void cpc_array_clear(CPCArray *array);
size_t cpc_array_len(const CPCArray *array);
void *cpc_array_get(const CPCArray *array, size_t index, size_t val_size, size_t val_alignment);
CPC_CHECK_RETURN bool cpc_array_append(CPCArray *array, const void *val, size_t val_size, size_t val_alignment);

#endif
