#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#include <fstream>
#include <string>
#pragma comment(lib, "wbemuuid.lib")

#include "DB.h"

#include "CPU.h"
#include "BIOS.h"
#include "DISK.h"



int main(int iArgCnt, char ** argv)
{
	// переходим в консоли на русский язык
	//system("chcp 65001 > nul");
	system("chcp 1251 > nul");

	CPU CPUInf;
	CPUInf.Go();

	BIOS BIOSInf;
	BIOSInf.Go();

	DISK DISKInf;
	DISKInf.Go();

	system("pause");
	return 0;
}


