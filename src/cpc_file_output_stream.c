#include "cpc_file_output_stream.h"

#include <stddef.h>

CPC_CHECK_RETURN bool cpc_file_output_stream_open(CPCFileOutputStream *stream, const char *filename, unsigned char flags) {
	CPC_ASSERT(stream != NULL);
	CPC_ASSERT(filename != NULL);
	CPC_ASSERT(!(flags & ~CPC_FILE_OUTPUT_STREAM_APPEND & ~CPC_FILE_OUTPUT_STREAM_TRUNCATE));
	CPC_ASSERT(!(flags & CPC_FILE_OUTPUT_STREAM_APPEND) || !(flags & CPC_FILE_OUTPUT_STREAM_TRUNCATE));
	stream->len = 0;
	return cpc_file_open(&stream->file, filename, flags | CPC_FILE_WRITE);
}

CPC_CHECK_RETURN bool cpc_file_output_stream_write(CPCFileOutputStream *stream, unsigned char c) {
	CPC_ASSERT(stream != NULL);
	CPC_ASSERT(stream->len <= CPC_FILE_OUTPUT_STREAM_BUF_SIZE);
	if (CPC_UNLIKELY(stream->len == CPC_FILE_OUTPUT_STREAM_BUF_SIZE)) cpc_file_output_stream_flush(stream);
	if (CPC_LIKELY(stream->len < CPC_FILE_OUTPUT_STREAM_BUF_SIZE)) {
		stream->buf[stream->len] = c;
		stream->len++;
		return true;
	}
	return false;
}

void cpc_file_output_stream_flush(CPCFileOutputStream *stream) {
	CPC_ASSERT(stream != NULL);
	size_t bytes_written = cpc_file_write(&stream->file, stream->buf, stream->len);
	CPC_ASSERT(bytes_written <= stream->len);
	stream->len -= (unsigned char)bytes_written;
}

CPC_CHECK_RETURN bool cpc_file_output_stream_close(CPCFileOutputStream *stream) {
	CPC_ASSERT(stream != NULL);
	cpc_file_output_stream_flush(stream);
	if (CPC_LIKELY(stream->len == 0)) {
		cpc_file_close(&stream->file);
		return true;
	}
	return false;
}
