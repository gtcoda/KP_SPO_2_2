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


int main(int iArgCnt, char ** argv)
{
	// переходим в консоли на русский язык
	system("chcp 1251 > nul");
	
	// Экземпляр SysInfo
	SysInfo info;

	// Отправим в БД
	info.PushMysqlCPU();
	info.PushMysqlBIOS();
	info.PushMysqlDISK();

	// Отобразим в stdout
	info.ShowProcessor();
	cout << "==================================" << endl;
	info.ShowBIOS();
	cout << "==================================" << endl;
	info.ShowDISK();
	cout << "==================================" << endl;
	info.ShowPartition();
	cout << "==================================" << endl;
	info.ShowKeyboard();
	system("pause");
	return 0;
}