#include "cpc_green_thread.h"

#ifdef CPC_DEBUG
	static bool cpc_green_thread_initialized = false;
#endif

#ifndef CPC_GREEN_THREAD_DISABLED
	#include "cpc_thread.h"
	#include "cpc_mutex.h"
	#include "cpc_semaphore.h"

	typedef struct {
		CPCJob job;
		void *restrict arg;
	} CPCJobQueueEntry;

	static volatile CPCJobQueueEntry cpc_job_queue[256];
	static volatile unsigned char cpc_job_queue_front = 0;
	static volatile unsigned char cpc_job_queue_back = 0;
	static CPCMutex cpc_job_queue_mutex;
	static CPCSemaphore cpc_job_count;

	CPC_ALWAYS_INLINE static bool cpc_job_queue_is_full(void) {
		return cpc_job_queue_front == (unsigned char)(cpc_job_queue_back - 1);
	}
	
	void cpc_green_thread_spawn(CPCJob job, void *restrict arg) {
		#ifdef CPC_DEBUG
			CPC_ASSERT(cpc_green_thread_initialized);
		#endif
		CPC_ASSERT(job);
		
		if (CPC_UNLIKELY(cpc_job_queue_is_full() || !cpc_mutex_try_lock(&cpc_job_queue_mutex))) {
			job(arg);
		} else {
			if (CPC_UNLIKELY(cpc_job_queue_is_full())) {
				cpc_mutex_unlock(&cpc_job_queue_mutex);
				job(arg);
			} else {
				cpc_job_queue[cpc_job_queue_front] = (CPCJobQueueEntry){ job, arg };
				cpc_job_queue_front++;
				cpc_mutex_unlock(&cpc_job_queue_mutex);
				cpc_semaphore_inc(&cpc_job_count);
			}
		}
	}

	void cpc_green_thread_yield(void) {
		#ifdef CPC_DEBUG
			CPC_ASSERT(cpc_green_thread_initialized);
		#endif
		
		if (CPC_UNLIKELY(!cpc_semaphore_try_dec(&cpc_job_count))) {
			cpc_thread_yield();
		} else {
			cpc_mutex_lock(&cpc_job_queue_mutex);
			CPCJobQueueEntry entry = cpc_job_queue[cpc_job_queue_back];
			cpc_job_queue_back++;
			cpc_mutex_unlock(&cpc_job_queue_mutex);
			entry.job(entry.arg);
		}
	}

	CPC_NO_RETURN static CPC_THREAD_DEF_START_ROUTINE(cpc_worker, arg) {
		CPC_UNUSED_VAR(arg);

		while (true) {
			cpc_semaphore_dec(&cpc_job_count);
			cpc_mutex_lock(&cpc_job_queue_mutex);
			CPCJobQueueEntry entry = cpc_job_queue[cpc_job_queue_back];
			cpc_job_queue_back++;
			cpc_mutex_unlock(&cpc_job_queue_mutex);
			entry.job(entry.arg);
		}
	}

	CPC_CHECK_RETURN bool cpc_green_thread_init(unsigned int worker_count) {
		#ifdef CPC_DEBUG
			CPC_ASSERT(!cpc_green_thread_initialized);
		#endif
		
		if (CPC_UNLIKELY(!cpc_semaphore_init(&cpc_job_count, 0))) {
			return false;
		}

		if (CPC_UNLIKELY(!cpc_mutex_init(&cpc_job_queue_mutex))) {
			cpc_semaphore_destroy(&cpc_job_count);
			return false;
		}
		
		while (worker_count > 0) {
			CPCThread thread;
			bool ok = cpc_thread_spawn(&thread, cpc_worker, NULL);
			CPC_ASSERT(ok);
			worker_count--;
		}

		#ifdef CPC_DEBUG
			cpc_green_thread_initialized = true;
		#endif
		return true;
	}
#else
	void cpc_green_thread_spawn(void (*job)(void *restrict), void *restrict arg) {
		#ifdef CPC_DEBUG
			CPC_ASSERT(cpc_green_thread_initialized);
		#endif
		CPC_ASSERT(job);
		job(arg);
	}

	void cpc_green_thread_yield(void) {
		#ifdef CPC_DEBUG
			CPC_ASSERT(cpc_green_thread_initialized);
		#endif
	}

	CPC_CHECK_RETURN bool cpc_green_thread_init(unsigned int) {
		#ifdef CPC_DEBUG
			CPC_ASSERT(!cpc_green_thread_initialized);
			cpc_green_thread_initialized = true;
		#endif
		return true;
	}
#endif
