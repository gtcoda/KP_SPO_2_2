#pragma once
#pragma once

#ifndef DISK_H
#define DISK_H
#include "SysInfo.h"



class DISK : public SysInfo {

private:
	// ���������� � ������
	WMIInfo DISK_I = {
		//WMI CLASS
			"Win32_DiskDrive",
			"DISK_INFO",
			"DISK",
			{
		// ������ ������������� ���������� ��������� info
			{"Size", "������ [�]", ""},
			{"Model", "������", ""},
			{"Caption", "��������", ""}
			// ����� ������������� ���������� ������y�� info	
				} };

	WMIInfoMany DISKstr = { "���� �" };

public:
	HRESULT Go(void);

};




#endif