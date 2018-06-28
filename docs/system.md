[Home](https://milesbarr.github.io/cross-platform-c/)

# System

## Usage

Get the CPU count.

```c
unsingned int cpu_count = cpc_cpu_count();
```

Get the page size.

```c
size_t page_size = cpc_page_size();
```

Get an environment variable.

```c
char val[256];
bool ok = cpc_env_get("key", val, sizeof(val));
```

Set an environment variable.

```c
bool ok = cpc_env_set("key", "val");
```

Get the current working directory.

```c
char path[256];
bool ok = cpc_working_dir_get(path, sizeof(path));
```

Set the current working directory.

```c
bool ok = cpc_working_dir_set("example");
```
