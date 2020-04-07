#include "ControlWMI.h"


// Конструктор. Подключение к WMI
ControlWMI::ControlWMI() {
	HRESULT hr;
		
	// Step 1: --------------------------------------------------
	// Initialize COM. ------------------------------------------

	hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		cout << "Failed to initialize COM library. Error code = 0x"
			<< hex << hr << endl;
	}

	// Step 2: --------------------------------------------------
	// Set general COM security levels --------------------------

	hr = CoInitializeSecurity(
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


	if (FAILED(hr))
	{
		cout << "Failed to initialize security. Error code = 0x"
			<< hex << hr << endl;
		CoUninitialize();
	}

	// Step 3: ---------------------------------------------------
	// Obtain the initial locator to WMI -------------------------

	//IWbemLocator *pLoc = NULL;

	hr = CoCreateInstance(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID *)&pLoc);

	if (FAILED(hr))
	{
		cout << "Failed to create IWbemLocator object. "
			<< "Err code = 0x"
			<< hex << hr << endl;
		CoUninitialize();
	}

	// Step 4: ---------------------------------------------------
	// Connect to WMI through the IWbemLocator::ConnectServer method

	// Connect to the local root\cimv2 namespace
	// and obtain pointer pSvc to make IWbemServices calls.
	hr = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"),
		NULL,
		NULL,
		0,
		NULL,
		0,
		0,
		&pSvc
	);

	if (FAILED(hr))
	{
		cout << "Could not connect. Error code = 0x"
			<< hex << hr << endl;
		pLoc->Release();
		CoUninitialize();
	}

	cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;


	// Step 5: --------------------------------------------------
	// Set security levels for the proxy ------------------------

	hr = CoSetProxyBlanket(
		pSvc,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx 
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx 
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities 
	);

	if (FAILED(hr))
	{
		cout << "Could not set proxy blanket. Error code = 0x"
			<< hex << hr << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
	}

	
}

// Отобразить в stdout результат запроса
HRESULT ControlWMI::ViewClassFull(BSTR Query) {
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

	return S_OK;
}

HRESULT ControlWMI::GetProp(BSTR Query, IWbemClassObject **pclsObj) {
	HRESULT hr;

	// Обьект CIM
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
	ULONG uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, pclsObj, &uReturn);

		if (0 == uReturn)
		{
			return E_FAIL;
		}
		return S_OK;
	}
	return E_FAIL;
}


// Отдать значение конкретного свойства.
HRESULT ControlWMI::GetPropName(BSTR Query, BSTR Name, VARIANT *vtProp) {
	// Указатель на обьект
	IWbemClassObject *pclsObj = NULL;
	HRESULT hr;

	// Передадим указатель на указатель.
	hr = GetProp(Query, &pclsObj);

	if (FAILED(hr)) {
		return hr;
	}

	// Получаем значения свойства Name.
	hr = pclsObj->Get(Name, 0, vtProp, 0, 0);
	if (FAILED(hr)) {
		return hr;
	}

	pclsObj->Release();
}


// Отобразить информацию о процессоре
HRESULT ControlWMI::ShowProcessor() {
	HRESULT hr;
	cout << "CPU Info" << endl;
	VARIANT vtProp;
	
	hr = GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"AddressWidth", &vtProp);
	if (!FAILED(hr)) {
		cout << "Разрядность: " << vtProp.intVal << endl;
	}
	
	hr = GetPropName((_bstr_t)"SELECT * FROM Win32_Processor", (_bstr_t)"AddressWidth", &vtProp);
	if (!FAILED(hr)) {
		cout << "Разрядность: " << vtProp.intVal << endl;
	}
		
	
	return S_OK;
}



// Деструктор.
ControlWMI::~ControlWMI() {
	pSvc->Release();
	pLoc->Release();
	CoUninitialize();
}





/*
// Отобразить информацию о процессоре
HRESULT ControlWMI::ShowProcessor() {
	// Указатель на обьект
	IWbemClassObject *pclsObj = NULL;
	HRESULT hr;

	// Передадим указатель на указатель.
	hr = GetProp((_bstr_t)"SELECT * FROM Win32_Processor", &pclsObj);

	if (FAILED(hr)) {
		return hr;
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

	return S_OK;

}

*/