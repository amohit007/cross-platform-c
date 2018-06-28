#ifndef CPC_MATH_H
#define CPC_MATH_H

#include "cpc_base.h"

#define CPC_IS_POWER_OF_TWO(x) ((x) && !((x) & ((x) - 1)))

#define CPC_SET_BIT(x, n) ((x) | (1 << (n)))
#define CPC_UNSET_BIT(x, n) ((x) & ~(1 << (n)))
#define CPC_TOGGLE_BIT(x, n) ((x) ^ (1 << (n)))
#define CPC_IS_BIT_SET(x, n) ((x) & (1 << (n)))

#define CPC_IS_EVEM(x) (((x) & 1) == 0)
#define CPC_IS_ODD(x) (((x) & 1) == 1)

#define CPC_ABS(x) ((1 - (((x) < 0) * 2)) * (x))
#define CPC_IS_SAME_SIGN(x, y) (((x) ^ (y)) >= 0)

CPC_PURE float cpc_inv_sqrt(float x);
CPC_PURE float cpc_pow(float base, float exp);

#endif
