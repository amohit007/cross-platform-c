#ifndef CPC_BOOL_H
#define CPC_BOOL_H

#if !defined(_MSC_VER) || _MSC_VER >= 1800
	#include <stdbool.h>
#else
	#ifndef bool
		#define bool char;
	#endif

	#ifndef true
		#define true 1
	#endif

	#ifndef false
		#define false 0
	#endif
#endif

#endif
