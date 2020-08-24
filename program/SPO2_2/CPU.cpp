#include "CPU.h"

HRESULT CPU::Go(void) {
	SysInfo::WMIData(&CPUstr);
	SysInfo::ShowWMIdata(&CPUstr);
	SysInfo::OutWMIdata(&CPUstr);
	SysInfo::PushMysql(&CPUstr);

	

	return S_OK;
}

