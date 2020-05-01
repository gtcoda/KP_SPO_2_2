#ifndef SysInfo_H
#define SysInfo_H

#define _WIN32_DCOM
using namespace std;
#include <iostream>
#include <iomanip>
#include <comdef.h>
#include <Wbemidl.h>
#include <algorithm>
#include <vector>

#include "windows.h"

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
const int MAX_PROPERTY = 15;
// ������������ ���������� �����������
const int MAX_INSTANCE = 10;
// ������������ ���������� ������� � ���������
const int MAX_CLASS = 8;

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
	int Count;						// ���������� ���������� ���������
	info ATTR[MAX_INSTANCE][MAX_PROPERTY];
};

// ��������� ������ ������� ���������� ������� ��������� ���� ���������

struct WMIInfoManyClass {
	WMIInfo Info[MAX_CLASS]; //��������� ��� ������� ������
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
			{"Size", "������ [�]", ""},
			{"Model", "������", ""},
			{"Caption", "��������", ""}
		// ����� ������������� ���������� ������y�� info	
			} };

	WMIInfoMany DISK = {"���� �"};

// ���������� � partition

	WMIInfo PARTITION_I = {
		//WMI CLASS
			"Win32_LogicalDisk",
			"PARTITION_INFO",
			"PART",
			{
		// ������ ������������� ���������� ��������� info
			{"Size", "������ [�]", ""},
			{"FileSystem", "�������� �������", ""},
			{"FreeSpace", "��������� ����� [�]", ""},
			{"Caption", "��������", ""}
			// ����� ������������� ���������� ������y�� info	
				} };

	WMIInfoMany PARTITION = { "������ �" };


// ���������� � ����������

WMIInfo KEYBOARD_I = {
	//WMI CLASS
		"Win32_Keyboard",
		"KEYBOARD_INFO",
		"KEYBOARD",
		{
	// ������ ������������� ���������� ��������� info
		{"Description", "��������", ""},
		{"DeviceID", "������������� ����������", ""},
		{"Caption", "��������", ""},
		{"NumberOfFunctionKeys", "���-�� ��", ""}
		// ����� ������������� ���������� ������y�� info	
			} };

WMIInfoMany KEYBOARD = { "���������� �" };

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

	
	//���������� � ����������� �����
	WMIInfoManyClass BB = { {
			{// ������ ����� �� ������
				"Win32_BaseBoard",
				"BaseBoard_INFO",
				"BaseBoard",
				{// ������ ������������� ���������� ��������� info	
					{"Caption", "������������ ����������", ""},
					{"Description", "��������", ""},
					{"Manufacturer", "�������������", ""},
					{"Product", "���", ""},
					{"SerialNumber", "�������� �����", ""},
					{"Tag", "�������������", ""},
					{"Version", "������", ""}
				}// ����� ������������� ���������� ������y�� info	
			},
			{// ������ ����� �� ������
				"Win32_MotherboardDevice",
				"BaseBoard_INFO",
				"BaseBoard",
				{// ������ ������������� ���������� ��������� info	
					{"Caption", "������������ ����������", ""},
					{"Description", "��������", ""},
					{"SystemName ", "��� ����������", ""},
					{"DeviceID ", "�������������", ""},
					{"PrimaryBusType ", "��� ��������� ����", ""},
					{"SecondaryBusType ", "��� ��������� ����", ""},
				}// ����� ������������� ���������� ������y�� info	
			},
		{}

	} };



	WMIInfo BaseBoard = {
		//WMI CLASS
			"Win32_BaseBoard",
			"BaseBoard_INFO",
			"BaseBoard",
			{
		// ������ ������������� ���������� ��������� info	
			{"Caption", "������������ ����������", ""},
			{"Description", "��������", ""},
			{"Manufacturer", "�������������", ""},
			{"Product", "���", ""},
			{"SerialNumber", "�������� �����", ""},
			{"Tag", "�������������", ""},
			{"Version", "������", ""}
			// ����� ������������� ���������� ������y�� info	
			} };


	// ���������� � ����
	WMIInfo Pointer = {
		//WMI CLASS
			"Win32_PointingDevice",
			"Pointer_INFO",
			"Pointer",
			{
		// ������ ������������� ���������� ��������� info	
			{"Caption", "������������ ����������", ""},
			{"Description", "��������", ""},
			{"Manufacturer", "�������������", ""},
			{"HardwareType", "���", ""},
			{"DeviceID", "�������������", ""},
			{"DeviceInterface ", "��� ����������", ""},
			{"NumberOfButtons ", "���������� ������", ""}
			// ����� ������������� ���������� ������y�� info	
			} };


	// ������ � ����������
	std::vector <WMIInfo> Process;
	// �������� ���������� ����������
	WMIInfo Process_info = {
		//WMI CLASS
			"Win32_Process",
			"Process_INFO",
			"PROCESS",
			{
		// ������ ������������� ���������� ��������� info	
			{"Handle", "Id", ""},
			{"Name", "���", ""}
			
			// ����� ������������� ���������� ������y�� info	
			} };

	// ����� �������� ��
	WMIInfo START = {
		//WMI CLASS
			"Win32_OperatingSystem",
			"Start ��",
			"Start",
			{
		// ������ ������������� ���������� ��������� info	
			{"LastBootUpTime", "����� ��������� ��������", ""},
			{"LocalDateTime", "����� ��������� ��������", ""}
			// ����� ������������� ���������� ������y�� info	
			} };

	LONGLONG Uptime;
	WMIInfo UPTIME = {
		//WMI CLASS
			"",
			"����� ������ ��",
			"UPTIME",
			{
		// ������ ������������� ���������� ��������� info	
			{"Day", "����", ""},
			{"Hours", "�����", ""},
			{"Min", "�����", ""},
			{"Second", "������", ""},
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
	HRESULT WMIData(std::vector <WMIInfo> *data, WMIInfo * st);

	// ���������� ������ � stdout
	HRESULT ShowWMIdata(WMIInfo *data);
	HRESULT ShowWMIdata(WMIInfoMany *data);
	HRESULT ShowWMIdata(std::vector <WMIInfo> *data, WMIInfo * st);
	// ��������� ������ � MySQL
	HRESULT PushMysql(WMIInfo *data);
	HRESULT PushMysql(WMIInfoMany *data);
	HRESULT PushMysql(std::vector <WMIInfo> *data, WMIInfo * st);

	// ���������� ����� ������ �������
	HRESULT UpTime(WMIInfo *upt);
	HRESULT ShowUpTime(LONGLONG *uptime, WMIInfo *upt);

};





#endif


