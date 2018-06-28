#include "cpc_string.h"

#ifdef CPC_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#undef WIN32_LEAN_AND_MEAN
	#include <strsafe.h>

	CPC_PURE size_t cpc_string_len(const char *str) {
		CPC_ASSERT(str != NULL);
		int len = lstrlenA(str);
		CPC_ASSERT(len >= 0);
		return (size_t)len;
	}

	CPC_PURE int cpc_string_compare(const char *str_a, const char *str_b) {
		CPC_ASSERT(str_a != NULL);
		CPC_ASSERT(str_b != NULL);
		return lstrcmpA(str_a, str_b);
	}

	CPC_CHECK_RETURN CPC_PURE bool cpc_string_copy(char *restrict dst, size_t dst_size, const char *restrict src) {
		CPC_ASSERT(dst != NULL);
		CPC_ASSERT(dst_size > 0);
		CPC_ASSERT(src != NULL);
		CPC_ASSERT(!(dst <= src && src < dst + dst_size));
		HRESULT result = StringCbCopyA(dst, dst_size, src);
		CPC_ASSERT(result == S_OK || result == STRSAFE_E_INSUFFICIENT_BUFFER);
		return result == S_OK;
	}
#else
	#include <string.h>

	CPC_PURE size_t cpc_string_len(const char *str) {
		CPC_ASSERT(str != NULL);
		return strlen(str);
	}

	CPC_PURE int cpc_string_compare(const char *str_a, const char *str_b) {
		CPC_ASSERT(str_a != NULL);
		CPC_ASSERT(str_b != NULL);
		return strcmp(str_a, str_b);
	}

	CPC_CHECK_RETURN CPC_PURE bool cpc_string_copy(char *restrict dst, size_t dst_size, const char *restrict src) {
		CPC_ASSERT(dst != NULL);
		CPC_ASSERT(dst_size > 0);
		CPC_ASSERT(src != NULL);
		CPC_ASSERT(!(dst <= src && src < dst + dst_size));
		return strlcpy(dst, src, dst_size) < dst_size;
	}
#endif

CPC_PURE bool cpc_string_eq(const char *str_a, const char *str_b) {
	CPC_ASSERT(str_a != NULL);
	CPC_ASSERT(str_b != NULL);
	return cpc_string_compare(str_a, str_b) == 0;
}
