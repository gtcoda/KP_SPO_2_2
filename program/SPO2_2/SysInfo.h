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

// Максимальное количество свойств
//#define MAX_PROPERTY 15
const int MAX_PROPERTY = 15;
// Максимальное количество экземпляров
//#define MAX_INSTANCE 10
const int MAX_INSTANCE = 10;

// Структура свойства
struct info {
	std::string Property;	// Название свойства
	std::string Name;		// Название свойства по русски
	std::string Value;		// Значение свойства
};

// Структура набора свойств класса отдающего один экземпляр
struct WMIInfo {
	std::string WMIClass;		// Название класса WMI
	std::string Description;	// Описание
	std::string Table;			// Имя таблицы
	info ATTR[MAX_PROPERTY];
};

// Структура набора свойств класса отдающего несколько экземпляров
struct WMIInfoMany {
	std::string DescriptionIterator; // Описание итерации
	std::string WMIClass;
	std::string Description;
	std::string Table;			
	info ATTR[MAX_INSTANCE][MAX_PROPERTY];
};


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


// Структура информации о дисках
struct DiskInfo {
	std::string Name;	// Название 
	std::string Model;	// Модель
	int64_t Size;	// Обьем
};


class SysInfo 
{
private:

	ControlWMI objWMI;

	// Экземляры информационной структуры

// Информация о BIOS	
	WMIInfo BIOS = {
	//WMI CLASS
		"Win32_BIOS",
		"BIOS_INFO",
		"BIOS",
		{
	// Начало инициализации внутренней структуры info	
		{"Manufacturer", "Произведено", ""},
		{"Version", "Версия", ""},
		{"Caption", "Название", ""}
	// Конец инициализации внутренней структyры info	
	}};

// Информация о дисках
	WMIInfo DISK_I = {
		//WMI CLASS
			"Win32_DiskDrive",
			"DISK_INFO",
			"DISK",
			{
		// Начало инициализации внутренней структуры info
			{"Size", "Размер", ""},
			{"Model", "Модель", ""},
			{"Caption", "Название", ""}
		// Конец инициализации внутренней структyры info	
			} };

	WMIInfoMany DISK = {"Диск №"};

//Информация о CPU
	WMIInfo CPU = {
		//WMI CLASS
			"Win32_Processor",
			"CPU_INFO",
			"CPU",
			{
		// Начало инициализации внутренней структуры info	
			{"AddressWidth", "Разрядность", ""},
			{"Architecture", "Архитектура", ""},
			{"Name", "Имя", ""},
			{"MaxClockSpeed", "Максимальная частота", ""},
			{"CurrentClockSpeed", "Текущая частота", ""},
			{"ExtClock", "Частота шины", ""},
			{"NumberOfCores", "Количество ядер", ""},
			{"NumberOfEnabledCore", "Количество активных ядер", ""},
			{"NumberOfLogicalProcessors", "Количество логических ядер", ""},
			{"L2CacheSize", "Размер L2", ""},
			{"L3CacheSize", "Размер L3", ""}
			// Конец инициализации внутренней структyры info	
			} };



	
	//MySQL 
	sql::Driver *driver;
	sql::Connection *con;
	// Переменные для подключения
	sql::SQLString DB_HOST = "tcp://gtcoda.ru:3306";
	sql::SQLString DB_LOGIN = "oop";
	sql::SQLString DB_PASSWORD = "3o4GAIQCHvPDPM6E";
	sql::SQLString DB_BD = "test";
	int id = 0;



	HRESULT ManyWMIInfo(WMIInfoMany *many, WMIInfo *one);


public:
	SysInfo();
	~SysInfo();
	// Отправка данных в БД MySQL
	HRESULT PushMysqlTest();


	// Получение данных из WMI
	HRESULT WMIData(WMIInfo *data);
	HRESULT WMIData(WMIInfoMany *data);
	// Отобразить данные в stdout
	HRESULT ShowWMIdata(WMIInfo *data);
	HRESULT ShowWMIdata(WMIInfoMany *data);
	// Отправить данные в MySQL
	HRESULT PushMysql(WMIInfo *data);
	HRESULT PushMysql(WMIInfoMany *data);

};



#endif


