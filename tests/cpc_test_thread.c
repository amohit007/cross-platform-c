#include "cpc_test_thread.h"

#include "cpc_thread.h"
#include "cpc_base.h"

volatile static int count = 0;

static CPC_THREAD_DEF_START_ROUTINE(start_routine_a, arg) {
	CPC_UNUSED_VAR(arg);

	while (count < 256) {
		if (count % 2 == 0) {
			count = count + 1;
		} else {
			cpc_thread_yield();
		}
	}
	return 0;
}

static CPC_THREAD_DEF_START_ROUTINE(start_routine_b, arg) {
	CPC_UNUSED_VAR(arg);

	while (count < 256) {
		if (count % 2 == 1) {
			count = count + 1;
		} else {
			cpc_thread_yield();
		}
	}
	return 0;
}

void cpc_test_thread(void) {
	puts("start testing threads...");

	CPCThread thread_a;
	CPCThread thread_b;
	bool result = cpc_thread_spawn(&thread_a, start_routine_a, NULL);
	CPC_ASSERT(result);
	result = cpc_thread_spawn(&thread_b, start_routine_b, NULL);
	CPC_ASSERT(result);

	while (count < 256) {
		cpc_thread_yield();
	}

	cpc_thread_join(&thread_a);
	cpc_thread_join(&thread_b);

	puts("done testing threads...");
}
