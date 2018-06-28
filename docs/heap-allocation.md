[Home](https://milesbarr.github.io/cross-platform-c/)

# Heap Allocation

## Usage

Allocate memory.

```c
void *ptr = cpc_heap_alloc(size, alignment);
```

Reallocate memory.

```c
ptr = cpc_heap_realloc(ptr, old_size, new_size, alignment);
```

Deallocate memory.

```c
cpc_heap_dealloc(ptr);
```
