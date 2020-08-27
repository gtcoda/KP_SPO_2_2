#pragma once

#ifndef POINTER_H
#define POINTER_H
#include "SysInfo.h"



class POINTER : public SysInfo {

private:

	// Информация о мыши
	WMIInfo POINTER_I = {
		//WMI CLASS
			"Win32_PointingDevice",
			"Pointer_INFO",
			"Pointer",
			{
		// Начало инициализации внутренней структуры info	
			{"Caption", "Наименование Устройства", ""},
			{"Description", "Описание", ""},
			{"Manufacturer", "Производитель", ""},
			{"HardwareType", "Тип", ""},
			{"DeviceID", "Идентификатор", ""},
			{"DeviceInterface ", "Тип интерфейса", ""},
			{"NumberOfButtons ", "Количество кнопок", ""}
			// Конец инициализации внутренней структyры info	
	} };


	WMIInfoMany POINTERstr = { "Указатель №" };


public:
	HRESULT Go(void);

};




#endif