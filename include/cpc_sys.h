#ifndef CPC_SYS_H
#define CPC_SYS_H

#include "cpc_bool.h"
#include "cpc_base.h"
#include <stddef.h>

unsigned int cpc_cpu_count(void);
size_t cpc_page_size(void);
CPC_CHECK_RETURN bool cpc_env_get(const char *restrict key, char *restrict val, size_t val_size);
CPC_CHECK_RETURN bool cpc_env_set(const char *key, const char *val);
CPC_CHECK_RETURN bool cpc_working_dir_get(char *path, size_t path_size);
CPC_CHECK_RETURN bool cpc_working_dir_set(const char *path);

#endif
