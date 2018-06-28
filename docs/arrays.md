[Home](https://milesbarr.github.io/cross-platform-c/)

# Arrays

## Usage

Initialize an array.

```c
CPCArray array;
cpc_array_init(&array);
```

Append to an array.

```c
int val = 0;
bool ok = cpc_array_append(&array, &val, sizeof(val), CPC_ALIGN_OF(int));
```

Get the length of an array.

```c
size_t len = cpc_array_len(&array);
```

Get an array element.

```c
int *val = cpc_array_get(&array, index, sizeof(int), CPC_ALIGN_OF(int));
```

Clear an array.

```c
cpc_array_clear(&array, sizeof(int), CPC_ALIGN_OF(int));
```

Destroy an array.

```c
cpc_array_destroy(&array, sizeof(int), CPC_ALIGN_OF(int));
```

## Examples

Iterate over an array.

```c
for (size_t i = 0; i < cpc_array_len(&array); i++) {
    int *val = cpc_array_get(&array, i, sizeof(*val), CPC_ALIGN_OF(int));
}
```
