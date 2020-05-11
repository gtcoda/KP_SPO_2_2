#pragma once

#ifndef PROCESS_H
#define PROCESS_H
#include "SysInfo.h"



class PROCESS : public SysInfo {

private:
	// Информация о запущеных процессах
	std::vector <WMIInfo> Process;
	// Описание получаемых параметров
	WMIInfo Process_info = {
		//WMI CLASS
			"Win32_Process",
			"Process_INFO",
			"PROCESS",
			{
		// Начало инициализации внутренней структуры info	
			{"Handle", "Id", ""},
			{"Name", "Имя", ""}

			// Конец инициализации внутренней структyры info	
			} };

public:
	HRESULT Go(void);

};




#endif
#pragma once
