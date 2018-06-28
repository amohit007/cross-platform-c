[Home](https://milesbarr.github.io/cross-platform-c/)

# Pool Allocator

Pool allocators allocate large chunks of memory which are handed out in small fixed-sized allocations.

## Usage

Initialize a pool allocator.

```c
CPCPoolAllocator allocator;
cpc_pool_allocator_init(&allocator, initial_count);
```

Allocate from a pool allocator.

```c
int *x = cpc_pool_allocator_alloc(&allocator, sizeof(int), CPC_ALIGN_OF(int));
```

Deallocate from a pool allocator.

```c
cpc_pool_allocator_dealloc(&allocator, x);
```
