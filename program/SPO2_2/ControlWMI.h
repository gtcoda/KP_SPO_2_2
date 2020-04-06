#ifndef DB_H
#define DB_H

#define _WIN32_DCOM

#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

class ControlWMI // определение класса
{
private:
	IWbemServices * pSvc = NULL;
	IWbemLocator *pLoc = NULL;
	
public:
	ControlWMI();
	~ControlWMI();
	HRESULT GetClassFull(BSTR Query);
};



#endif

