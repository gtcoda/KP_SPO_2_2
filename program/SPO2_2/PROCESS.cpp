#include "PROCESS.h"

HRESULT PROCESS::Go(void) {
	SysInfo::Info(&Process,&Process_info);

	return S_OK;
}