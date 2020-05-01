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

// Максимальное количество свойств
const int MAX_PROPERTY = 15;
// Максимальное количество экземпляров
const int MAX_INSTANCE = 10;
// Максимальное количество классов в структуре
const int MAX_CLASS = 8;

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
	int Count;						// Количество заполненых элементов
	info ATTR[MAX_INSTANCE][MAX_PROPERTY];
};

// Структура набора свойств нескольких классов отдающего один экземпляр

struct WMIInfoManyClass {
	WMIInfo Info[MAX_CLASS]; //Структуры для каждого класса
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
			{"Size", "Размер [б]", ""},
			{"Model", "Модель", ""},
			{"Caption", "Название", ""}
		// Конец инициализации внутренней структyры info	
			} };

	WMIInfoMany DISK = {"Диск №"};

// Информация о partition

	WMIInfo PARTITION_I = {
		//WMI CLASS
			"Win32_LogicalDisk",
			"PARTITION_INFO",
			"PART",
			{
		// Начало инициализации внутренней структуры info
			{"Size", "Размер [б]", ""},
			{"FileSystem", "Файловая система", ""},
			{"FreeSpace", "Свободный обьем [б]", ""},
			{"Caption", "Название", ""}
			// Конец инициализации внутренней структyры info	
				} };

	WMIInfoMany PARTITION = { "Раздел №" };


// Информация о клавиатуре

WMIInfo KEYBOARD_I = {
	//WMI CLASS
		"Win32_Keyboard",
		"KEYBOARD_INFO",
		"KEYBOARD",
		{
	// Начало инициализации внутренней структуры info
		{"Description", "Описание", ""},
		{"DeviceID", "Идентификатор устройства", ""},
		{"Caption", "Название", ""},
		{"NumberOfFunctionKeys", "Кол-во ФК", ""}
		// Конец инициализации внутренней структyры info	
			} };

WMIInfoMany KEYBOARD = { "Клавиатура №" };

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

	
	//Информация о Материнской Плате
	WMIInfoManyClass BB = { {
			{// Первый класс на разбор
				"Win32_BaseBoard",
				"BaseBoard_INFO",
				"BaseBoard",
				{// Начало инициализации внутренней структуры info	
					{"Caption", "Наименование Устройства", ""},
					{"Description", "Описание", ""},
					{"Manufacturer", "Производитель", ""},
					{"Product", "Тип", ""},
					{"SerialNumber", "Серийный номер", ""},
					{"Tag", "Идентификатор", ""},
					{"Version", "Версия", ""}
				}// Конец инициализации внутренней структyры info	
			},
			{// Второй класс на разбор
				"Win32_MotherboardDevice",
				"BaseBoard_INFO",
				"BaseBoard",
				{// Начало инициализации внутренней структуры info	
					{"Caption", "Наименование Устройства", ""},
					{"Description", "Описание", ""},
					{"SystemName ", "Имя компьютера", ""},
					{"DeviceID ", "Идентификатор", ""},
					{"PrimaryBusType ", "Тип первичной шины", ""},
					{"SecondaryBusType ", "Тип вторичной шины", ""},
				}// Конец инициализации внутренней структyры info	
			},
		{}

	} };



	WMIInfo BaseBoard = {
		//WMI CLASS
			"Win32_BaseBoard",
			"BaseBoard_INFO",
			"BaseBoard",
			{
		// Начало инициализации внутренней структуры info	
			{"Caption", "Наименование Устройства", ""},
			{"Description", "Описание", ""},
			{"Manufacturer", "Производитель", ""},
			{"Product", "Тип", ""},
			{"SerialNumber", "Серийный номер", ""},
			{"Tag", "Идентификатор", ""},
			{"Version", "Версия", ""}
			// Конец инициализации внутренней структyры info	
			} };


	// Информация о мыши
	WMIInfo Pointer = {
		//WMI CLASS
			"Win32_PointingDevice",
			"Pointer_INFO",
			"Pointer",
			{
		// Начало инициализации внутренней структуры info	
			{"Caption", "Наименование Устройства", ""},
			{"Description", "Описание", ""},
			{"Manufacturer", "Производитель", ""},
			{"HardwareType", "Тип", ""},
			{"DeviceID", "Идентификатор", ""},
			{"DeviceInterface ", "Тип интерфейса", ""},
			{"NumberOfButtons ", "Количество кнопок", ""}
			// Конец инициализации внутренней структyры info	
			} };


	// Работа с процессами
	std::vector <WMIInfo> Process;
	// Описание получаемых параметров
	WMIInfo Process_info = {
		//WMI CLASS
			"Win32_Process",
			"Process_INFO",
			"PROCESS",
			{
		// Начало инициализации внутренней структуры info	
			{"Handle", "Id", ""},
			{"Name", "Имя", ""}
			
			// Конец инициализации внутренней структyры info	
			} };

	// Время загрузки ОС
	WMIInfo START = {
		//WMI CLASS
			"Win32_OperatingSystem",
			"Start ОС",
			"Start",
			{
		// Начало инициализации внутренней структуры info	
			{"LastBootUpTime", "Время последней загрузки", ""},
			{"LocalDateTime", "Время последней загрузки", ""}
			// Конец инициализации внутренней структyры info	
			} };

	LONGLONG Uptime;
	WMIInfo UPTIME = {
		//WMI CLASS
			"",
			"Время работы ОС",
			"UPTIME",
			{
		// Начало инициализации внутренней структуры info	
			{"Day", "Дней", ""},
			{"Hours", "Часов", ""},
			{"Min", "Минут", ""},
			{"Second", "Секунд", ""},
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
	HRESULT WMIData(std::vector <WMIInfo> *data, WMIInfo * st);

	// Отобразить данные в stdout
	HRESULT ShowWMIdata(WMIInfo *data);
	HRESULT ShowWMIdata(WMIInfoMany *data);
	HRESULT ShowWMIdata(std::vector <WMIInfo> *data, WMIInfo * st);
	// Отправить данные в MySQL
	HRESULT PushMysql(WMIInfo *data);
	HRESULT PushMysql(WMIInfoMany *data);
	HRESULT PushMysql(std::vector <WMIInfo> *data, WMIInfo * st);

	// Возвращает время работы системы
	HRESULT UpTime(WMIInfo *upt);
	HRESULT ShowUpTime(LONGLONG *uptime, WMIInfo *upt);

};





#endif


