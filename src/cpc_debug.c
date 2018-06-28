#include "cpc_debug.h"

#include "cpc_base.h"

#ifdef CPC_DEBUG
	#ifdef CPC_PLATFORM_WINDOWS
		#define WIN32_LEAN_AND_MEAN
		#include <Windows.h>
		#undef WIN32_LEAN_AND_MEAN
		#include <debugapi.h>
		
		void cpc_debug_print(const char *str) {
			OutputDebugStringA(str);
		}

		void cpc_debug_break(void) {
			DebugBreak();
		}
	#else
		#include <stdio.h>
		#include <signal.h>
		
		void cpc_debug_print(const char *str) {
			int result = fputs(str, stdout);
			CPC_ASSERT(result >= 0);
		}

		void cpc_debug_break(void) {
			int result = raise(SIGTRAP);
			CPC_ASSERT(result == 0);
		}
	#endif
#else
	void cpc_debug_print(const char *str) {
		CPC_UNUSED_VAR(str);
	}
	
	void cpc_debug_break(void) {}
#endif
