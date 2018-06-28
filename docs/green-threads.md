[Home](https://milesbarr.github.io/cross-platform-c/)

# Green Threads

Green threads map any number of threads to any number of concurrent jobs. Threads continually pick up jobs from a queue and run them in parallel.

Jobs can be enqueued by the main thread or by other jobs. Jobs can wait on a condition and will process other jobs in the background while waiting. This library is designed to be simple and lightweight, but also to provide a powerful abstraction.

## Usage

Initialize green threads.

```c
unsigned int worker_count = cpc_cpu_count();
cpc_green_thread_init(worker_count);
```

Spawn a job.

```c
cpc_green_thread_spawn(job, NULL);
```

Yield a job.

```c
cpc_green_thread_yield();
```
