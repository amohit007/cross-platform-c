#include "cpc_mutex.h"

#ifdef CPC_PLATFORM_WINDOWS
	CPC_CHECK_RETURN bool cpc_mutex_init(CPCMutex *mutex) {
		CPC_ASSERT(mutex != NULL);
		*mutex = CreateMutex(NULL, FALSE, NULL);
		return *mutex != NULL;
	}
	
	void cpc_mutex_destroy(CPCMutex *mutex) {
		CPC_ASSERT(mutex != NULL);
		CPC_ASSERT(*mutex != NULL);
		BOOL result = CloseHandle(*mutex);
		CPC_ASSERT(result);
	}
	
	void cpc_mutex_lock(CPCMutex *mutex) {
		CPC_ASSERT(mutex != NULL);
		CPC_ASSERT(*mutex != NULL);
		DWORD result = WaitForSingleObject(*mutex, INFINITE);
		CPC_ASSERT(result == WAIT_OBJECT_0);
	}

	CPC_CHECK_RETURN bool cpc_mutex_try_lock(CPCMutex *mutex) {
		CPC_ASSERT(mutex != NULL);
		CPC_ASSERT(*mutex != NULL);
		DWORD result = WaitForSingleObject(*mutex, 0);
		CPC_ASSERT(result == WAIT_OBJECT_0 || result == WAIT_TIMEOUT);
		return result == WAIT_OBJECT_0;
	}

	void cpc_mutex_unlock(CPCMutex *mutex) {
		CPC_ASSERT(mutex != NULL);
		CPC_ASSERT(*mutex != NULL);
		BOOL result = ReleaseMutex(*mutex);
		CPC_ASSERT(result);
	}
#else
	CPC_CHECK_RETURN bool cpc_mutex_init(CPCMutex *mutex) {
		CPC_ASSERT(mutex != NULL);
		return pthread_mutex_init(mutex, NULL) == 0;
	}
	
	void cpc_mutex_destroy(CPCMutex *mutex) {
		CPC_ASSERT(mutex != NULL);
		int result = pthread_mutex_destroy(mutex);
		CPC_ASSERT(result == 0);
	}

	void cpc_mutex_lock(CPCMutex *mutex) {
		CPC_ASSERT(mutex != NULL);
		int result = pthread_mutex_lock(mutex);
		CPC_ASSERT(result == 0);
	}

	CPC_CHECK_RETURN bool cpc_mutex_try_lock(CPCMutex *mutex) {
		CPC_ASSERT(mutex != NULL);
		return pthread_mutex_trylock(mutex) == 0;
	}

	void cpc_mutex_unlock(CPCMutex *mutex) {
		CPC_ASSERT(mutex != NULL);
		int result = pthread_mutex_unlock(mutex);
		CPC_ASSERT(result == 0);
	}
#endif
