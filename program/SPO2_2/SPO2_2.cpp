#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#include <fstream>
#include <string>
#pragma comment(lib, "wbemuuid.lib")
/*
#pragma comment(lib,"mysqlcppconn-static.lib")
#pragma comment(lib,"mysqlcppconn.lib")


#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <ctime>
*/

#include "ControlWMI.h"
#include "SysInfo.h"


int main(int iArgCnt, char ** argv)
{
	// переходим в консоли на русский язык
	system("chcp 1251 > nul");
/*
	std::time_t t = std::time(0);  // t is an integer type

try {
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;


	driver = get_driver_instance();
	con = driver->connect("tcp://gtcoda.ru:3306", "oop", "3o4GAIQCHvPDPM6E");
	// Connect to the MySQL test database 
	con->setSchema("test");
	
	sql::PreparedStatement *prep_stmt;

	prep_stmt = con->prepareStatement("INSERT INTO test_table(test_char, time) VALUES (?, ?)");
	prep_stmt->setString(1, "a");
	prep_stmt->setInt64(2, t);
	prep_stmt->execute();

	std::string s = "sfdsdfsd";

	sql::SQLString sq = sql::SQLString(s.c_str());

	prep_stmt->setString(1,sq);
	prep_stmt->setInt64(2, t);
	prep_stmt->execute();

	delete prep_stmt;
	delete con;


}
catch (sql::SQLException &e) {
	cout << "# ERR: SQLException in " << __FILE__;
	cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
	cout << "# ERR: " << e.what();
	cout << " (MySQL error code: " << e.getErrorCode();
	cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}
*/

	// переходим в консоли на русский язык
	system("chcp 1251 > nul");
	SysInfo info;

	info.PushMysqlCPU();
//	SysInfo info;
	/*
	std::ofstream out("out.txt"); //откроем файл для вывод
	std::streambuf *coutbuf = std::cout.rdbuf(); //запомним старый буфер
	std::cout.rdbuf(out.rdbuf()); //и теперь все будет в файл out.txt!
	*/
	info.ShowProcessor();
	cout << "==================================" << endl;
	info.ShowBIOS();
	cout << "==================================" << endl;
	info.ShowDISK();
	cout << "==================================" << endl;
	info.ShowPartition();
	//std::cout.rdbuf(coutbuf); // востановить вывод

	system("pause");
	return 0;
}