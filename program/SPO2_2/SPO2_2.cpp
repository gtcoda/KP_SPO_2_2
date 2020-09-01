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

#include "menu.h"

const char*  meni_main[] = {
								MENU_SHOW,
								MENU_PUSH_DB,
								MENU_PUSH_FILE,
								MENU_EXIT
};

const char* meni_points[] = {
				MENU_CPU,
				MENU_BIOS,
				MENU_PARTITION,
				MENU_HDD,
				MENU_BASEBOARD,
				MENU_KEYBOARD,
				MENU_MOUSE,
				MENU_VIDEO,
				MENU_MONITOR,
				MENU_NETWORK,
				MENU_PROCESS,
				MENU_UPTIME,
				MENU_USERS,
				MENU_ALL,
				MENU_EXIT
};

int main(int iArgCnt, char ** argv){	
	// переходим в консоли на русский язык
	system("chcp 65001 > nul");

	CPU CPUInf;
	USERS USERSInf;
	VIDEO VIDEOInf;
	UPTIME UPTIMEInf;
	BIOS BIOSInf;
	DISK DISKInf;
	PARTITION PARTITIONInf;
	KEYBOARD KEYBOARDInf;
	POINTER POINTERInf;
	NETWORK NETWORKInf;
	BASEBOARD BASEBOARDInf;
	MONITOR MONITORInf;
	PROCESS PROCESSInf;
	
	printf(VELCOM);

	int i = 0;
	while (1) {
		// ##############################
		// ##############################
		
		i = menu_horizont(COLUMN_LINE_MENU, MEMU_MAIN, meni_points, sizeof(meni_points) / sizeof(meni_points[0]),i);

		clear(COLUMN_LINE_MENU, MEMU_MAIN + 1);

		if (!strcmp(meni_points[i], MENU_ALL)) {
			CPUInf.Go();
			BIOSInf.Go();
			PARTITIONInf.Go();
			DISKInf.Go();
			BASEBOARDInf.Go();
			KEYBOARDInf.Go();
			POINTERInf.Go();
			VIDEOInf.Go();
			MONITORInf.Go();
			NETWORKInf.Go();
			PROCESSInf.Go();
			UPTIMEInf.Go();
			UPTIMEInf.Go();
			USERSInf.Go();
			continue;
		}
		if (!strcmp(meni_points[i], MENU_CPU)) {
			CPUInf.Go();
			continue;
		}
		else if (!strcmp(meni_points[i], MENU_BIOS) ) {
			BIOSInf.Go();
			continue;
		}
		else if (!strcmp(meni_points[i], MENU_PARTITION)) {
			PARTITIONInf.Go();
			continue;
		}
		else if (!strcmp(meni_points[i], MENU_HDD)) {
			DISKInf.Go();
			continue;
		}
		else if (!strcmp(meni_points[i], MENU_BASEBOARD)) {
			BASEBOARDInf.Go();
			continue;
		}
		else if (!strcmp(meni_points[i], MENU_KEYBOARD)) {
			KEYBOARDInf.Go();
			continue;
		}
		else if (!strcmp(meni_points[i], MENU_MOUSE)) {
			POINTERInf.Go();
			continue;
		}
		else if (!strcmp(meni_points[i], MENU_VIDEO)) {
			VIDEOInf.Go();
			continue;
		}
		else if (!strcmp(meni_points[i], MENU_MONITOR)) {
			MONITORInf.Go();
			continue;
		}
		else if (!strcmp(meni_points[i], MENU_NETWORK)) {
			NETWORKInf.Go();
			continue;
		}
		else if (!strcmp(meni_points[i], MENU_PROCESS)) {
			PROCESSInf.Go();
			continue;
		}
		else if (!strcmp(meni_points[i], MENU_UPTIME)) {
			UPTIMEInf.Go();
			continue;
		}
		else if (!strcmp(meni_points[i], MENU_USERS)) {
			USERSInf.Go();
			continue;
		}
		else if (!strcmp(meni_points[i], MENU_EXIT)) {
			break;
		}
	}

	system("pause");
	return 0;
}


