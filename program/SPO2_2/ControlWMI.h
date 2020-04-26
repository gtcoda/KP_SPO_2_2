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



class ControlWMI // ����������� ������
{
private:
	IWbemServices * pSvc = NULL;
	IWbemLocator *pLoc = NULL;

public:
	ControlWMI();
	~ControlWMI();

	// ��������� ��������������� ������ ��������
	HRESULT Get(BSTR Query, IEnumWbemClassObject** pEnumerator);

};



#endif

