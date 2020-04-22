#include "SysInfo.h"


// Отобразить информацию о процессоре
HRESULT SysInfo::ShowProcessor() {
	
	HRESULT hr;
	cout << "CPU Info" << endl;
	IEnumWbemClassObject * pEnumerator = NULL;

	objWMI.Get((_bstr_t)"SELECT * FROM Win32_Processor", &pEnumerator);


	hr = WBEM_S_NO_ERROR;
	// Final Next will return WBEM_S_FALSE
	while (WBEM_S_NO_ERROR == hr)
	{
		ULONG            uReturned;
		IWbemClassObject*    apObj[2];

		hr = pEnumerator->Next(WBEM_INFINITE, 2, apObj, &uReturned);

		if (SUCCEEDED(hr))
		{
			for (ULONG n = 0; n < uReturned; n++)
			{
				VARIANT vtProp;
				
				hr = apObj[n]->Get((_bstr_t)"AddressWidth", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "Разрядность: " << vtProp.intVal << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"Architecture", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "Архитектура: ";

					switch (vtProp.intVal) {
					case 0: cout << "x86"; break;
					case 1: cout << "MIPS"; break;
					case 2: cout << "Alpha"; break;
					case 3: cout << "PowerPC"; break;
					case 5: cout << "ARM"; break;
					case 6: cout << "ia64"; break;
					case 9: cout << "x64"; break;
					}
					cout << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"Name", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "Имя: " << vtProp.bstrVal << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"MaxClockSpeed", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "Максимальная частота: " << vtProp.intVal << " МГц" << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"CurrentClockSpeed", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "Текущая частота: " << vtProp.intVal << " МГц" << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"ExtClock", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "Частота шины: " << vtProp.intVal << " МГц" << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"NumberOfCores", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "Количество ядер: " << vtProp.intVal << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"NumberOfEnabledCore", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "Количество активных ядер: " << vtProp.intVal << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"NumberOfLogicalProcessors", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "Количество логических ядер: " << vtProp.intVal << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"L2CacheSize", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "Размер L2: " << vtProp.intVal << " Кб" << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"L3CacheSize", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "Размер L3: " << vtProp.intVal << " Кб" << endl;
				}
				


				apObj[n]->Release();
			}

		}
	}

	return S_OK;
}

// Отобразить информацию о BIOS
HRESULT SysInfo::ShowBIOS() {
	HRESULT hr;
	cout << "BIOS Info" << endl;



	IEnumWbemClassObject * pEnumerator = NULL;

	objWMI.Get((_bstr_t)"SELECT * FROM Win32_BIOS", &pEnumerator);


	hr = WBEM_S_NO_ERROR;
	// Final Next will return WBEM_S_FALSE
	while (WBEM_S_NO_ERROR == hr)
	{
		ULONG            uReturned;
		IWbemClassObject*    apObj[10];

		hr = pEnumerator->Next(WBEM_INFINITE, 10, apObj, &uReturned);

		if (SUCCEEDED(hr))
		{
			for (ULONG n = 0; n < uReturned; n++)
			{
				VARIANT vtProp;

				apObj[n]->Get((_bstr_t)"BIOSVersion", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					SAFEARRAY * ar;
					BSTR *Version;
					// Прeобразуем VARIANT в SAFEARRAY
					ar = vtProp.parray;
					// Получим доступ к SAFEARRAY
					hr = SafeArrayAccessData(ar, (void **)&Version);
					cout << "BIOS Version: ";
					for (int i = 0; i < ar->rgsabound->cElements; i++) {
						wcout << Version[i] << " ";
					}
					SafeArrayUnaccessData(ar);
					cout << endl;
				}

				apObj[n]->Get((_bstr_t)"BuildNumber", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "BuildNumber: " << vtProp.intVal << " Кб" << endl;
				}


				apObj[n]->Get((_bstr_t)"Manufacturer", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "Произведено: " << vtProp.bstrVal << endl;
				}

				apObj[n]->Get((_bstr_t)"Version", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "Версия: " << vtProp.bstrVal << endl;
				}


				apObj[n]->Release();
			}

		}
	}


	return S_OK;
}

// Отобразить информацию о DISK
HRESULT SysInfo::ShowDISK() {
	HRESULT hr;
	cout << "DISK Info" << endl;
	IEnumWbemClassObject * pEnumerator = NULL;
	
	objWMI.Get((_bstr_t)"SELECT * FROM Win32_DiskDrive", &pEnumerator);
	

	hr = WBEM_S_NO_ERROR;
	// Final Next will return WBEM_S_FALSE
	while (WBEM_S_NO_ERROR == hr)
	{
		ULONG            uReturned;
		IWbemClassObject*    apObj[10];

		hr = pEnumerator->Next(WBEM_INFINITE, 10, apObj, &uReturned);

		if (SUCCEEDED(hr))
		{
			for (ULONG n = 0; n < uReturned; n++)
			{

				VARIANT vtProp;
				VARIANT Caption = {}, Model = {}, Size = {};

				apObj[n]->Get((_bstr_t)"Caption", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "Название: " << vtProp.bstrVal  << endl;
				}

				apObj[n]->Get((_bstr_t)"Model", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "Модель: " << vtProp.bstrVal << endl;
				}

				apObj[n]->Get((_bstr_t)"Size", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "Размер: " << vtProp.intVal << endl;
				}



				apObj[n]->Release();
			}

		}    
	}    


	return S_OK;
}

// Отобразить информацию о разделах
HRESULT SysInfo::ShowPartition() {
	HRESULT hr;
	cout << "Partition Info" << endl;
	IEnumWbemClassObject * pEnumerator = NULL;

	objWMI.Get((_bstr_t)"SELECT * FROM Win32_LogicalDisk", &pEnumerator);


	hr = WBEM_S_NO_ERROR;

	while (WBEM_S_NO_ERROR == hr)
	{
		ULONG            uReturned;
		IWbemClassObject*    apObj[10];

		hr = pEnumerator->Next(WBEM_INFINITE, 10, apObj, &uReturned);

		if (uReturned > 0)
		{
			std::cout << "Caption \t"
				<< "FileSystem \t"
				<< "Size \t"
				<< "FreeSize \t"
				<< std::endl;


			for (ULONG n = 0; n < uReturned; n++)
			{

				VARIANT vtProp;
				
				apObj[n]->Get((_bstr_t)"Caption", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << vtProp.bstrVal << "\t\t";
				}


				apObj[n]->Get((_bstr_t)"FileSystem", 0, &vtProp, 0, 0);
				if (!FAILED(hr) & (vtProp.bstrVal != NULL)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout  << vtProp.bstrVal << "\t\t";
				}

				apObj[n]->Get((_bstr_t)"Size", 0, &vtProp, 0, 0);
				if (!FAILED(hr) & (vtProp.bstrVal != NULL)) {
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_UI8);
					cout << vtProp.llVal / 1000000000 << "\t";
				}

				apObj[n]->Get((_bstr_t)"FreeSpace", 0, &vtProp, 0, 0);
				if (!FAILED(hr) & (vtProp.bstrVal != NULL)) {
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_UI8);
					cout << vtProp.llVal / 1000000000 << "\t";
				}

				cout << endl;
				apObj[n]->Release();
			}

		}
	}


	return S_OK;
}
