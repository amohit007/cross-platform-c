#include "cpc_hash.h"

#include <stddef.h>

CPC_PURE unsigned long cpc_djb2(const char *str) {
	CPC_ASSERT(str != NULL);
	unsigned long hash = 5381;
	while (*str != '\0') {
		hash = (hash << 5) + hash + (unsigned long)*str;
		str++;
	}
	return hash;
}

CPC_PURE unsigned long cpc_sdbm(const char *str) {
	CPC_ASSERT(str != NULL);
	unsigned long hash = 0;	
	while (*str != '\0') {
		hash = (hash << 6) + (hash << 16) - hash + (unsigned long)*str;
		str++;
	}
	return hash;
}
