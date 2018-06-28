[Home](https://milesbarr.github.io/cross-platform-c/)

# Directories

## Usage

Open a directory.

```c
CPCDir dir;
bool ok = cpc_dir_open(&dir, "example");
```

Read from a directory.

```c
const char *name;
bool is_dir;
while (cpc_dir_read(&dir, &name, &is_dir)) {}
```

Close a directory.

```c
cpc_dir_close(&dir);
```

Create a directory.

```c
bool ok = cpc_dir_create("example");
```

Delete a directory.

```c
bool ok = cpc_dir_delete("example");
```
