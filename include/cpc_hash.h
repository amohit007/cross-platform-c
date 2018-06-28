#ifndef CPC_HASH_H
#define CPC_HASH_H

#include "cpc_base.h"

CPC_PURE unsigned long cpc_djb2(const char *str);
CPC_PURE unsigned long cpc_sdbm(const char *str);

#endif
