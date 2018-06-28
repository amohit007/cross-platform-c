#ifndef CPC_URL_H
#define CPC_URL_H

#include "cpc_bool.h"
#include "cpc_base.h"
#include <stddef.h>

CPC_CHECK_RETURN bool cpc_url_encode(const char *restrict url, char *restrict encoded_url, size_t encoded_url_size);
CPC_CHECK_RETURN bool cpc_url_decode(const char *restrict encoded_url, char *restrict url, size_t url_size);

#endif
