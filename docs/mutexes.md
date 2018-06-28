[Home](https://milesbarr.github.io/cross-platform-c/)

# Mutexes

## Usage

Initialize a mutex.

```c
CPCMutex mutex;
bool ok = cpc_mutex_init(&mutex);
```

Lock a mutex.

```c
cpc_mutex_lock(&mutex);
```

Try to lock a mutex.

```c
bool locked = cpc_mutex_try_lock(&mutex);
```

Unlock a mutex.

```c
cpc_mutex_unlock(&mutex);
```

Destroy a mutex.

```c
cpc_mutex_destroy(&mutex);
```

## Examples

Protect a count variable with a mutex.

```c
volatile int count = 0;
CPCMutex mutex;

void inc() {
    cpc_mutex_lock(&mutex);
    count++;
    cpc_mutex_unlock(&mutex);
}

int main() {
    bool ok = cpc_mutex_init(&mutex);
}
```
