[Home](https://milesbarr.github.io/cross-platform-c/)

# Memory Mapped Files

## Usage

Open a memory mapped file.

```c
CPCMMap mmap;
size_t bytes_mapped = cpc_mmap_open(&mmap, "example.txt", flags, 0, CPC_MMAP_ENTIRE_FILE);
```

Flags:

```c
CPC_MMAP_READ
CPC_MMAP_WRITE
CPC_MMAP_RANDOM_ACCESS
```

Get the pointer to a memory mapped file.

```c
void *ptr = cpc_mmap_ptr(&mmap);
```

Flush changes to a memory mapped file.

```c
bool ok = cpc_mmap_flush(&mmap);
```

Close a memory mapped file.

```c
cpc_mmap_close(&mmap);
```
