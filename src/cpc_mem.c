#include "cpc_mem.h"

#include "cpc_math.h"

// GCC sometimes replaces the loops with memcpy calls
#ifdef CPC_COMPILER_GCC
	#pragma GCC push_options
	#pragma GCC optimize ("no-tree-loop-distribute-patterns")
#endif

void cpc_mem_copy(void *restrict dst, const void *restrict src, size_t size, size_t alignment) {
	CPC_ASSERT(dst != NULL);
	CPC_ASSERT(CPC_IS_ALIGNED(dst, alignment));
	CPC_ASSERT(src != NULL);
	CPC_ASSERT(CPC_IS_ALIGNED(src, alignment));
	CPC_ASSERT(!(src <= dst && (char *)dst < (const char *)src + size));
	CPC_ASSERT(!(dst <= src && (const char *)src < (char *)dst + size));
	CPC_ASSERT(size % alignment == 0);
	CPC_ASSERT(CPC_IS_POWER_OF_TWO(alignment));
	
	#ifdef CPC_MEM_AVX512
		if (alignment >= sizeof(__m512i)) {
			__m512i *restrict d = (__m512i *restrict)dst;
			const __m512i *restrict s = (const __m512i *restrict)src;
			for (; size > 0; size -= sizeof(__m512i)) {
				_mm512_store_si512((void *restrict)dst, _mm512_load_si512((const void *restrict)src));
				d++;
				s++;
				size -= sizeof(__m512i);
			}
		} else
	#endif
	#ifdef CPC_MEM_AVX256
		if (alignment >= sizeof(__m256i)) {
			__m256i *restrict d = (__m256i *restrict)dst;
			const __m256i *restrict s = (const __m256i *restrict)src;
			while (size > 0) {
				_mm256_store_si256(dst, _mm256_load_si256(src));
				d++;
				s++;
				size -= sizeof(__m256i);
			}
		} else
	#endif
	#ifdef CPC_MEM_SSE128
		if (alignment >= sizeof(__m128i)) {
			__m128i *restrict d = (__m128i *restrict)dst;
			const __m128i *restrict s = (const __m128i *restrict)src;
			while (size > 0) {
				_mm_store_si128(dst, _mm_load_si128(src));
				d++;
				s++;
				size -= sizeof(__m128i);
			}
		} else
	#endif
	if (alignment >= sizeof(long long)) {
		long long *restrict d = (long long *restrict)dst;
		const long long *restrict s = (const long long *restrict)src;
		while (size > 0) {
			*d = *s;
			d++;
			s++;
			size -= sizeof(long long);
		}
	} else if (alignment >= sizeof(long)) {
		long *restrict d = (long *restrict)dst;
		const long *restrict s = (const long *restrict)src;
		while (size > 0) {
			*d = *s;
			d++;
			s++;
			size -= sizeof(long);
		}
	} else if (alignment >= sizeof(int)) {
		int *restrict d = (int *restrict)dst;
		const int *restrict s = (const int *restrict)src;
		while (size > 0) {
			*d = *s;
			d++;
			s++;
			size -= sizeof(int);
		}
	} else if (alignment >= sizeof(short)) {
		short *restrict d = (short *restrict)dst;
		const short *restrict s = (const short *restrict)src;
		while (size > 0) {
			*d = *s;
			d++;
			s++;
			size -= sizeof(short);
		}
	} else {
		char *restrict d = (char *restrict)dst;
		const char *restrict s = (const char *restrict)src;
		while (size > 0) {
			*d = *s;
			d++;
			s++;
			size -= sizeof(char);
		}
	}
}

void cpc_mem_fill(void *dst, size_t size, size_t alignment, char val) {
	CPC_ASSERT(dst != NULL);
	CPC_ASSERT(CPC_IS_ALIGNED(dst, alignment));
	CPC_ASSERT(size % alignment == 0);
	CPC_ASSERT(CPC_IS_POWER_OF_TWO(alignment));

	if (alignment < CPC_MEM_OPTIMAL_ALIGNMENT) {
		while ((size > 0) & ((unsigned long long)dst % CPC_MEM_OPTIMAL_ALIGNMENT)) {
			*(char *)dst = val;
			dst = (void *)((char *)dst + 1);
			size--;
		}
	}

	int a = val | (val << 8) | (val << 16) | (val << 24);
	while (size >= CPC_MEM_OPTIMAL_ALIGNMENT) {
		#ifdef CPC_MEM_AVX512
			_mm512_store_si512(dst, _mm512_set1_epi32(a));
		#elif defined(CPC_MEM_AVX256)
			_mm256_store_si256(dst, _mm256_set_epi32(a, a, a, a, a, a, a, a));
		#elif defined(CPC_MEM_SSE128)
			_mm_store_si128(dst, _mm_set_epi32(a, a, a, a));
		#else
			*(long long)dst = 0;
		#endif

		dst = (void *)((char *)dst + CPC_MEM_OPTIMAL_ALIGNMENT);
		size -= CPC_MEM_OPTIMAL_ALIGNMENT;
	}

	if (alignment < CPC_MEM_OPTIMAL_ALIGNMENT) {
		while (size > 0) {
			*(char *)dst = val;
			dst = (void *)((char *)dst + 1);
			size--;
		}
	}

	CPC_ASSERT(size == 0);
}

void cpc_mem_zero(void *dst, size_t size, size_t alignment) {
	CPC_ASSERT(dst != NULL);
	CPC_ASSERT(CPC_IS_ALIGNED(dst, alignment));
	CPC_ASSERT(size % alignment == 0);
	CPC_ASSERT(CPC_IS_POWER_OF_TWO(alignment));

	if (alignment < CPC_MEM_OPTIMAL_ALIGNMENT) {
		while ((size > 0) & ((unsigned long long)dst % CPC_MEM_OPTIMAL_ALIGNMENT)) {
			*(char *)dst = 0;
			dst = (void *)((char *)dst + 1);
			size--;
		}
	}

	while (size >= CPC_MEM_OPTIMAL_ALIGNMENT) {
		#ifdef CPC_MEM_AVX512
			_mm512_store_si512(dst, _mm512_setzero_si512());
		#elif defined(CPC_MEM_AVX256)
			_mm256_store_si256(dst, _mm256_setzero_si256());
		#elif defined(CPC_MEM_SSE128)
			_mm_store_si128(dst, _mm_setzero_si128());
		#else
			*(long long)dst = 0;
		#endif

		dst = (void *)((char *)dst + CPC_MEM_OPTIMAL_ALIGNMENT);
		size -= CPC_MEM_OPTIMAL_ALIGNMENT;
	}

	if (alignment < CPC_MEM_OPTIMAL_ALIGNMENT) {
		while (size > 0) {
			*(char *)dst = 0;
			dst = (void *)((char *)dst + 1);
			size--;
		}
	}

	CPC_ASSERT(size == 0);
}

#ifdef __GNUC__
	#pragma GCC pop_options
#endif
