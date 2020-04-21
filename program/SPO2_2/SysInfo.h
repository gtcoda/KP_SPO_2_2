#ifndef SysInfo_H
#define SysInfo_H

#define _WIN32_DCOM
using namespace std;
#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>
#include "ControlWMI.h"

#pragma comment(lib, "wbemuuid.lib")

class SysInfo 
{
private:
	ControlWMI objWMI;
public:
	HRESULT ShowProcessor();
	HRESULT ShowBIOS();
	HRESULT ShowDISK();
};



#endif


