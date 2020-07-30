#pragma once
#ifndef VIDEO_H
#define VIDEO_H
#include "SysInfo.h"



class VIDEO : public SysInfo {

private:
	//Информация о видеокарте
	WMIInfo VIDEOstr = {
		//WMI CLASS
			"Win32_VideoController",
			"VIDEO_INFO",
			"VIDEO",
			{
		// Начало инициализации внутренней структуры info	
			{"AdapterCompatibility", "Производитель", ""},
			{"Description", "Название", ""},
			{"AdapterRAM", "Размер памяти", ""},
			{"CurrentHorizontalResolution", "Горизонтальное разрешение", ""},
			{"CurrentVerticalResolution", "Вертикальное разрешение", ""},
			{"DriverVersion", "Версия драйвера", ""},
			{"PNPDeviceID", "PNP", ""},
			// Конец инициализации внутренней структyры info	
			} };

public:
	HRESULT Go(void);
	HRESULT GoXML(WMIInfo * CPU);



};




#endif#pragma once
