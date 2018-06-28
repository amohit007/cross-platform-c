#include "cpc_mmap.h"

#include "cpc_base.h"
#include <assert.h>

#ifdef CPC_PLATFORM_WINDOWS
	size_t cpc_mmap_offset_granularity(void) {
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		return info.dwAllocationGranularity;
	}
	
	CPC_CHECK_RETURN size_t cpc_mmap_open(CPCMMap *mmap, const char *filename, unsigned char flags, unsigned long long offset, size_t size) {
		CPC_ASSERT(mmap);
		CPC_ASSERT(filename != NULL);
		CPC_ASSERT(flags & CPC_MMAP_READ || flags & CPC_MMAP_WRITE);
		#ifdef CPC_DEBUG
			CPC_ASSERT(offset % cpc_mmap_offset_granularity() == 0);
		#endif
		CPC_ASSERT(size > 0);

		if (CPC_UNLIKELY(!cpc_file_open(&mmap->file, filename, flags))) {
			return 0;
		}

		mmap->file_mapping = CreateFileMapping(&mmap->file, NULL, flags & CPC_MMAP_READ ? (flags & CPC_MMAP_WRITE ? PAGE_READWRITE : PAGE_READONLY) : PAGE_WRITECOPY, 0, 0, NULL);
		if (CPC_UNLIKELY(!mmap->file_mapping)) {
			cpc_file_close(&mmap->file);
			return 0;
		}

		unsigned long long file_size = cpc_file_size(&mmap->file);
		if (size > file_size - offset) {
			CPC_ASSERT(file_size - offset <= SIZE_MAX);
			size = (size_t)(file_size - offset);

			if (CPC_UNLIKELY(size == 0)) {
				BOOL result = CloseHandle(mmap->file_mapping);
				CPC_ASSERT(result);
				cpc_file_close(&mmap->file);
				return 0;
			}
		}

		mmap->ptr = MapViewOfFile(mmap->file_mapping, flags & CPC_MMAP_WRITE ? FILE_MAP_WRITE : FILE_MAP_READ, (DWORD)(offset >> 32), (DWORD)offset, size);
		if (CPC_UNLIKELY(!mmap->ptr)) {
			BOOL result = CloseHandle(mmap->file_mapping);
			CPC_ASSERT(result);
			cpc_file_close(&mmap->file);
			return 0;
		}

		return size;
	}

	void *cpc_mmap_ptr(const CPCMMap *mmap) {
		CPC_ASSERT(mmap);
		CPC_ASSERT(mmap->file != INVALID_HANDLE_VALUE);
		CPC_ASSERT(mmap->file_mapping);
		CPC_ASSERT(mmap->ptr);
		return mmap->ptr;
	}

	CPC_CHECK_RETURN bool cpc_mmap_flush(CPCMMap *mmap) {
		CPC_ASSERT(mmap);
		CPC_ASSERT(mmap->file != INVALID_HANDLE_VALUE);
		CPC_ASSERT(mmap->file_mapping);
		CPC_ASSERT(mmap->ptr);
		BOOL result = FlushViewOfFile(mmap->ptr, 0);
		CPC_ASSERT(result);
		return true;
	}
	
	void cpc_mmap_close(CPCMMap *mmap) {
		CPC_ASSERT(mmap);
		CPC_ASSERT(mmap->file != INVALID_HANDLE_VALUE);
		CPC_ASSERT(mmap->file_mapping);
		CPC_ASSERT(mmap->ptr);
		BOOL result = CloseHandle(mmap->file_mapping);
		CPC_ASSERT(result);
		cpc_file_close(&mmap->file);
	}
#else
	#include <sys/mman.h>

	size_t cpc_mmap_offset_granularity(void) {
		long page_size = sysconf(_SC_PAGESIZE);
		CPC_ASSERT(page_size <= SIZE_MAX);
		return (page_size > 0) * (size_t)page_size;
	}

	CPC_CHECK_RETURN size_t cpc_mmap_open(CPCMMap *mmap_, const char *filename, CPCMMapFlags flags, unsigned long long offset, size_t size) {
		CPC_ASSERT(mmap_ != NULL);
		CPC_ASSERT(filename != NULL);
		CPC_ASSERT(flags & CPC_MMAP_READ || flags & CPC_MMAP_WRITE);
		CPC_ASSERT(offset % cpc_mmap_offset_granularity() == 0);
		CPC_ASSERT(size > 0);

		if (CPC_UNLIKELY(!cpc_file_open(&mmap_->file, filename, flags))) {
			return 0;
		}

		unsigned long long file_size = cpc_file_size(&mmap->file);
		if (size > file_size - offset) {
			size = file_size - offset;

			if (CPC_UNLIKELY(size == 0)) {
				cpc_file_close(&mmap_->file);
				return 0;
			}
		}

		mmap_->size = size;
		int prot = (flags & CPC_MMAP_READ ? PROT_READ : 0) | (flags & CPC_MMAP_WRITE ? PROT_WRITE : 0);
		mmap_->ptr = mmap(NULL, size, prot, MAP_PRIVATE, mmap_->file, offset);
		if (CPC_UNLIKELY(mmap_->ptr == MAP_FAILED)) {
			cpc_file_close(&mmap_->file);
			return 0;
		}

		return size;
	}

	void *cpc_mmap_ptr(const CPCMMap *mmap) {
		CPC_ASSERT(mmap);
		CPC_ASSERT(mmap->size > 0);
		CPC_ASSERT(mmap->ptr);
		return mmap->ptr;
	}

	CPC_CHECK_RETURN bool cpc_mmap_flush(CPCMMap *mmap) {
		CPC_ASSERT(mmap);
		CPC_ASSERT(mmap->size > 0);
		CPC_ASSERT(mmap->ptr);
		return msync(mmap->ptr, mmap->size, 0) == 0;
	}
	
	void cpc_mmap_close(CPCMMap *mmap) {
		CPC_ASSERT(mmap);
		CPC_ASSERT(mmap->size > 0);
		CPC_ASSERT(mmap->ptr);
		int result = munmap(mmap->ptr, mmap->size);
		CPC_ASSERT(result == 0);
	}
#endif
