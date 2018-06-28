#ifndef CPC_MUTEX_H
#define CPC_MUTEX_H

#include "cpc_bool.h"
#include "cpc_base.h"

#ifdef CPC_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#undef WIN32_LEAN_AND_MEAN

	typedef HANDLE CPCMutex;
#else
	#include <pthread.h>
	
	typedef pthread_mutex_t CPCMutex;
#endif

CPC_CHECK_RETURN bool cpc_mutex_init(CPCMutex *mutex);
void cpc_mutex_destroy(CPCMutex *mutex);
void cpc_mutex_lock(CPCMutex *mutex);
CPC_CHECK_RETURN bool cpc_mutex_try_lock(CPCMutex *mutex);
void cpc_mutex_unlock(CPCMutex *mutex);

#endif
