#ifndef DB_H
#define DB_H

#define _WIN32_DCOM

#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")
struct ProcessorProp {
	BSTR Name;
	BSTR Value;
};



class ControlWMI // определение класса
{
private:
	IWbemServices * pSvc = NULL;
	IWbemLocator *pLoc = NULL;
	
public:
	ControlWMI();
	~ControlWMI();
	HRESULT ViewClassFull(BSTR Query);
	HRESULT GetProp(BSTR Query, IWbemClassObject **pclsObj);
	HRESULT GetPropName(BSTR Query, BSTR Name, VARIANT *vtProp);

	HRESULT ShowProcessor();
};



#endif

