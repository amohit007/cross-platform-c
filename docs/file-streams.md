[Home](https://milesbarr.github.io/cross-platform-c/)

# File Streams

File streams provide buffered input and output for files while reading or writing one byte at a time.

## Usage

### File Input Streams

Open a file input stream.

```c
CPCFileInputStream stream;
bool ok = cpc_file_input_stream_open(&stream, "example.txt");
```

Check if a file input stream is done.

```c
bool done = cpc_file_input_stream_is_done(&stream);
```

Peek at a file input stream.

```c
char c = cpc_file_input_stream_peek(&stream);
```

Read from a file input stream.

```c
char c = cpc_file_input_stream_read(&stream);
```

Close a file input stream.

```c
cpc_file_input_stream_close(&stream);
```

### File Output Streams

Open a file output stream.

```c
CPCFileOutputStream stream;
bool ok = cpc_file_output_stream_open(&stream, "example.txt", flags);
```

Flags:

```c
CPC_FILE_OUTPUT_STREAM_APPEND
CPC_FILE_OUTPUT_STREAM_TRUNCATE
```

Write to a file output stream.

```c
bool ok = cpc_file_output_stream_write(&stream, 255);
```

Flush a file output stream.

```c
bool ok = cpc_file_output_stream_flush(&stream);
```

Close a file output stream.

```c
bool ok = cpc_file_output_stream_close(&stream);
```
