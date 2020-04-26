#ifndef SysInfo_H
#define SysInfo_H

#define _WIN32_DCOM
using namespace std;
#include <iostream>
#include <iomanip>
#include <comdef.h>
#include <Wbemidl.h>
#include "ControlWMI.h"
#include "ConvertStr.h"

#pragma comment(lib, "wbemuuid.lib")
/*    MySQL connector 1.3   */
#pragma comment(lib,"mysqlcppconn-static.lib")
#pragma comment(lib,"mysqlcppconn.lib")
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <ctime>


struct CPUInfo {
	std::string Name;	// имя
	std::string Arc;	// Архитектура
	int64_t AddressWidth;	// Разрядность
	int64_t MaxCS;			// Максимальная частота ядра
	int64_t CurCS;			// Текущая частота ядра
	int64_t BusS;			// Частота шины
	int64_t NCore;			// Количество ядер
	int64_t EnCore;			// Количество активных ядер
	int64_t LogicCore;		// Количество логических ядер
	int64_t L2;				// Размер L2
	int64_t L3;				// Размер L3
};

struct BIOSInfo {
	std::string Name;	// имя
	std::string Arc;	// Архитектура
	
};







class SysInfo 
{
private:
	ControlWMI objWMI;

	CPUInfo CPU;


	//MySQL 
	sql::Driver *driver;
	sql::Connection *con;
	int id = 0;
	sql::SQLString DB_HOST = "tcp://gtcoda.ru:3306";
	sql::SQLString DB_LOGIN = "oop";
	sql::SQLString DB_PASSWORD = "3o4GAIQCHvPDPM6E";
	sql::SQLString DB_BD = "test";




public:
	SysInfo();
	~SysInfo();
	HRESULT PushMysqlTest();
	HRESULT PushMysqlCPU();

	HRESULT CPUInfo();
	   
	HRESULT ShowProcessor();
	HRESULT ShowBIOS();
	HRESULT ShowDISK();
	HRESULT ShowPartition();

};



#endif


