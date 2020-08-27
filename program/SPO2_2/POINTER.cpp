#include "POINTER.h"

HRESULT POINTER::Go(void) {
	SysInfo::Info(&POINTERstr, &POINTER_I);

	return S_OK;
}