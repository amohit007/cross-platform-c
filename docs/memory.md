[Home](https://milesbarr.github.io/cross-platform-c/)

# Memory

These functions are similar those in the C standard library, but an alignment parameter allows for more efficient operations.

## Usage

Optimal alignment for memory operations:

```c
CPC_MEM_OPTIMAL_ALIGNMENT
```

Copy memory.

```c
char src[256];
char dst[256];
cpc_mem_copy(dst, src, sizeof(src), CPC_ALIGN_OF(char));
```

Fill memory.

```c
char dst[256];
cpc_mem_fill(dst, sizeof(dst), CPC_ALIGN_OF(char), 255);
```

Zero memory.

```c
char dst[256];
cpc_mem_zero(dst, sizeof(dst), CPC_ALIGN_OF(char));
```
