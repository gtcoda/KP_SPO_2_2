#include "NETWORK.h"

HRESULT NETWORK::Go(void) {
	SysInfo::Info(&NetworkAdapter,&NetworkAdapter_I);

	return S_OK;
}