#ifndef CPC_GREEN_THREAD_H
#define CPC_GREEN_THREAD_H

#include "cpc_bool.h"
#include "cpc_base.h"

typedef void (*CPCJob)(void *);

CPC_CHECK_RETURN bool cpc_green_thread_init(unsigned int worker_count);
void cpc_green_thread_spawn(void (*job)(void *), void *restrict arg);
void cpc_green_thread_yield(void);

#endif
