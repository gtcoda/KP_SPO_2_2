#include "BIOS.h"

HRESULT BIOS::Go(void) {
	SysInfo::Info(&BIOSstr);
	return S_OK;
}