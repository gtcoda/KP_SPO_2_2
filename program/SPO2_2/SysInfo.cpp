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


	return S_OK;
}
