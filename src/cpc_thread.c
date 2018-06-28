#include "cpc_thread.h"

#ifdef CPC_PLATFORM_WINDOWS
	CPC_CHECK_RETURN bool cpc_thread_spawn(CPCThread *thread, CPCThreadStartRoutine start_routine, void *arg) {
		CPC_ASSERT(thread != NULL);
		CPC_ASSERT(start_routine);
		*thread = CreateThread(NULL, 0, start_routine, arg, 0, NULL);
		return *thread != NULL;
	}
	
	void cpc_thread_join(CPCThread *thread) {
		CPC_ASSERT(thread != NULL);
		CPC_ASSERT(*thread != NULL);
		
		DWORD result1 = WaitForSingleObject(*thread, INFINITE);
		CPC_ASSERT(result1 == WAIT_OBJECT_0);
		
		BOOL result2 = CloseHandle(*thread);
		CPC_ASSERT(result2);
	}
	
	void cpc_thread_yield(void) {
		SwitchToThread();
	}
	
	void cpc_thread_sleep(unsigned int millis) {
		Sleep(millis);
	}
#else
	#include <sys/time.h>
	#include <sched.h>

	CPC_CHECK_RETURN bool cpc_thread_spawn(CPCThread *thread, CPCThreadStartRoutine start_routine, void *arg) {
		CPC_ASSERT(thread != NULL);
		CPC_ASSERT(start_routine);
		return pthread_create(thread, NULL, start_routine, arg) == 0;
	}

	void cpc_thread_join(CPCThread *thread) {
		CPC_ASSERT(thread != NULL);
		int result = pthread_join(*thread, NULL);
		CPC_ASSERT(result == 0);
	}

	void cpc_thread_yield(void) {
		int result = sched_yield();
		CPC_ASSERT(result == 0);
	}

	void cpc_thread_sleep(unsigned int millis) {
		int result = usleep(millis * 1000);
		CPC_ASSERT(result == 0);
	}
#endif
