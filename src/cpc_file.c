#include "cpc_file.h"

#ifdef CPC_PLATFORM_WINDOWS
	CPC_CHECK_RETURN bool cpc_file_open(CPCFile *file, const char *filename, unsigned char flags) {
		CPC_ASSERT(file != NULL);
		CPC_ASSERT(filename != NULL);
		CPC_ASSERT(!(flags & ~CPC_FILE_READ & ~CPC_FILE_WRITE & ~CPC_FILE_APPEND & ~CPC_FILE_TRUNCATE & ~CPC_FILE_RANDOM_ACCESS));
		CPC_ASSERT(flags & CPC_FILE_READ || flags & CPC_FILE_WRITE);
		CPC_ASSERT(flags & CPC_FILE_WRITE || !(flags & CPC_FILE_APPEND));
		CPC_ASSERT(flags & CPC_FILE_WRITE || !(flags & CPC_FILE_TRUNCATE));
		CPC_ASSERT(!(flags & CPC_FILE_APPEND) || !(flags & CPC_FILE_TRUNCATE));
		*file = CreateFileA(filename,
			(flags & CPC_FILE_READ ? GENERIC_READ : 0) | (flags & CPC_FILE_WRITE ? GENERIC_WRITE : 0),
			0, NULL,
			flags & CPC_FILE_WRITE ? (flags & CPC_FILE_TRUNCATE ? CREATE_ALWAYS : OPEN_ALWAYS) : OPEN_EXISTING,
			flags & CPC_FILE_RANDOM_ACCESS ? FILE_FLAG_RANDOM_ACCESS : FILE_FLAG_SEQUENTIAL_SCAN,
			NULL
		);
		if (CPC_LIKELY(*file != INVALID_HANDLE_VALUE)) {
			if (flags & CPC_FILE_APPEND) {
				DWORD result = SetFilePointer(*file, 0, NULL, FILE_END);
				#ifdef CPC_DEBUG
					CPC_ASSERT(result != INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR);
				#else
					CPC_UNUSED_VAR(result);
				#endif
			}
			return true;
		}
		return false;
	}

	size_t cpc_file_read(CPCFile *file, void *buf, size_t buf_size) {
		CPC_ASSERT(file != NULL);
		CPC_ASSERT(*file != INVALID_HANDLE_VALUE);
		CPC_ASSERT(buf != NULL || buf_size == 0);

		CPC_ASSERT(buf_size <= MAXDWORD);
		DWORD bytes_read;
		ReadFile(*file, buf, (DWORD)buf_size, &bytes_read, NULL);
		CPC_ASSERT((size_t)bytes_read <= buf_size);
		return (size_t)bytes_read;
	}

	size_t cpc_file_write(CPCFile *file, const void *buf, size_t buf_size) {
		CPC_ASSERT(file != NULL);
		CPC_ASSERT(*file != INVALID_HANDLE_VALUE);
		CPC_ASSERT(buf != NULL || buf_size == 0);

		CPC_ASSERT(buf_size <= MAXDWORD);
		DWORD bytes_written;
		WriteFile(*file, buf, (DWORD)buf_size, &bytes_written, NULL);
		CPC_ASSERT((size_t)bytes_written <= buf_size);
		return (size_t)bytes_written;
	}

	CPC_CHECK_RETURN bool cpc_file_flush(CPCFile *file) {
		CPC_ASSERT(file != NULL);
		CPC_ASSERT(*file != INVALID_HANDLE_VALUE);
		return FlushFileBuffers(*file);
	}

	CPC_CHECK_RETURN bool cpc_file_seek(CPCFile *file, unsigned long long offset) {
		CPC_ASSERT(file != NULL);
		CPC_ASSERT(*file != INVALID_HANDLE_VALUE);
		LONG offset_high = (LONG)(offset >> 32);
		return SetFilePointer(*file, (LONG)offset, &offset_high, FILE_BEGIN) != INVALID_SET_FILE_POINTER;
	}

	void cpc_file_close(CPCFile *file) {
		CPC_ASSERT(file != NULL);
		CPC_ASSERT(*file != INVALID_HANDLE_VALUE);
		BOOL result = CloseHandle(*file);
		CPC_ASSERT(result);
	}

	unsigned long long cpc_file_size(CPCFile *file) {
		CPC_ASSERT(file != NULL);
		CPC_ASSERT(*file != INVALID_HANDLE_VALUE);
		
		LARGE_INTEGER file_size;
		BOOL result = GetFileSizeEx(*file, &file_size);
		CPC_ASSERT(result);
		CPC_ASSERT(file_size.QuadPart >= 0);
		return (unsigned long long)file_size.QuadPart;
	}

	CPC_CHECK_RETURN bool cpc_file_rename(const char *src_filename, const char *dst_filename) {
		CPC_ASSERT(src_filename != NULL);
		CPC_ASSERT(dst_filename != NULL);
		return MoveFile(src_filename, dst_filename);
	}

	CPC_CHECK_RETURN bool cpc_file_copy(const char *src_filename, const char *dst_filename) {
		CPC_ASSERT(src_filename != NULL);
		CPC_ASSERT(dst_filename != NULL);
		return CopyFile(src_filename, dst_filename, FALSE);
	}

	CPC_CHECK_RETURN bool cpc_file_delete(const char *filename) {
		CPC_ASSERT(filename != NULL);
		return DeleteFile(filename);
	}
