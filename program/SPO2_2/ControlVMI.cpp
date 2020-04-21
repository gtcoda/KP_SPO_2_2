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

HRESULT ControlWMI::Get(BSTR Query, IEnumWbemClassObject** pEnumerator) {
	HRESULT hr;

	// Обьект CIM
	hr = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(Query),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		pEnumerator);

	return hr;
}

// Деструктор.
ControlWMI::~ControlWMI() {
	pSvc->Release();
	pLoc->Release();
	CoUninitialize();
}