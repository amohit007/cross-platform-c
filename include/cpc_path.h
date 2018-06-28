#ifndef CPC_PATH_H
#define CPC_PATH_H

#include "cpc_bool.h"
#include "cpc_base.h"

#ifdef CPC_PLATFORM_WINDOWS
	#define CPC_PATH_SEPARATOR '\\'
#else
	#define CPC_PATH_SEPARATOR '/'
#endif

bool cpc_path_exists(const char *path);

#endif