#else
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/stat.h>

	CPC_CHECK_RETURN bool cpc_file_open(CPCFile *file, const char *filename, unsigned char flags) {
		CPC_ASSERT(file != NULL);
		CPC_ASSERT(filename != NULL);
		CPC_ASSERT(flags & CPC_FILE_READ || flags & CPC_FILE_WRITE);
		CPC_ASSERT(flags & CPC_FILE_WRITE || !(flags & CPC_FILE_APPEND));
		CPC_ASSERT(flags & CPC_FILE_WRITE || !(flags & CPC_FILE_TRUNCATE));
		CPC_ASSERT(!(flags & CPC_FILE_APPEND) || !(flags & CPC_FILE_TRUNCATE));
		*file = open(filename,
			(flags & CPC_FILE_READ && flags & CPC_FILE_WRITE ? O_RDWR | O_CREAT : 0)
			| (flags & CPC_FILE_READ && !(flags & CPC_FILE_WRITE) ? O_RDONLY : 0)
			| (!(flags & CPC_FILE_READ) && flags & CPC_FILE_WRITE ? O_WRONLY | O_CREAT : 0)
			| (flags & CPC_FILE_APPEND ? O_APPEND : 0)
			| (flags & CPC_FILE_TRUNCATE ? O_TRUNC : 0));
		return *file != -1;
	}

	size_t cpc_file_read(CPCFile *file, void *buf, size_t buf_size) {
		CPC_ASSERT(file != NULL);
		CPC_ASSERT(*file != -1);
		CPC_ASSERT(buf != NULL || buf_size == 0);
		ssize_t bytes_read = read(*file, buf, buf_size);
		CPC_ASSERT(bytes_read <= buf_size);
		return (bytes_read > 0) * (size_t)bytes_read;
	}

	size_t cpc_file_write(CPCFile *file, const void *buf, size_t buf_size) {
		CPC_ASSERT(file != NULL);
		CPC_ASSERT(*file != -1);
		CPC_ASSERT(buf != NULL || buf_size == 0);
		size_t bytes_written = write(*file, buf, buf_size);
		CPC_ASSERT((size_t)bytes_written <= buf_size);
		return bytes_written;
	}

	void cpc_file_flush(CPCFile *file) {
		CPC_ASSERT(file != NULL);
		CPC_ASSERT(*file != -1);
		return fdatasync(*file) == 0;
	}

	CPC_CHECK_RETURN bool cpc_file_seek(CPCFile *file, unsigned long long offset) {
		CPC_ASSERT(file != NULL);
		CPC_ASSERT(*file != -1);
		return lseek(*file, offset, SEEK_SET) == 0;
	}

	void cpc_file_close(CPCFile *file) {
		CPC_ASSERT(file != NULL);
		CPC_ASSERT(*file != -1);
		int result = close(*file);
		CPC_ASSERT(result == 0);
	}

	unsigned long long cpc_file_size(CPCFile *file) {
		CPC_ASSERT(file != NULL);
		CPC_ASSERT(*file != -1);
		struct stat st;
		int result = fstat(*file, &st);
		return result == 0 ? (unsigned long long)st.st_size : 0;
	}

	CPC_CHECK_RETURN bool cpc_file_rename(const char *src_filename, const char *dst_filename) {
		CPC_ASSERT(src_filename != NULL);
		CPC_ASSERT(dst_filename != NULL);
		return rename(src_filename, dst_filename) == 0;
	}

	#ifdef CPC_PLATFORM_LINUX
		#include <sys/sendfile.h>

		CPC_CHECK_RETURN bool cpc_file_copy(const char *src_filename, const char *dst_filename) {
			CPC_ASSERT(src_filename != NULL);
			CPC_ASSERT(dst_filename != NULL);

			bool result = false;
			CPCFile src_file;
			if (CPC_LIKELY(cpc_file_open(&src_file, src_filename, CPC_FILE_READ))) {
				CPCFile dest_file;
				if (CPC_LIKELY(cpc_file_open(&dest_file, dst_filename, CPC_FILE_WRITE | CPC_FILE_TRUNCATE))) {
					result = true;
					unsigned long long file_size = cpc_file_size(&src_file);
					while (file_size > 0) {
						ssize_t bytes_copied = sendfile(src_file, dest_file, NULL, file_size);
						if (CPC_UNLIKELY(bytes_copied <= 0)) {
							result = false;
							break;
						}
						CPC_ASSERT(bytes_copied <= file_size);
						file_size -= bytes_copied;
					}
					cpc_file_close(&dest_file);
				}
				cpc_file_close(&src_file);
			}
			return result;
		}
	#else
		#define CPC_FILE_COPY_BUF_SIZE 256

		CPC_CHECK_RETURN bool cpc_file_copy(const char *src_filename, const char *dst_filename) {
			CPC_ASSERT(src_filename != NULL);
			CPC_ASSERT(dst_filename != NULL);

			bool result = false;
			CPCFile src_file;
			if (CPC_LIKELY(cpc_file_open(&src_file, src_filename, CPC_FILE_READ))) {
				CPCFile dest_file;
				if (CPC_LIKELY(cpc_file_open(&dest_file, dst_filename, CPC_FILE_WRITE | CPC_FILE_TRUNCATE))) {
					result = true;
					unsigned long long file_size = cpc_file_size(&src_file);
					char buf[CPC_FILE_COPY_BUF_SIZE];
					while (file_size > 0) {
						size_t bytes_read = cpc_file_read(&src_file, buf, sizeof(buf));
						if (CPC_UNLIKELY(bytes_read == 0 || !cpc_file_write(&dest_file, buf, bytes_read))) {
							result = false;
							break;
						}
						CPC_ASSERT(bytes_read <= file_size);
						file_size -= bytes_read;
					}
					cpc_file_close(&dest_file);
				}
				cpc_file_close(&src_file);
			}
			return result;
		}
	#endif

	CPC_CHECK_RETURN bool cpc_file_delete(const char *filename) {
		CPC_ASSERT(filename != NULL);
		return unlink(filename) == 0;
	}
#endif
