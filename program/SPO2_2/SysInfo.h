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

// ��������� ��������� � CPU
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

// ��������� ���������� � BIOS
struct BIOSInfo {
	std::string Version;	// ������ 
	std::string Caption;	// �������
	std::string Manufacturer;	// �������������
};


class SysInfo 
{
private:

	ControlWMI objWMI;

	// ��������� �������������� ���������
	CPUInfo CPU;
	BIOSInfo BIOS;
	
	//MySQL 
	sql::Driver *driver;
	sql::Connection *con;
	// ���������� ��� �����������
	sql::SQLString DB_HOST = "tcp://gtcoda.ru:3306";
	sql::SQLString DB_LOGIN = "oop";
	sql::SQLString DB_PASSWORD = "3o4GAIQCHvPDPM6E";
	sql::SQLString DB_BD = "test";
	int id = 0;



public:
	SysInfo();
	~SysInfo();
	// �������� ������ � �� MySQL
	HRESULT PushMysqlTest();
	HRESULT PushMysqlCPU();
	HRESULT PushMysqlBIOS();

	// ��������� ������ �� WMI
	HRESULT CPUInfo();
	HRESULT BIOSInfo();
	

	// ����������� ������ � stdout
	HRESULT ShowProcessor();
	HRESULT ShowBIOS();
	HRESULT ShowDISK();
	HRESULT ShowPartition();

};



#endif


