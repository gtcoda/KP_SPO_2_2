#pragma once

#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "SysInfo.h"



class KEYBOARD : public SysInfo {

private:

	// Информация о клавиатуре
	WMIInfo KEYBOARD_I = {
		//WMI CLASS
			"Win32_Keyboard",
			"KEYBOARD_INFO",
			"KEYBOARD",
			{
		// Начало инициализации внутренней структуры info
			{"Description", "Описание", ""},
			{"DeviceID", "Идентификатор устройства", ""},
			{"Caption", "Название", ""},
			{"NumberOfFunctionKeys", "Кол-во ФК", ""}
			// Конец инициализации внутренней структyры info	
				} };

	WMIInfoMany KEYBOARDstr = { "Клавиатура №" };


public:
	HRESULT Go(void);

};




#endif
