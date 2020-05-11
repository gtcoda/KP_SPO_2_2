#pragma once

#ifndef PARTITION_H
#define PARTITION_H
#include "SysInfo.h"



class PARTITION : public SysInfo {

private:

	// Информация о partition
	WMIInfo PARTITION_I = {
		//WMI CLASS
			"Win32_LogicalDisk",
			"PARTITION_INFO",
			"PART",
			{
		// Начало инициализации внутренней структуры info
			{"Size", "Размер [б]", ""},
			{"FileSystem", "Файловая система", ""},
			{"FreeSpace", "Свободный обьем [б]", ""},
			{"Caption", "Название", ""}
			// Конец инициализации внутренней структyры info	
	} };

	WMIInfoMany PARTITIONstr = { "Раздел №" };


public:
	HRESULT Go(void);

};




#endif#pragma once
