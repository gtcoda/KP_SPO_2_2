#pragma once
#ifndef CPU_H
#define CPU_H
#include "SysInfo.h"



class CPU : public SysInfo {

private:
	//Информация о CPU
	WMIInfo CPUstr = {
		//WMI CLASS
			"Win32_Processor",
			"CPU_INFO",
			"CPU",
			{
		// Начало инициализации внутренней структуры info	
			{"AddressWidth", "Разрядность", ""},
			{"Architecture", "Архитектура", ""},
			{"Name", "Имя", ""},
			{"MaxClockSpeed", "Максимальная частота", ""},
			{"CurrentClockSpeed", "Текущая частота", ""},
			{"ExtClock", "Частота шины", ""},
			{"NumberOfCores", "Количество ядер", ""},
			{"NumberOfEnabledCore", "Количество активных ядер", ""},
			{"NumberOfLogicalProcessors", "Количество логических ядер", ""},
			{"L2CacheSize", "Размер L2", ""},
			{"L3CacheSize", "Размер L3", ""}
			// Конец инициализации внутренней структyры info	
			} };

public:
	HRESULT Go(void);
	HRESULT GoXML(WMIInfo * CPU);



};




#endif