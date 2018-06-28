#ifndef CPC_FILE_OUTPUT_STREAM_H
#define CPC_FILE_OUTPUT_STREAM_H

#include "cpc_file.h"
#include "cpc_bool.h"
#include "cpc_base.h"

#define CPC_FILE_OUTPUT_STREAM_BUF_SIZE 4096

#define CPC_FILE_OUTPUT_STREAM_APPEND CPC_FILE_APPEND
#define CPC_FILE_OUTPUT_STREAM_TRUNCATE CPC_FILE_TRUNCATE

typedef struct {
	CPCFile file;
	unsigned short len;
	unsigned char buf[CPC_FILE_OUTPUT_STREAM_BUF_SIZE];
} CPCFileOutputStream;

CPC_CHECK_RETURN bool cpc_file_output_stream_open(CPCFileOutputStream *stream, const char *filename, unsigned char flags);
CPC_CHECK_RETURN bool cpc_file_output_stream_write(CPCFileOutputStream *stream, unsigned char c);
void cpc_file_output_stream_flush(CPCFileOutputStream *stream);
CPC_CHECK_RETURN bool cpc_file_output_stream_close(CPCFileOutputStream *stream);

#endif
