[Home](https://milesbarr.github.io/cross-platform-c/)

# Files

## Usage

Open a file.

```c
CPCFile file;
bool ok = cpc_file_open(&file, "example.txt", flags);
```

Flags:

```c
CPC_FILE_READ
CPC_FILE_WRITE
CPC_FILE_APPEND
CPC_FILE_TRUNCATE
CPC_FILE_RANDOM_ACCESS
```

Read from a file.

```c
char buf[256];
size_t bytes_read = cpc_file_read(&file, buf, sizeof(buf));
```

Write to a file.

```c
char buf[] = "Hello, World!";
size_t bytes_written = cpc_file_write(&file, buf, sizeof(buf));
```

Flush a file.

```c
bool ok = cpc_file_flush(&file);
```

Seek a file offset.

```c
unsigned long long offset = 0;
bool ok = cpc_file_seek(&file, offset);
```

Get the size of a file.

```c
unsigned long long file_size = cpc_file_size(&file);
```

Close a file.

```c
cpc_file_close(&file);
```

Rename a file.

```c
bool ok = cpc_file_rename("old.txt", "new.txt");
```

Copy a file.

```c
bool ok = cpc_file_copy("old.txt", "new.txt");
```

Delete a file.

```c
bool ok = cpc_file_delete("example.txt");
```
