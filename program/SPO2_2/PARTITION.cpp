#include "PARTITION.h"

HRESULT PARTITION::Go(void) {
	SysInfo::Info(&PARTITIONstr, &PARTITION_I);

	return S_OK;
}