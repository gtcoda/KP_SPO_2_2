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

// Структура информаци о CPU
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

// Структура информации о BIOS
struct BIOSInfo {
	std::string Version;	// Версия 
	std::string Caption;	// Подпись
	std::string Manufacturer;	// Производитель
};

// Структура информации о разделах
struct PartitionInfo {
	
};

// Структура информации о дисках
struct DiskInfo {
	std::string Name;	// Название 
	std::string Model;	// Модель
	int64_t Size;	// Обьем
};

struct DISK_t {
	DiskInfo DISK_I[10];
	int count = 0;
};

// Структура информации о клавиатуре
struct KeyboardInfo {

};

// Структура информации о системной плате
struct MBInfo {

};


// Структура информации о манипуляторе
struct MouseInfo {

};

// Структура информации о видеокарте
struct VAInfo {

};

// Структура информации о мониторе
struct DisplayInfo {

};

// Структура информации о сетевых адаптерах
struct IfInfo {

};

// Структура информации о запущеных приложениях
struct APPInfo {

};



class SysInfo 
{
private:

	ControlWMI objWMI;

	// Экземляры информационной структуры
	CPUInfo CPU;
	BIOSInfo BIOS;
	DISK_t DISK;
	
	//MySQL 
	sql::Driver *driver;
	sql::Connection *con;
	// Переменные для подключения
	sql::SQLString DB_HOST = "tcp://gtcoda.ru:3306";
	sql::SQLString DB_LOGIN = "oop";
	sql::SQLString DB_PASSWORD = "3o4GAIQCHvPDPM6E";
	sql::SQLString DB_BD = "test";
	int id = 0;



public:
	SysInfo();
	~SysInfo();
	// Отправка данных в БД MySQL
	HRESULT PushMysqlTest();
	HRESULT PushMysqlCPU();
	HRESULT PushMysqlBIOS();
	HRESULT PushMysqlDISK();

	// Получение данных из WMI
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
	  

	// Отображение данных в stdout
	HRESULT ShowProcessor();
	HRESULT ShowBIOS();
	HRESULT ShowDISK();
	HRESULT ShowPartition();

};



#endif


