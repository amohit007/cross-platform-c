[Home](https://milesbarr.github.io/cross-platform-c/)

# Base Functionality

## Usage

Debug mode:

```c
CPC_DEBUG
```

Platform detection:

```c
CPC_PLATFORM_WINDOWS
CPC_PLATFORM_ANDROID
CPC_PLATFORM_LINUX
CPC_PLATFORM_BSD
CPC_PLATFORM_HP_UX
CPC_PLATFORM_AIX
CPC_PLATFORM_IOS
CPC_PLATFORM_MACOS
CPC_PLATFORM_SOLARIS
CPC_PLATFORM_NAME
```

Compiler detection:

```c
CPC_COMPILER_CLANG
CPC_COMPILER_INTEL
CPC_COMPILER_GCC
CPC_COMPILER_HP
CPC_COMPILER_IBM
CPC_COMPILER_MSVC
CPC_COMPILER_NAME
```

POSIX detection:

```c
CPC_POSIX
```

Conditional hints:

```c
CPC_ASSUME(cond);
CPC_ASSERT(cond);
CPC_STATIC_ASSERT(cond);
if (CPC_LIKELY(cond)) {}
if (CPC_UNLIKELY(cond)) {}
```

Function attributes:

```c
CPC_ALWAYS_INLINE void f();
CPC_NEVER_INLINE void f();
CPC_FLATTEN void f();
CPC_NO_RETURN void f();
CPC_CHECK_RETURN void f();
CPC_PURE void f();
CPC_HOT void f();
CPC_COLD void f();
CPC_DEPRECATED void f();
```

Thread local variables:

```c
CPC_THREAD_LOCAL int x;
```

Alignment:

```c
struct CPC_ALIGN(32) Struct {};
size_t alignment = CPC_ALIGN_OF(int);
bool aligned = CPC_IS_ALIGNED(ptr, alignment);
```

Unused variables:

```c
CPC_UNUSED_VAR(x);
```

Unreachable code:

```c
CPC_UNREACHABLE;
```
