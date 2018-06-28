#include "cpc_sys.h"

#ifdef CPC_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#undef WIN32_LEAN_AND_MEAN
	#include <direct.h>

	unsigned int cpc_cpu_count(void) {
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		return info.dwNumberOfProcessors;
	}

	size_t cpc_page_size(void) {
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		return info.dwPageSize;
	}

	CPC_CHECK_RETURN bool cpc_env_get(const char *restrict key, char *restrict val, size_t val_size) {
		CPC_ASSERT(key != NULL);
		CPC_ASSERT(*key != '\0');
		CPC_ASSERT(val != NULL || val_size == 0);
		CPC_ASSERT(!(val <= key && key < val + val_size));
		DWORD val_len = GetEnvironmentVariable(key, val, (DWORD)val_size);
		return (0 < val_len) & (val_len < val_size);
	}

	CPC_CHECK_RETURN bool cpc_env_set(const char *key, const char *val) {
		CPC_ASSERT(key != NULL);
		CPC_ASSERT(*key != '\0');
		CPC_ASSERT(val != NULL);
		return SetEnvironmentVariable(key, val);
	}

	CPC_CHECK_RETURN bool cpc_working_dir_get(char *path, size_t path_size) {
		CPC_ASSERT(path != NULL);
		return !!_getcwd(path, (int)path_size);
	}

	CPC_CHECK_RETURN bool cpc_working_dir_set(const char *path) {
		CPC_ASSERT(path != NULL);
		return _chdir(path) == 0;
	}
#else
	#include <stdlib.h>
	#include <unistd.h>

	#define CPC_CPU_COUNT_FALLBACK 1
	#define CPC_PAGE_SIZE_FALLBACK 4096

	#ifdef __unix__
		#include <unistd.h>
	#endif

	#ifdef _POSIX_VERSION
		#include <unistd.h>
		#include <stdint.h>

		unsigned int cpc_cpu_count(void) {
			long cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
			CPC_ASSERT(cpu_count <= UINT_MAX);
			return cpu_count > 0 ? (unsigned int)cpu_count : CPC_CPU_COUNT_FALLBACK;
		}

		size_t cpc_page_size(void) {
			long page_size = sysconf(_SC_PAGESIZE);
			CPC_ASSERT(page_size <= SIZE_MAX);
			return page_size > 0 ? (size_t)page_size : CPC_PAGE_SIZE_FALLBACK;
		}
	#else
		unsigned int cpc_cpu_count(void) {
			return CPC_CPU_COUNT_FALLBACK;
		}

		size_t cpc_page_size(void) {
			return CPC_PAGE_SIZE_FALLBACK;
		}
	#endif

	CPC_CHECK_RETURN bool cpc_env_get(const char *restrict key, char *restrict val, size_t val_size) {
		CPC_ASSERT(key != NULL);
		CPC_ASSERT(*key != '\0');
		CPC_ASSERT(val != NULL || val_size == 0);
		CPC_ASSERT(!(val <= key && key < val + val_size));
		return cpc_string_copy(val, val_size, getenv(key));
	}

	CPC_CHECK_RETURN bool cpc_env_set(const char *key, const char *val) {
		CPC_ASSERT(key != NULL);
		CPC_ASSERT(*key != '\0');
		CPC_ASSERT(val != NULL);
		return setenv(key, val, 1) == 0;
	}

	CPC_CHECK_RETURN bool cpc_working_dir_get(char *path, size_t path_size) {
		CPC_ASSERT(path != NULL);
		return !!getcwd(path, (int)path_size);
	}

	CPC_CHECK_RETURN bool cpc_working_dir_set(const char *path) {
		CPC_ASSERT(path != NULL);
		return chdir(path) == 0;
	}
#endif
