#pragma once
#ifndef CPU_H
#define CPU_H
#include "SysInfo.h"



class CPU : public SysInfo {

private:
	//���������� � CPU
	WMIInfo CPUstr = {
		//WMI CLASS
			"Win32_Processor",
			"CPU_INFO",
			"CPU",
			{
		// ������ ������������� ���������� ��������� info	
			{"AddressWidth", "�����������", ""},
			{"Architecture", "�����������", ""},
			{"Name", "���", ""},
			{"MaxClockSpeed", "������������ �������", ""},
			{"CurrentClockSpeed", "������� �������", ""},
			{"ExtClock", "������� ����", ""},
			{"NumberOfCores", "���������� ����", ""},
			{"NumberOfEnabledCore", "���������� �������� ����", ""},
			{"NumberOfLogicalProcessors", "���������� ���������� ����", ""},
			{"L2CacheSize", "������ L2", ""},
			{"L3CacheSize", "������ L3", ""}
			// ����� ������������� ���������� ������y�� info	
			} };

public:
	HRESULT Go(void);

};




#endif