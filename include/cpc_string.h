#ifndef CPC_STRING_H
#define CPC_STRING_H

#include "cpc_bool.h"
#include "cpc_base.h"
#include <stddef.h>

CPC_PURE size_t cpc_string_len(const char *str);
CPC_PURE int cpc_string_compare(const char *str_a, const char *str_b);
CPC_CHECK_RETURN CPC_PURE bool cpc_string_copy(char *restrict dst, size_t dst_size, const char *restrict src);
bool cpc_string_eq(const char *str_a, const char *str_b);

#endif
