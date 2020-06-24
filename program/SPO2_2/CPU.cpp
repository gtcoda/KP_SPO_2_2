#include "CPU.h"

HRESULT CPU::Go(void) {
	SysInfo::Info(&CPUstr);
	SysInfo::OutWMIdata(&CPUstr);
	

	return S_OK;
}
