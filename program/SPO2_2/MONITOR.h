#pragma once

#ifndef MONITOR_H
#define MONITOR_H
#include "SysInfo.h"



class MONITOR : public SysInfo {

private:
	// Информация о мониторе
	WMIInfo DesktopMonitor_I = {
		//WMI CLASS
			"Win32_DesktopMonitor",
			"DesktopMonitor_INFO",
			"DesktopMonitor",
			{
		// Начало инициализации внутренней структуры info
			{"Description", "Описание:", ""},
			{"DeviceID", "Идентификатор устройства", ""},
			{"Name", "Название", ""},
			{"MonitorManufacturer", "Производитель монитора", ""}
			// Конец инициализации внутренней структyры info	
		} };

	WMIInfoMany DesktopMonitor = { "Монитор №" };



public:
	HRESULT Go(void);

};




#endif
