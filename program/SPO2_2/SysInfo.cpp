#include "SysInfo.h"


// ���������� ���������� � ����������
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
					cout << "�����������: " << vtProp.intVal << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"Architecture", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "�����������: ";

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
					// ����������� ����� � ������
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "���: " << vtProp.bstrVal << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"MaxClockSpeed", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "������������ �������: " << vtProp.intVal << " ���" << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"CurrentClockSpeed", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "������� �������: " << vtProp.intVal << " ���" << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"ExtClock", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "������� ����: " << vtProp.intVal << " ���" << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"NumberOfCores", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "���������� ����: " << vtProp.intVal << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"NumberOfEnabledCore", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "���������� �������� ����: " << vtProp.intVal << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"NumberOfLogicalProcessors", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "���������� ���������� ����: " << vtProp.intVal << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"L2CacheSize", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "������ L2: " << vtProp.intVal << " ��" << endl;
				}

				hr = apObj[n]->Get((_bstr_t)"L3CacheSize", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					cout << "������ L3: " << vtProp.intVal << " ��" << endl;
				}
				


				apObj[n]->Release();
			}

		}
	}

	return S_OK;
}

// ���������� ���������� � BIOS
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
					// ��e�������� VARIANT � SAFEARRAY
					ar = vtProp.parray;
					// ������� ������ � SAFEARRAY
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
					cout << "BuildNumber: " << vtProp.intVal << " ��" << endl;
				}


				apObj[n]->Get((_bstr_t)"Manufacturer", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// ����������� ����� � ������
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "�����������: " << vtProp.bstrVal << endl;
				}

				apObj[n]->Get((_bstr_t)"Version", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// ����������� ����� � ������
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "������: " << vtProp.bstrVal << endl;
				}


				apObj[n]->Release();
			}

		}
	}


	return S_OK;
}

// ���������� ���������� � DISK
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
					// ����������� ����� � ������
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "��������: " << vtProp.bstrVal  << endl;
				}

				apObj[n]->Get((_bstr_t)"Model", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// ����������� ����� � ������
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "������: " << vtProp.bstrVal << endl;
				}

				apObj[n]->Get((_bstr_t)"Size", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// ����������� ����� � ������
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "������: " << vtProp.intVal << endl;
				}



				apObj[n]->Release();
			}

		}    
	}    


	return S_OK;
}