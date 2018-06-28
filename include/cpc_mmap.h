#ifndef CPC_MMAP_H
#define CPC_MMAP_H

#include "cpc_file.h"
#include "cpc_bool.h"
#include "cpc_base.h"
#include <stddef.h>
#include <stdint.h>

#define CPC_MMAP_READ          CPC_FILE_READ
#define CPC_MMAP_WRITE         CPC_FILE_WRITE
#define CPC_MMAP_RANDOM_ACCESS CPC_FILE_RANDOM_ACCESS

#define CPC_MMAP_ENTIRE_FILE SIZE_MAX

#ifdef CPC_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#undef WIN32_LEAN_AND_MEAN
	
	typedef struct {
		CPCFile file;
		HANDLE file_mapping;
		void *ptr;
	} CPCMMap;
#else
	#include <sys/mman.h>

	typedef struct {
		CPCFile file;
		size_t size;
		void *ptr;
	} CPCMMap;
#endif

size_t cpc_mmap_offset_granularity(void);
CPC_CHECK_RETURN size_t cpc_mmap_open(CPCMMap *mmap, const char *filename, unsigned char flags, unsigned long long offset, size_t size);
void *cpc_mmap_ptr(const CPCMMap *mmap);
CPC_CHECK_RETURN bool cpc_mmap_flush(CPCMMap *mmap);
void cpc_mmap_close(CPCMMap *mmap);

#endif
