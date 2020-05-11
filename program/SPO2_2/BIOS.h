#pragma once

#ifndef BIOS_H
#define BIOS_H
#include "SysInfo.h"



class BIOS : public SysInfo {

private:
	// Информация о BIOS	
	WMIInfo BIOSstr = {
		//WMI CLASS
			"Win32_BIOS",
			"BIOS_INFO",
			"BIOS",
			{
		// Начало инициализации внутренней структуры info	
			{"Manufacturer", "Произведено", ""},
			{"Version", "Версия", ""},
			{"Caption", "Название", ""}
			// Конец инициализации внутренней структyры info	
			} };

public:
	HRESULT Go(void);

};




#endif