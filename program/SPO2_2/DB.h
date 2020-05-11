#ifndef DB_H
#define DB_H
/*
Соединение с БД
*/

#define _WIN32_DCOM
using namespace std;
#include <iostream>
#include <iomanip>
#include <comdef.h>
#include <Wbemidl.h>
#include <algorithm>
#include <vector>


/*    MySQL connector 1.3   */
#pragma comment(lib,"mysqlcppconn-static.lib")
#pragma comment(lib,"mysqlcppconn.lib")
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#pragma once
class DBase
{
public:

	

	static DBase& Instance()
	{
		static DBase theSingleInstance;
		return theSingleInstance;
	}

	// Получить соединение
	HRESULT GetConnector(sql::Connection **conget);
	// Получить id сессии
	int GetID(void);


private:

	//MySQL 
	sql::Driver *driver;
	sql::Connection *con;
	// Переменные для подключения
	sql::SQLString DB_HOST = "tcp://gtcoda.ru:3306";
	sql::SQLString DB_LOGIN = "oop";
	sql::SQLString DB_PASSWORD = "3o4GAIQCHvPDPM6E";
	sql::SQLString DB_BD = "test";
	int id;

	DBase();
	DBase(const DBase& root) = delete;
	DBase& operator=(const DBase&) = delete;
};



#endif