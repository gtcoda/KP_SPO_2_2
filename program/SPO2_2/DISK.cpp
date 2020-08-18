#include "DISK.h"

HRESULT DISK::Go(void) {
	SysInfo::Info(&DISKstr, &DISK_I);

	return S_OK;
}