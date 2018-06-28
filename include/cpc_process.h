#ifndef CPC_PROCESS_H
#define CPC_PROCESS_H

#include "cpc_base.h"

#define CPC_PROCESS_EXIT_SUCCESS 0
#define CPC_PROCESS_EXIT_FAILURE 1

CPC_NO_RETURN void cpc_process_exit(unsigned int status);

#endif
