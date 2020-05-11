#pragma once

#ifndef BASEBOARD_H
#define BASEBOARD_H
#include "SysInfo.h"



class BASEBOARD : public SysInfo {

private:

	//Информация о Материнской Плате
	WMIInfo BaseBoard = {
		//WMI CLASS
			"Win32_BaseBoard",
			"BaseBoard_INFO",
			"BaseBoard",
			{
		// Начало инициализации внутренней структуры info	
			{"Caption", "Наименование Устройства", ""},
			{"Description", "Описание", ""},
			{"Manufacturer", "Производитель", ""},
			{"Product", "Тип", ""},
			{"SerialNumber", "Серийный номер", ""},
			{"Tag", "Идентификатор", ""},
			{"Version", "Версия", ""}
			// Конец инициализации внутренней структyры info	
			} };


public:
	HRESULT Go(void);

};




#endif#pragma once
