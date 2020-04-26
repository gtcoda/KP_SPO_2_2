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
	std::string Name;	// ���
	std::string Arc;	// �����������
	int64_t AddressWidth;	// �����������
	int64_t MaxCS;			// ������������ ������� ����
	int64_t CurCS;			// ������� ������� ����
	int64_t BusS;			// ������� ����
	int64_t NCore;			// ���������� ����
	int64_t EnCore;			// ���������� �������� ����
	int64_t LogicCore;		// ���������� ���������� ����
	int64_t L2;				// ������ L2
	int64_t L3;				// ������ L3
};

struct BIOSInfo {
	std::string Name;	// ���
	std::string Arc;	// �����������
	
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


