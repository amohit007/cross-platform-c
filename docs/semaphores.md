[Home](https://milesbarr.github.io/cross-platform-c/)

# Semaphores

## Usage

Initialize a semaphore.

```c
CPCSemaphore sem;
bool ok = cpc_semaphore_init(&sem, 0);
```

Increment a semaphore.

```c
cpc_semaphore_inc(&sem);
```

Decrement a semaphore.
   
```c
cpc_semaphore_dec(&sem);
```

Try to decrement a semaphore.

```c
bool dec = cpc_semaphore_try_dec(&sem);
```

Destroy a semaphore.

```c
cpc_semaphore_destroy(&sem);
```
