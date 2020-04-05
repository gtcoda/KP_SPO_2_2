
#define _WIN32_DCOM

#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")
int s;



HRESULT GetClassFull(IWbemServices * pSvc, BSTR Query) {
	HRESULT hr;

	IEnumWbemClassObject* pEnumerator = NULL;
	hr = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(Query),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hr)) {
		return hr;
	}

	wcout << "============" << Query << "===========" << endl;


	IWbemClassObject *pclsObj = NULL;
	ULONG uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == uReturn)
		{
			break;
		}

		SAFEARRAY *vtPR = NULL;
		hr = pclsObj->GetNames(NULL, WBEM_FLAG_ALWAYS, NULL, &vtPR);
		// Указатель на массив с именами свойств
		BSTR *PrName;
		hr = SafeArrayAccessData(vtPR, (void **)&PrName);


		for (int i = 10; i < vtPR->rgsabound->cElements; i++) {
			//wcout << PrName[i] << endl;


			VARIANT vtProp;

			// Получаем значения свойства Name.
			hr = pclsObj->Get(PrName[i], 0, &vtProp, 0, 0);
			// Преобразуем ответ в строку
			hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
			// Отобразим ответ
			if (vtProp.bstrVal != NULL) {
				wcout << PrName[i] << "	: " << vtProp.bstrVal << endl;
			}

			VariantClear(&vtProp);
		}

		SafeArrayUnaccessData(vtPR);
		pclsObj->Release();
	}




}



int main(int iArgCnt, char ** argv)
{
	HRESULT hres;

	// Step 1: --------------------------------------------------
	// Initialize COM. ------------------------------------------

	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres))
	{
		cout << "Failed to initialize COM library. Error code = 0x"
			<< hex << hres << endl;
		return 1;                  // Program has failed.
	}

	// Step 2: --------------------------------------------------
	// Set general COM security levels --------------------------

	hres = CoInitializeSecurity(
		NULL,
		-1,                          // COM negotiates service
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities 
		NULL                         // Reserved
	);


	if (FAILED(hres))
	{
		cout << "Failed to initialize security. Error code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return 1;                      // Program has failed.
	}

	// Step 3: ---------------------------------------------------
	// Obtain the initial locator to WMI -------------------------

	IWbemLocator *pLoc = NULL;

	hres = CoCreateInstance(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID *)&pLoc);

	if (FAILED(hres))
	{
		cout << "Failed to create IWbemLocator object. "
			<< "Err code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return 1;                 // Program has failed.
	}

	// Step 4: ---------------------------------------------------
	// Connect to WMI through the IWbemLocator::ConnectServer method

	IWbemServices *pSvc = NULL;

	// Connect to the local root\cimv2 namespace
	// and obtain pointer pSvc to make IWbemServices calls.
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"),
		NULL,
		NULL,
		0,
		NULL,
		0,
		0,
		&pSvc
	);

	if (FAILED(hres))
	{
		cout << "Could not connect. Error code = 0x"
			<< hex << hres << endl;
		pLoc->Release();
		CoUninitialize();
		return 1;                // Program has failed.
	}

	cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;


	// Step 5: --------------------------------------------------
	// Set security levels for the proxy ------------------------

	hres = CoSetProxyBlanket(
		pSvc,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx 
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx 
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities 
	);

	if (FAILED(hres))
	{
		cout << "Could not set proxy blanket. Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return 1;               // Program has failed.
	}



	GetClassFull(pSvc,(_bstr_t)"SELECT * FROM Win32_Processor");




/*
	// For example, get the name of the operating system
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_Processor"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hres))
	{
		cout << "Query for operating system name failed."
			<< " Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return 1;               // Program has failed.
	}

	// Step 7: -------------------------------------------------
	// Get the data from the query in step 6 -------------------

	IWbemClassObject *pclsObj = NULL;
	ULONG uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == uReturn)
		{
			break;
		}

		SAFEARRAY *vtPR = NULL;
		hr = pclsObj->GetNames(NULL, WBEM_FLAG_ALWAYS,NULL, &vtPR);
		// Указатель на массив с именами свойств
		BSTR *PrName;
		hr = SafeArrayAccessData(vtPR, (void **)&PrName);


		for (int i = 10; i < vtPR->rgsabound->cElements; i++) {
			//wcout << PrName[i] << endl;


			VARIANT vtProp;

			// Получаем значения свойства Name.
			hr = pclsObj->Get(PrName[i], 0, &vtProp, 0, 0);
			// Преобразуем ответ в строку
			hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
			// Отобразим ответ
			if (vtProp.bstrVal != NULL) {
				wcout << PrName[i] << "	: " << vtProp.bstrVal << endl;
			}

			VariantClear(&vtProp);
		}

		SafeArrayUnaccessData(vtPR);




		VARIANT vtProp;

		// Get the value of the Name property
		hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		wcout << " OS Name : " << vtProp.bstrVal << endl;
		VariantClear(&vtProp);

		pclsObj->Release();
	}



	*/


	
	pLoc->Release();
	pSvc->Release();
	CoUninitialize();
	return 0;
}