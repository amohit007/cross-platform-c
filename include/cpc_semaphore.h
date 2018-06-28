#ifndef CPC_SEMAPHORE_H
#define CPC_SEMAPHORE_H

#include "cpc_bool.h"
#include "cpc_base.h"

#ifdef CPC_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#undef WIN32_LEAN_AND_MEAN
	
	typedef HANDLE CPCSemaphore;
#else
	#include <semaphore.h>
	
	typedef sem_t CPCSemaphore;
#endif

CPC_CHECK_RETURN bool cpc_semaphore_init(CPCSemaphore *sem, unsigned int count);
void cpc_semaphore_destroy(CPCSemaphore *sem);
void cpc_semaphore_inc(CPCSemaphore *sem);
void cpc_semaphore_dec(CPCSemaphore *sem);
CPC_CHECK_RETURN bool cpc_semaphore_try_dec(CPCSemaphore *sem);

#endif
