#pragma once

#ifndef UPTIME_H
#define UPTIME_H
#include "SysInfo.h"



class UPTIME : public SysInfo {

private:

	// Информация о uptime
	WMIInfo UPTIMEstr = {
		//WMI CLASS
			"",
			"Время работы ОС",
			"UPTIME",
			{
		// Начало инициализации внутренней структуры info	
			{"Day", "Дней", ""},
			{"Hours", "Часов", ""},
			{"Min", "Минут", ""},
			{"Second", "Секунд", ""},
			// Конец инициализации внутренней структyры info	
			} };

public:
	HRESULT Go(void);
	// Возвращает время работы системы
	HRESULT UpTime(WMIInfo *upt);

};




#endif

