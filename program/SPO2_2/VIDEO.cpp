#include "VIDEO.h"

HRESULT VIDEO::Go(void) {
	SysInfo::Info(&VIDEOstr);
	return S_OK;
}
