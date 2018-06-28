#ifndef CPC_MEM_H
#define CPC_MEM_H

#include "cpc_base.h"
#include <stddef.h>
#ifdef CPC_COMPILER_MSVC
	#include <xmmintrin.h>
#else
	#include <x86intrin.h>
#endif

#if defined(__AVX512BW__)
	#define CPC_MEM_AVX512
#endif
#if defined(__AVX__) || defined(__AVX2__)
	#define CPC_MEM_AVX256
#endif
#if defined(__SSE__) || defined(__SSE2__) || defined(__SSE3__) || defined(__SSE4_1__) || defined(__SSE4_2__) || defined(__SSSE3__)
	#define CPC_MEM_SSE128
#endif

#ifdef CPC_MEM_AVX512
	#define CPC_MEM_OPTIMAL_ALIGNMENT 64
#elif defined(CPC_MEM_AVX256)
	#define CPC_MEM_OPTIMAL_ALIGNMENT 32
#elif defined(CPC_MEM_SSE128)
	#define CPC_MEM_OPTIMAL_ALIGNMENT 16
#else
	#define CPC_MEM_OPTIMAL_ALIGNMENT 8
#endif

void cpc_mem_copy(void *restrict dst, const void *restrict src, size_t size, size_t alignment);
void cpc_mem_fill(void *dst, size_t size, size_t alignment, char val);
void cpc_mem_zero(void *dst, size_t size, size_t alignment);

#endif
