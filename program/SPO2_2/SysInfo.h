#ifndef SysInfo_H
#define SysInfo_H

#define _WIN32_DCOM
using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>
#include <comdef.h>
#include <Wbemidl.h>
#include <algorithm>
#include <vector>
#include <string>

#include "windows.h"

#include "ControlWMI.h"
#include "ConvertStr.h"
#include "OutXML.h"

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

#include "DB.h"




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


// Структура набора свойств нескольких классов отдающего несколько экземпляров
struct WMIInfoManyClassManyObject {
	WMIInfoMany Inf[MAX_CLASS]; //Структуры для каждого класса
};

class SysInfo 
{
private:

	ControlWMI& objWMI = ControlWMI::Instance();

	//MySQL 
	sql::Connection *con;
		   
	OutXML& OXML = OutXML::Instance();


public:
	int id = 0;

	SysInfo();
	~SysInfo();

	// Go
	HRESULT Info(WMIInfo *data);
	HRESULT Info(WMIInfoMany *data, WMIInfo *data_i);
	HRESULT Info(std::vector <WMIInfo> *data, WMIInfo *st);

	// Получение данных из WMI
	HRESULT WMIData(WMIInfo *data);
	HRESULT WMIData(WMIInfoMany *data);
	HRESULT WMIData(std::vector <WMIInfo> *data, WMIInfo * st);
	HRESULT WMIData(WMIInfoManyClassManyObject *data);

	// Отобразить данные в stdout
	HRESULT ShowWMIdata(WMIInfo *data);
	HRESULT ShowWMIdata(WMIInfoMany *data);
	HRESULT ShowWMIdata(std::vector <WMIInfo> *data, WMIInfo * st);
	HRESULT ShowWMIdata(WMIInfoManyClassManyObject *data);

	// Записать данные в файл в формате XML
	HRESULT OutWMIdata(WMIInfo *data);
	HRESULT OutWMIdata(WMIInfoMany *data);
	HRESULT OutWMIdata(std::vector <WMIInfo> *data, WMIInfo * st);
	HRESULT OutWMIdata(WMIInfoManyClassManyObject *data);

	// Отправить данные в MySQL
	HRESULT PushMysql(WMIInfo *data);
	HRESULT PushMysql(WMIInfoMany *data);
	HRESULT PushMysql(std::vector <WMIInfo> *data, WMIInfo * st);


	HRESULT ManyWMIInfo(WMIInfoMany *many, WMIInfo *one);
	HRESULT WMIDataExtruder(string * str,VARIANT * vtProp);
};





#endif


