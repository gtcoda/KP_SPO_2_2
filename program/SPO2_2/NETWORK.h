#pragma once

#ifndef NETWORK_H
#define NETWORK_H
#include "SysInfo.h"



class NETWORK : public SysInfo {

private:

	// Сетевые адаптеры
		// Информация о сетевых адаптерах
	WMIInfo NetworkAdapter_I = {
		//WMI CLASS
			"Win32_NetworkAdapter",
			"NetworkAdapter_INFO",
			"NetworkAdapter",
			{
		// Начало инициализации внутренней структуры info
			{"Caption", "Наименование устройства: ", ""},
			{"Description", "Описание: ", ""},
			{"DeviceID", "Идентификатор устройства: ", ""},
			{"Manufacturer", "Производитель: ", ""},
			{"MaxSpeed", "Максимальная скорость: ", ""},
			{"NetworkAddresses[]", "IP-адрес: ", ""},
			{"Status", "Статус устройства: ", ""}
			// Конец инициализации внутренней структyры info	
		} };

	WMIInfoMany NetworkAdapter = { "Адаптер №" };


public:
	HRESULT Go(void);

};




#endif