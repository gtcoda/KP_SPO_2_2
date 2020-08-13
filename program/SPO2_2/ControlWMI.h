#ifndef ControlWMI_H
#define ControlWMI_H

#define _WIN32_DCOM

#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#include "comutil.h"

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
	static ControlWMI& Instance(){
		static ControlWMI theSingleInstance;
		return theSingleInstance;
	}
	ControlWMI();
	~ControlWMI();
	// Получение результирующего набора обьектов
	HRESULT Get(BSTR Query, IEnumWbemClassObject** pEnumerator);
};



#endif

