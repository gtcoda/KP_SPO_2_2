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
	SysInfo info;
	/*
	std::ofstream out("out.txt"); //откроем файл для вывод
	std::streambuf *coutbuf = std::cout.rdbuf(); //запомним старый буфер
	std::cout.rdbuf(out.rdbuf()); //и теперь все будет в файл out.txt!
	*/
	info.ShowProcessor();
	
	//std::cout.rdbuf(coutbuf); // востановить вывод

	return 0;
}