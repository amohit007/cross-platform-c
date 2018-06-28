#ifndef CPC_FILE_H
#define CPC_FILE_H

#include "cpc_base.h"
#include "cpc_bool.h"

#define CPC_FILE_READ          (1 << 0)
#define CPC_FILE_WRITE         (1 << 1)
#define CPC_FILE_APPEND        (1 << 2)
#define CPC_FILE_TRUNCATE      (1 << 3)
#define CPC_FILE_RANDOM_ACCESS (1 << 4)

#ifdef CPC_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#undef WIN32_LEAN_AND_MEAN
	
	typedef HANDLE CPCFile;
#else
	typedef int CPCFile;
#endif

CPC_CHECK_RETURN bool cpc_file_open(CPCFile *file, const char *filename, unsigned char flags);
size_t cpc_file_read(CPCFile *file, void *buf, size_t buf_size);
size_t cpc_file_write(CPCFile *file, const void *buf, size_t buf_size);
CPC_CHECK_RETURN bool cpc_file_flush(CPCFile *file);
CPC_CHECK_RETURN bool cpc_file_seek(CPCFile *file, unsigned long long offset);
unsigned long long cpc_file_size(CPCFile *file);
void cpc_file_close(CPCFile *file);
CPC_CHECK_RETURN bool cpc_file_delete(const char *filename);
CPC_CHECK_RETURN bool cpc_file_rename(const char *src_filename, const char *dst_filename);
CPC_CHECK_RETURN bool cpc_file_copy(const char *src_filename, const char *dst_filename);

#endif
