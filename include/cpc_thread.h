#ifndef CPC_THREAD_H
#define CPC_THREAD_H

#include "cpc_bool.h"
#include "cpc_base.h"

#ifdef CPC_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#undef WIN32_LEAN_AND_MEAN
	
	#define CPC_THREAD_DEF_START_ROUTINE(name, param) DWORD __stdcall name(void *param)

	typedef HANDLE CPCThread;
	typedef LPTHREAD_START_ROUTINE CPCThreadStartRoutine;
#else
	#include <pthread.h>
	
	#define CPC_THREAD_DEF_START_ROUTINE(name, param) void *name(void *param)

	typedef pthread_t CPCThread;
	typedef void *(*CPCThreadStartRoutine)(void *);
#endif

CPC_CHECK_RETURN bool cpc_thread_spawn(CPCThread *thread, CPCThreadStartRoutine start_routine, void *arg);
void cpc_thread_join(CPCThread *thread);
void cpc_thread_yield(void);
void cpc_thread_sleep(unsigned int millis);

#endif
