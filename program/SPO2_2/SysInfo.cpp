#include "SysInfo.h"


// Отобразить информацию о процессоре
HRESULT SysInfo::ShowProcessor() {
	HRESULT hr;
	cout << "CPU Info" << endl;
	VARIANT vtProp;

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"AddressWidth", &vtProp);
	if (!FAILED(hr)) {
		cout << "Разрядность: " << vtProp.intVal << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"Architecture", &vtProp);
	if (!FAILED(hr)) {
		cout << "Архитектура: ";

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
		// Преобразуем ответ в строку
		hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
		wcout << "Имя: " << vtProp.bstrVal  << endl;
	}




	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"MaxClockSpeed", &vtProp);
	if (!FAILED(hr)) {
		cout << "Максимальная частота: " << vtProp.intVal << " МГц" << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"CurrentClockSpeed", &vtProp);
	if (!FAILED(hr)) {
		cout << "Текущая частота: " << vtProp.intVal << " МГц" << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"ExtClock", &vtProp);
	if (!FAILED(hr)) {
		cout << "Частота шины: " << vtProp.intVal << " МГц" << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"NumberOfCores", &vtProp);
	if (!FAILED(hr)) {
		cout << "Количество ядер: " << vtProp.intVal  << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"NumberOfEnabledCore", &vtProp);
	if (!FAILED(hr)) {
		cout << "Количество активных ядер: " << vtProp.intVal << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"NumberOfLogicalProcessors", &vtProp);
	if (!FAILED(hr)) {
		cout << "Количество логических ядер: " << vtProp.intVal << endl;
	}

	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"L2CacheSize", &vtProp);
	if (!FAILED(hr)) {
		cout << "Размер L2: " << vtProp.intVal << " Кб" << endl;
	}


	hr = objWMI.GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"L3CacheSize", &vtProp);
	if (!FAILED(hr)) {
		cout << "Размер L3: " << vtProp.intVal << " Кб" << endl;
	}



	return S_OK;
}
