#ifndef CPC_BASE_H
#define CPC_BASE_H

#ifndef NDEBUG
	#define CPC_DEBUG
#endif

#if defined(_WIN32) || defined(_WIN64)
	#define CPC_PLATFORM_WINDOWS
#elif defined(__CYGWIN__) && !defined(_WIN32)
	#define CPC_PLATFORM_WINDOWS
#elif defined(__ANDROID__)
	#define CPC_PLATFORM_ANDROID
#elif defined(__linux__)
	#define CPC_PLATFORM_LINUX
#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
	#include <sys/param.h>
	#ifdef BSD
		#define CPC_PLATFORM_BSD
	#endif
#elif defined(__hpux)
	#define CPC_PLATFORM_HP_UX
#elif defined(_AIX)
	#define CPC_PLATFORM_AIX
#elif defined(__APPLE__) && defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1 || TARGET_OS_IPHONE == 1
		#define CPC_PLATFORM_IOS
	#elif TARGET_OS_MAC == 1
		#define CPC_PLATFORM_MACOS
	#endif
#elif defined(__sun) && defined(__SVR4)
	#define CPC_PLATFORM_SOLARIS
#endif

#if defined(__clang__)
	#define CPC_COMPILER_CLANG
#elif defined(__ICC) || defined(__INTEL_COMPILER)
	#define CPC_COMPILER_INTEL
#elif defined(__GNUC__)
	#define CPC_COMPILER_GCC
#elif defined(__HP_cc) || defined(__HP_aCC)
	#define CPC_COMPILER_HP
#elif defined(__IBMC__) || defined(__IBMCPP__)
	#define CPC_COMPILER_IBM
#elif defined(_MSC_VER)
	#define CPC_COMPILER_MSVC
#endif

#if defined(CPC_PLATFORM_LINUX) || (defined(__APPLE__) && defined(__MACH__))
	#include <unistd.h>

	#ifdef _POSIX_VERSION
		#define CPC_POSIX _POSIX_VERSION
	#endif
#endif

#ifdef CPC_COMPILER_MSVC
	#define restrict __restrict
	#define inline __inline
#endif

#if defined(CPC_COMPILER_GCC) || defined(CPC_COMPILER_CLANG)
	#ifdef CPC_DEBUG
		#define CPC_ALWAYS_INLINE __attribute__ ((always_inline)) inline
		#define CPC_FLATTEN       __attribute__ ((flatten))
	#else
		#define CPC_ALWAYS_INLINE inline
		#define CPC_FLATTEN
	#endif
	#define CPC_NEVER_INLINE __attribute__ ((noinline))
	#define CPC_NO_RETURN    __attribute__ ((noreturn))
	#define CPC_CHECK_RETURN __attribute__ ((warn_unused_result))
	#define CPC_PURE         __attribute__ ((pure))
	#define CPC_HOT          __attribute__ ((hot))
	#define CPC_COLD         __attribute__ ((cold)) CPC_NEVER_INLINE
	#define CPC_DEPRECATED   __attribute__ ((deprecated))
	#define CPC_UNREACHABLE  __builtin_unreachable()
	#define CPC_LIKELY(x)    __builtin_expect(!!(x), 1)
	#define CPC_UNLIKELY(x)  __builtin_expect(!!(x), 0)
	#ifdef CPC_COMPILER_CLANG
		#define CPC_ASSUME(cond) do { if (__has_builtin(__builtin_assume)) __builtin_assume(cond); else if (!(cond)) CPC_UNREACHABLE; } while (0)
	#else
		#define CPC_ASSUME(cond) do { if (__builtin_constant_p(cond) && !(cond)) CPC_UNREACHABLE; } while (0)
	#endif
	#define CPC_ALIGN(alignment) __attribute__ ((aligned(alignment)))
	#define CPC_ALIGN_OF(type) (__alignof__(type))
#elif defined(CPC_COMPILER_MSVC)
	#ifdef CPC_DEBUG
		#define CPC_ALWAYS_INLINE __forceinline
	#else
		#define CPC_ALWAYS_INLINE inline
	#endif
	#define CPC_NEVER_INLINE __declspec(noinline)
	#define CPC_FLATTEN
	#define CPC_NO_RETURN __declspec(noreturn)
	#define CPC_CHECK_RETURN _Check_return_
	#define CPC_PURE __declspec(noalias)
	#define CPC_HOT
	#define CPC_COLD CPC_NEVER_INLINE
	#define CPC_DEPRECATED __declspec(deprecated)
	#define CPC_UNREACHABLE
	#define CPC_LIKELY(x) (x)
	#define CPC_UNLIKELY(x) (x)
	#define CPC_ASSUME(cond) __assume(cond)
	#define CPC_ALIGN(alignment) __declspec(align(alignment))
	#define CPC_ALIGN_OF(type) (__alignof(type))
#else
	#define CPC_ALWAYS_INLINE inline
	#define CPC_NEVER_INLINE
	#define CPC_FLATTEN
	#define CPC_NO_RETURN
	#define CPC_CHECK_RETURN
	#define CPC_PURE
	#define CPC_HOT
	#define CPC_COLD
	#define CPC_DEPRECATED
	#define CPC_UNREACHABLE
	#define CPC_LIKELY(x) (x)
	#define CPC_UNLIKELY(x) (x)
	#define CPC_ASSUME(cond) do {} while (0)
	#define CPC_ALIGN_OF(type) ((char *)(&((struct { char c; type t; } *)0)->t) - (char *)0)
#endif

#define CPC_IS_ALIGNED(ptr, alignment) ((unsigned long long)(ptr) % (alignment) == 0)

#ifdef CPC_COMPILER_MSVC
	#define CPC_THREAD_LOCAL __declspec(thread)
#elif defined(CPC_PLATFORM_WINDOWS)
	#define CPC_THREAD_LOCAL __thread
#else
	#include <threads.h>
	#define CPC_THREAD_LOCAL thread_local
#endif

#define CPC_TO_STRING(str) #str

#ifdef CPC_COMPILER_CLANG
	#define CPC_UNUSED_VAR(var) _Pragma(CPC_TO_STRING(unused(var)))
#else
	#define CPC_UNUSED_VAR(var) do (void)(var); while (0)
#endif

#ifdef CPC_DEBUG
	#include <assert.h>

	#define CPC_ASSERT(cond) assert(cond)
#else
	#define CPC_ASSERT(cond) CPC_ASSUME(cond)
#endif

#define CPC_STATIC_ASSERT(cond) ((void)sizeof(char[1 - 2 * !(cond)]))

#endif
