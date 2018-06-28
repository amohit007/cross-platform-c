#include "cpc_file_input_stream.h"

CPC_CHECK_RETURN bool cpc_file_input_stream_open(CPCFileInputStream *stream, const char *filename) {
	CPC_ASSERT(stream != NULL);
	CPC_ASSERT(filename != NULL);
	
	stream->index = sizeof(stream->buf) - 1;
	#ifndef NDEBUG
		stream->len = sizeof(stream->buf);
	#endif

	if (CPC_LIKELY(cpc_file_open(&stream->file, filename, CPC_FILE_READ))) {
		cpc_file_input_stream_read(stream);
		return true;
	}
	return false;
}

void cpc_file_input_stream_close(CPCFileInputStream *stream) {
	CPC_ASSERT(stream != NULL);
	cpc_file_close(&stream->file);
}

CPC_PURE bool cpc_file_input_stream_is_done(const CPCFileInputStream *stream) {
	CPC_ASSERT(stream != NULL);
	return stream->index >= stream->len;
}

char cpc_file_input_stream_peek(const CPCFileInputStream *stream) {
	CPC_ASSERT(stream != NULL);
	CPC_ASSERT(!cpc_file_input_stream_is_done(stream));
	return stream->buf[stream->index];
}

char cpc_file_input_stream_read(CPCFileInputStream *stream) {
	CPC_ASSERT(stream != NULL);
	CPC_ASSERT(!cpc_file_input_stream_is_done(stream));

	char c = cpc_file_input_stream_peek(stream);
	stream->index++;
	if (CPC_UNLIKELY(stream->index == sizeof(stream->buf))) {
		stream->index = 0;
		
		size_t bytes_read = cpc_file_read(&stream->file, stream->buf, sizeof(stream->buf));
		CPC_ASSERT(bytes_read <= sizeof(stream->buf));
		stream->len = (unsigned char)bytes_read;

		if (CPC_UNLIKELY(stream->len < sizeof(stream->buf))) {
			cpc_file_input_stream_close(stream);
		}
	}
	return c;
}
