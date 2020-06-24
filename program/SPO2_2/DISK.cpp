#include "DISK.h"

HRESULT DISK::Go(void) {
	SysInfo::Info(&DISKstr, &DISK_I);
	SysInfo::OutWMIdata(&DISKstr);

	return S_OK;
}