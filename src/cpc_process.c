#include "cpc_process.h"

#ifdef CPC_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#undef WIN32_LEAN_AND_MEAN
	
	CPC_NO_RETURN void cpc_process_exit(unsigned int status) {
		ExitProcess(status);
	}
#else
	#include <stdlib.h>
	#include <limits.h>
	
	CPC_NO_RETURN void cpc_process_exit(unsigned int status) {
		CPC_ASSERT(status <= INT_MAX)
		exit((int)status);
	}
#endif
