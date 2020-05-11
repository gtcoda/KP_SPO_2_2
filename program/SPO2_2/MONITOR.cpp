#include "MONITOR.h"

HRESULT MONITOR::Go(void) {
	SysInfo::Info(&DesktopMonitor, &DesktopMonitor_I);

	return S_OK;
}