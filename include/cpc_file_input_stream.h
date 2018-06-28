#ifndef CPC_FILE_INPUT_STREAM_H
#define CPC_FILE_INPUT_STREAM_H

#include "cpc_file.h"
#include "cpc_bool.h"
#include "cpc_base.h"

#define CPC_FILE_INPUT_STREAM_BUF_SIZE 4096

typedef struct {
	CPCFile file;
	unsigned short index;
	unsigned short len;
	char buf[CPC_FILE_INPUT_STREAM_BUF_SIZE];
} CPCFileInputStream;

CPC_CHECK_RETURN bool cpc_file_input_stream_open(CPCFileInputStream *stream, const char *filename);
void cpc_file_input_stream_close(CPCFileInputStream *stream);
CPC_PURE bool cpc_file_input_stream_is_done(const CPCFileInputStream *stream);
char cpc_file_input_stream_peek(const CPCFileInputStream *stream);
char cpc_file_input_stream_read(CPCFileInputStream *stream);

#endif
