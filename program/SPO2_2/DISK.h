#pragma once
#pragma once

#ifndef DISK_H
#define DISK_H
#include "SysInfo.h"



class DISK : public SysInfo {

private:
	// Информация о дисках
	WMIInfo DISK_I = {
		//WMI CLASS
			"Win32_DiskDrive",
			"DISK_INFO",
			"DISK",
			{
		// Начало инициализации внутренней структуры info
			{"Size", "Размер [б]", ""},
			{"Model", "Модель", ""},
			{"Caption", "Название", ""}
			// Конец инициализации внутренней структyры info	
				} };

	WMIInfoMany DISKstr = { "Диск №" };

public:
	HRESULT Go(void);

};




#endif