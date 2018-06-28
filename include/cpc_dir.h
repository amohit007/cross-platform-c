#ifndef CPC_DIR_H
#define CPC_DIR_H

#include "cpc_base.h"
#include "cpc_bool.h"

#ifdef CPC_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#undef WIN32_LEAN_AND_MEAN
	
	typedef struct {
		WIN32_FIND_DATAA find_data;
		HANDLE find_handle;
		bool first;
	} CPCDir;
#else
	#include <dirent.h>

	typedef DIR *CPCDir;
#endif

CPC_CHECK_RETURN bool cpc_dir_open(CPCDir *dir, const char *path);
CPC_CHECK_RETURN bool cpc_dir_read(CPCDir *dir, const char **name, bool *is_dir);
void cpc_dir_close(CPCDir *dir);	
CPC_CHECK_RETURN bool cpc_dir_create(const char *path);
CPC_CHECK_RETURN bool cpc_dir_delete(const char *path);

#endif
