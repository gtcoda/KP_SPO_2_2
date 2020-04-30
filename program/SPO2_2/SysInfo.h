#ifndef SysInfo_H
#define SysInfo_H

#define _WIN32_DCOM
using namespace std;
#include <iostream>
#include <iomanip>
#include <comdef.h>
#include <Wbemidl.h>
#include <algorithm>

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

// ������������ ���������� �������
//#define MAX_PROPERTY 15
const int MAX_PROPERTY = 15;
// ������������ ���������� �����������
//#define MAX_INSTANCE 10
const int MAX_INSTANCE = 10;

// ��������� ��������
struct info {
	std::string Property;	// �������� ��������
	std::string Name;		// �������� �������� �� ������
	std::string Value;		// �������� ��������
};

// ��������� ������ ������� ������ ��������� ���� ���������
struct WMIInfo {
	std::string WMIClass;		// �������� ������ WMI
	std::string Description;	// ��������
	std::string Table;			// ��� �������
	info ATTR[MAX_PROPERTY];
};

// ��������� ������ ������� ������ ��������� ��������� �����������
struct WMIInfoMany {
	std::string DescriptionIterator; // �������� ��������
	std::string WMIClass;
	std::string Description;
	std::string Table;			
	info ATTR[MAX_INSTANCE][MAX_PROPERTY];
};


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


// ��������� ���������� � ������
struct DiskInfo {
	std::string Name;	// �������� 
	std::string Model;	// ������
	int64_t Size;	// �����
};


class SysInfo 
{
private:

	ControlWMI objWMI;

	// ��������� �������������� ���������

// ���������� � BIOS	
	WMIInfo BIOS = {
	//WMI CLASS
		"Win32_BIOS",
		"BIOS_INFO",
		"BIOS",
		{
	// ������ ������������� ���������� ��������� info	
		{"Manufacturer", "�����������", ""},
		{"Version", "������", ""},
		{"Caption", "��������", ""}
	// ����� ������������� ���������� ������y�� info	
	}};

// ���������� � ������
	WMIInfo DISK_I = {
		//WMI CLASS
			"Win32_DiskDrive",
			"DISK_INFO",
			"DISK",
			{
		// ������ ������������� ���������� ��������� info
			{"Size", "������", ""},
			{"Model", "������", ""},
			{"Caption", "��������", ""}
		// ����� ������������� ���������� ������y�� info	
			} };

	WMIInfoMany DISK = {"���� �"};

//���������� � CPU
	WMIInfo CPU = {
		//WMI CLASS
			"Win32_Processor",
			"CPU_INFO",
			"CPU",
			{
		// ������ ������������� ���������� ��������� info	
			{"AddressWidth", "�����������", ""},
			{"Architecture", "�����������", ""},
			{"Name", "���", ""},
			{"MaxClockSpeed", "������������ �������", ""},
			{"CurrentClockSpeed", "������� �������", ""},
			{"ExtClock", "������� ����", ""},
			{"NumberOfCores", "���������� ����", ""},
			{"NumberOfEnabledCore", "���������� �������� ����", ""},
			{"NumberOfLogicalProcessors", "���������� ���������� ����", ""},
			{"L2CacheSize", "������ L2", ""},
			{"L3CacheSize", "������ L3", ""}
			// ����� ������������� ���������� ������y�� info	
			} };



	
	//MySQL 
	sql::Driver *driver;
	sql::Connection *con;
	// ���������� ��� �����������
	sql::SQLString DB_HOST = "tcp://gtcoda.ru:3306";
	sql::SQLString DB_LOGIN = "oop";
	sql::SQLString DB_PASSWORD = "3o4GAIQCHvPDPM6E";
	sql::SQLString DB_BD = "test";
	int id = 0;



	HRESULT ManyWMIInfo(WMIInfoMany *many, WMIInfo *one);


public:
	SysInfo();
	~SysInfo();
	// �������� ������ � �� MySQL
	HRESULT PushMysqlTest();


	// ��������� ������ �� WMI
	HRESULT WMIData(WMIInfo *data);
	HRESULT WMIData(WMIInfoMany *data);
	// ���������� ������ � stdout
	HRESULT ShowWMIdata(WMIInfo *data);
	HRESULT ShowWMIdata(WMIInfoMany *data);
	// ��������� ������ � MySQL
	HRESULT PushMysql(WMIInfo *data);
	HRESULT PushMysql(WMIInfoMany *data);

};



#endif


