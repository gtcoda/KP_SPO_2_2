#include "BASEBOARD.h"

HRESULT BASEBOARD::Go(void) {
	SysInfo::Info(&BaseBoardstr);

	return S_OK;
}