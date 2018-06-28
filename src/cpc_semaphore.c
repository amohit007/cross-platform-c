#include "cpc_semaphore.h"

#ifdef CPC_PLATFORM_WINDOWS
	#include <limits.h>

	CPC_CHECK_RETURN bool cpc_semaphore_init(CPCSemaphore *sem, unsigned int count) {
		CPC_ASSERT(sem != NULL);
		*sem = CreateSemaphore(NULL, count, LONG_MAX, NULL);
		return *sem != NULL;
	}
	
	void cpc_semaphore_destroy(CPCSemaphore *sem) {
		CPC_ASSERT(sem != NULL);
		CPC_ASSERT(*sem != NULL);
		BOOL result = CloseHandle(*sem);
		CPC_ASSERT(result);
	}

	void cpc_semaphore_inc(CPCSemaphore *sem) {
		CPC_ASSERT(sem != NULL);
		CPC_ASSERT(*sem != NULL);
		BOOL result = ReleaseSemaphore(*sem, 1, NULL);
		CPC_ASSERT(result);
	}
	
	void cpc_semaphore_dec(CPCSemaphore *sem) {
		CPC_ASSERT(sem != NULL);
		CPC_ASSERT(*sem != NULL);
		DWORD result = WaitForSingleObject(*sem, INFINITE);
		CPC_ASSERT(result == WAIT_OBJECT_0);
	}
	
	CPC_CHECK_RETURN bool cpc_semaphore_try_dec(CPCSemaphore *sem) {
		CPC_ASSERT(sem != NULL);
		CPC_ASSERT(*sem != NULL);
		DWORD result = WaitForSingleObject(*sem, 0);
		CPC_ASSERT(result == WAIT_OBJECT_0 || result == WAIT_TIMEOUT);
		return result == WAIT_OBJECT_0;
	}
#else
	CPC_CHECK_RETURN bool cpc_semaphore_init(CPCSemaphore *sem, unsigned int count) {
		CPC_ASSERT(sem != NULL);
		return sem_init(sem, 0, count) == 0;
	}

	void cpc_semaphore_destroy(CPCSemaphore *sem) {
		CPC_ASSERT(sem != NULL);
		int result = sem_destroy(sem);
		CPC_ASSERT(result == 0);
	}

	void cpc_semaphore_inc(CPCSemaphore *sem) {
		CPC_ASSERT(sem != NULL);
		int result = sem_post(sem);
		CPC_ASSERT(result == 0);
	}

	void cpc_semaphore_dec(CPCSemaphore *sem) {
		CPC_ASSERT(sem != NULL);
		int result = sem_wait(sem);
		CPC_ASSERT(result == 0);
	}

	CPC_CHECK_RETURN bool cpc_semaphore_try_dec(CPCSemaphore *sem) {
		CPC_ASSERT(sem != NULL);
		return sem_trywait(sem) == 0;
	}
#endif
