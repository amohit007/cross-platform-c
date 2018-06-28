#include "cpc_math.h"

#include <math.h>

#ifndef CPC_MATH_EXACT
	float cpc_inv_sqrt(float x) {
		CPC_ASSERT(x > 0);
		if (sizeof(float) == 4 && sizeof(int) == 4) {
			union { float f; int i; } u = { x };
			x *= 0.5f;
			u.i = 0x5f3759df - (u.i >> 1);
			return u.f * (1.5f - (x * u.f * u.f));
		} else {
			return 1 / sqrtf(x);
		}
	}

	float cpc_pow(float base, float exp) {
		if (sizeof(float) == 4 && sizeof(int) == 4) {
			union { float f; int i; } u = { base };
			u.i = (int)(exp * (u.i - 1064866805) + 1064866805);
			return u.f;
		} else {
			return powf(base, exp);
		}
	}
#else
	float cpc_inv_sqrt(float x) {
		CPC_ASSERT(x > 0);
		return 1 / sqrtf(x);
	}

	float cpc_pow(float base, float exp) {
		return powf(base, exp);
	}
#endif
