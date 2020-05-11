#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#include <fstream>
#include <string>
#pragma comment(lib, "wbemuuid.lib")

#include "ControlWMI.h"
#include "SysInfo.h"


class InfoNetwork: public SysInfo {

public:
	HRESULT ShowWMIdata() {
		id;
		return S_OK;
	}
};



int main(int iArgCnt, char ** argv)
{
	// переходим в консоли на русский язык
	//system("chcp 65001 > nul");
	system("chcp 1251 > nul");


	// Экземпляр SysInfo
	SysInfo info;
	InfoNetwork infoNetworks;
	infoNetworks.ShowWMIdata();


	system("pause");
	return 0;
}


