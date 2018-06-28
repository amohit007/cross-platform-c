#include "cpc_dir.h"

#include <stddef.h>

#ifdef CPC_PLATFORM_WINDOWS
	#include "cpc_string.h"
	#include "cpc_heap.h"
	#include "cpc_mem.h"

	CPC_CHECK_RETURN bool cpc_dir_open(CPCDir *dir, const char *path) {
		CPC_ASSERT(dir != NULL);
		CPC_ASSERT(path != NULL);

		size_t path_len = cpc_string_len(path);
		char *find_path = cpc_heap_alloc(path_len + 4 + 1, 1);
		if (CPC_UNLIKELY(!find_path)) return false;
		
		cpc_mem_copy(find_path, path, path_len, 1);
		cpc_mem_copy(find_path + path_len, "\\*.*", 5, 1);
		
		dir->find_handle = FindFirstFileA(find_path, &dir->find_data);

		cpc_heap_dealloc(find_path);
		return dir->find_handle != INVALID_HANDLE_VALUE;
	}

	CPC_CHECK_RETURN bool cpc_dir_read(CPCDir *dir, const char **name, bool *is_dir) {
		CPC_ASSERT(dir != NULL);
		CPC_ASSERT(dir->find_handle != INVALID_HANDLE_VALUE);
		CPC_ASSERT(name);
		CPC_ASSERT(is_dir);

		while (dir->first || FindNextFileA(dir->find_handle, &dir->find_data)) {
			dir->first = false;

			const char *filename = dir->find_data.cFileName;
			CPC_ASSERT(*filename);
			if (!(filename[0] == '.' && (filename[1] == '\0' || (filename[1] == '.' && filename[2] == '\0')))) {
				*name = filename;
				*is_dir = !!(dir->find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
				return true;
			}
		}
		return false;
	}

	void cpc_dir_close(CPCDir *dir) {
		CPC_ASSERT(dir != NULL);
		CPC_ASSERT(dir->find_handle != INVALID_HANDLE_VALUE);
		BOOL result = FindClose(dir->find_handle);
		CPC_ASSERT(result);
	}
	
	CPC_CHECK_RETURN bool cpc_dir_create(const char *path) {
		CPC_ASSERT(path != NULL);
		return CreateDirectory(path, NULL);
	}

	CPC_CHECK_RETURN bool cpc_dir_delete(const char *path) {
		CPC_ASSERT(path != NULL);
		return RemoveDirectory(path);
	}
#else
	#include <sys/stat.h>
	#include <unistd.h>

	CPC_CHECK_RETURN bool cpc_dir_open(CPCDir *dir, const char *path) {
		CPC_ASSERT(dir != NULL);
		CPC_ASSERT(path != NULL);
		*dir = opendir(path);
		return *dir != NULL;
	}

	CPC_CHECK_RETURN bool cpc_dir_read(CPCDir *dir, const char **name, bool *is_dir) {
		CPC_ASSERT(dir != NULL);
		CPC_ASSERT(*dir != '\0');
		CPC_ASSERT(name != NULL);
		CPC_ASSERT(is_dir);

		while (true) {
			struct dirent *entry = readdir(*dir);
			if (!entry) break;

			const char *filename = entry->d_name;
			CPC_ASSERT(*filename);
			if (!(filename[0] == '.' && (filename[1] == '\0' || (filename[1] == '.' && filename[2] == '\0')))) {
				*name = filename;
				*is_dir = entry->d_type == DT_DIR;
				return true;
			}
		}
		return false;
	}
	
	void cpc_dir_close(CPCDir *dir) {
		CPC_ASSERT(dir != NULL);
		CPC_ASSERT(*dir != '\0');
		int result = closedir(*dir);
		CPC_ASSERT(result == 0);
	}
	
	CPC_CHECK_RETURN bool cpc_dir_create(const char *path) {
		CPC_ASSERT(path != NULL);
		return mkdir(path, 0) == 0;
	}

	CPC_CHECK_RETURN bool cpc_dir_delete(const char *path) {
		CPC_ASSERT(path != NULL);
		return rmdir(path) == 0;
	}
#endif
