#include "BASEBOARD.h"

HRESULT BASEBOARD::Go(void) {
	SysInfo::Info(&BaseBoard);

	return S_OK;
}