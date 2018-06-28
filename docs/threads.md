[Home](https://milesbarr.github.io/cross-platform-c/)

# Threads

## Usage

Define a thread start routine.

```c
CPC_THREAD_DEF_START_ROUTINE(start_routine, arg) { return 0; }
```

Spawn a thread.

```c
CPCThread thread;
bool ok = cpc_thread_spawn(&thread, start_routine, NULL);
```

Join a thread.

```c
cpc_thread_join(&thread);
```

Yield the current thread.

```c
cpc_thread_yield();
```

Sleep the current thread.

```c
cpc_thread_sleep(1000);
```
