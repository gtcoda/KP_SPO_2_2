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
#include "PARTITION.h"
#include "KEYBOARD.h"
#include "POINTER.h"
#include "NETWORK.h"
#include "BASEBOARD.h"
#include "MONITOR.h"
#include "PROCESS.h"
#include "UPTIME.h"
#include "VIDEO.h"
#include "USERS.h"


int main(int iArgCnt, char ** argv){	
	// переходим в консоли на русский язык
	system("chcp 65001 > nul");


	USERS USERSInf;
	USERSInf.Go();

	VIDEO VIDEOInf;
	VIDEOInf.Go();


	UPTIME UPTIMEInf;
	UPTIMEInf.Go();

	CPU CPUInf;
	CPUInf.Go();

	BIOS BIOSInf;
	BIOSInf.Go();

	DISK DISKInf;
	DISKInf.Go();
	
	PARTITION PARTITIONInf;
	PARTITIONInf.Go();

	KEYBOARD KEYBOARDInf;
	KEYBOARDInf.Go();

	POINTER POINTERInf;
	POINTERInf.Go();

	NETWORK NETWORKInf;
	NETWORKInf.Go();

	BASEBOARD BASEBOARDInf;
	BASEBOARDInf.Go();

	MONITOR MONITORInf;
	MONITORInf.Go();

	PROCESS PROCESSInf;
	PROCESSInf.Go();

	system("pause");
	return 0;
}


