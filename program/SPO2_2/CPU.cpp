#include "CPU.h"

HRESULT CPU::Go(void) {
	SysInfo::Info(&CPUstr);
	return S_OK;
}
