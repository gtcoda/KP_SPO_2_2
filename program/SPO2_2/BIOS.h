#pragma once

#ifndef BIOS_H
#define BIOS_H
#include "SysInfo.h"



class BIOS : public SysInfo {

private:
	// ���������� � BIOS	
	WMIInfo BIOSstr = {
		//WMI CLASS
			"Win32_BIOS",
			"BIOS_INFO",
			"BIOS",
			{
		// ������ ������������� ���������� ��������� info	
			{"Manufacturer", "�����������", ""},
			{"Version", "������", ""},
			{"Caption", "��������", ""}
			// ����� ������������� ���������� ������y�� info	
			} };

public:
	HRESULT Go(void);

};




#endif