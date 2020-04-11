#include "SysInfo.h"


// ���������� ���������� � ����������
HRESULT SysInfo::ShowProcessor() {
	HRESULT hr;
	cout << "CPU Info" << endl;
	VARIANT vtProp;

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"AddressWidth", &vtProp);
	if (!FAILED(hr)) {
		cout << "�����������: " << vtProp.intVal << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"Architecture", &vtProp);
	if (!FAILED(hr)) {
		cout << "�����������: ";

		switch (vtProp.intVal) {
		case 0: cout << "x86" ; break;
		case 1: cout << "MIPS"; break;
		case 2: cout << "Alpha"; break;
		case 3: cout << "PowerPC"; break;
		case 5: cout << "ARM"; break;
		case 6: cout << "ia64"; break;
		case 9: cout << "x64"; break;
		}
		cout << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"Name", &vtProp);
	if (!FAILED(hr)) {
		// ����������� ����� � ������
		hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
		wcout << "���: " << vtProp.bstrVal  << endl;
	}




	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"MaxClockSpeed", &vtProp);
	if (!FAILED(hr)) {
		cout << "������������ �������: " << vtProp.intVal << " ���" << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"CurrentClockSpeed", &vtProp);
	if (!FAILED(hr)) {
		cout << "������� �������: " << vtProp.intVal << " ���" << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"ExtClock", &vtProp);
	if (!FAILED(hr)) {
		cout << "������� ����: " << vtProp.intVal << " ���" << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"NumberOfCores", &vtProp);
	if (!FAILED(hr)) {
		cout << "���������� ����: " << vtProp.intVal  << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"NumberOfEnabledCore", &vtProp);
	if (!FAILED(hr)) {
		cout << "���������� �������� ����: " << vtProp.intVal << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"NumberOfLogicalProcessors", &vtProp);
	if (!FAILED(hr)) {
		cout << "���������� ���������� ����: " << vtProp.intVal << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"L2CacheSize", &vtProp);
	if (!FAILED(hr)) {
		cout << "������ L2: " << vtProp.intVal << " ��" << endl;
	}


	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"L3CacheSize", &vtProp);
	if (!FAILED(hr)) {
		cout << "������ L3: " << vtProp.intVal << " ��" << endl;
	}



	return S_OK;
}
