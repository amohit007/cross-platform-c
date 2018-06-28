#include "cpc_path.h"

#ifdef CPC_PLATFORM_WINDOWS
	#include <Shlwapi.h>

	bool cpc_path_exists(const char *path) {
		CPC_ASSERT(path != NULL);
		return PathFileExistsA(path);
	}
#else
	#include <sys/stat.h>

	bool cpc_path_exists(const char *path) {
		CPC_ASSERT(path != NULL);
		struct stat sb;
		return stat(path, &sb) == 0;
	}
#endif
