#pragma once
#ifndef USERS_H
#define USERS_H
#include "SysInfo.h"
#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")

#include <stdio.h>
#include <windows.h>
#include <lm.h>
#include <locale.h>
#include <ctime>

class USERS : public SysInfo {

private:
	//Информация о пользователях
	WMIInfo USERS_I = {
		//WMI CLASS
			"",
			"USERS_INFO",
			"USERS",
			{
		// Начало инициализации внутренней структуры info	
			{"Name", "Имя", ""},
			{"Last_logon", "Последний вход", ""},
			{"Day", "Дней", ""},
			{"Hours", "Часов", ""},
			{"Min", "Минут", ""},
			{"Second", "Секунд", ""},
			// Конец инициализации внутренней структyры info	
			} };

	WMIInfoMany USERSstr = { "Пользователь " };





public:
	HRESULT Go(void);




};




#endif#pragma once
