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

// ��������� ���������� � ��������
struct PartitionInfo {
	
};

// ��������� ���������� � ������
struct DiskInfo {
	std::string Name;	// �������� 
	std::string Model;	// ������
	int64_t Size;	// �����
};

struct DISK_t {
	DiskInfo DISK_I[10];
	int count = 0;
};

// ��������� ���������� � ����������
struct KeyboardInfo {

};

// ��������� ���������� � ��������� �����
struct MBInfo {

};


// ��������� ���������� � ������������
struct MouseInfo {

};

// ��������� ���������� � ����������
struct VAInfo {

};

// ��������� ���������� � ��������
struct DisplayInfo {

};

// ��������� ���������� � ������� ���������
struct IfInfo {

};

// ��������� ���������� � ��������� �����������
struct APPInfo {

};



class SysInfo 
{
private:

	ControlWMI objWMI;

	// ��������� �������������� ���������
	CPUInfo CPU;
	BIOSInfo BIOS;
	DISK_t DISK;
	
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
	HRESULT PushMysqlDISK();

	// ��������� ������ �� WMI
	HRESULT CPUInfo();
	HRESULT BIOSInfo();
	HRESULT PartitionInfo();
	HRESULT DiskInfo();
	HRESULT KeyboardInfo();
	HRESULT MBInfo(); //
	HRESULT MouseInfo();//
	HRESULT VAInfo();//
	HRESULT DisplayInfo();//
	HRESULT IfInfo();//
	HRESULT AppInfo();
	  

	// ����������� ������ � stdout
	HRESULT ShowProcessor();
	HRESULT ShowBIOS();
	HRESULT ShowDISK();
	HRESULT ShowPartition();

};



#endif


