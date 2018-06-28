[Home](https://milesbarr.github.io/cross-platform-c/)

# Strings

## Usage

Get the length of a string.

```c
size_t len = cpc_string_len("Hello, World!");
```

Compare two strings.

```c
int cmp = cpc_string_compare("Hello", "World");
```

Check strings for equality.

```c
bool eq = cpc_string_eq("Hello", "World");
```

Copy a string.

```c
char dst[256];
const char *src = "Hello, World!";
bool ok = cpc_string_copy(dst, sizeof(dst), src);
```
