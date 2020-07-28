#pragma once

#ifndef NETWORK_H
#define NETWORK_H
#define _CRT_SECURE_NO_WARNINGS
#include "SysInfo.h"


#include <stdio.h>
#include <windows.h>
#include <iphlpapi.h>
#pragma comment(lib, "IPHLPAPI.lib")


class NETWORK : public SysInfo {

private:

	// Сетевые адаптеры
		// Информация о сетевых адаптерах
	WMIInfo NetworkAdapter_I = {
		//WMI CLASS
			"Win32_NetworkAdapter",
			"NetworkAdapter_INFO",
			"NETWORK",
			{
		// Начало инициализации внутренней структуры info
			{"AdapterName", "Имя устройства: ", ""},
			{"Description", "Описание: ", ""},
			{"MAC", "MAC адрес: ", ""},
			{"IP", "IP адрес: ", ""},
			{"Gateway", "Шлюз: ", ""},
			{"DHCP", "DNCP статус: ", ""},
			{"IP_DHCP", "DNCP сервер: ", ""}
			// Конец инициализации внутренней структyры info	
		} };

	WMIInfoMany NetworkAdapter = { "Адаптер №" };


	HRESULT GetNetworkInfo(WMIInfoMany *NetworkAdapter);

public:
	HRESULT Go(void);

};




#endif