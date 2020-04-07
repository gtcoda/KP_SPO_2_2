#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")

#include "ControlWMI.h"

int main(int iArgCnt, char ** argv)
{

	// переходим в консоли на русский язык
	system("chcp 1251 > nul");
	ControlWMI m;
	//m.ViewClassFull((_bstr_t)"SELECT * FROM Win32_Processor");
	m.ShowProcessor();
	

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
	return 0;
}