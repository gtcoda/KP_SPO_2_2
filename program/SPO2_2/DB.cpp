#include "DB.h"

// Конструктор
DBase::DBase() {
	// Проверка интернет соединения до хоста
	if (!InternetCheckConnectionW(HOST, FLAG_ICC_FORCE_CONNECTION, 0)) {
		STATUS = 1;
	}
	else {
		cout << HOST_BAD <<endl;
		STATUS = 0;
		return;
	}

	sql::PreparedStatement *prep_stmt;
	sql::Statement *stmt;
	sql::ResultSet *res;

	std::time_t t = std::time(0);

	driver = get_driver_instance();

	// Устанавливаем соединение с базой
	con = driver->connect(DB_HOST, DB_LOGIN, DB_PASSWORD);
	
	if (con == NULL) {
		cout << HOST_BAD << endl;
		STATUS = 0;
		return;
	}

	
	try {
	// Выбиаем рабочую БД
	con->setSchema(DB_BD);
	

	}
	catch (sql::SQLException &e) {
		STATUS = 0;
		cout << HOST_BAD << endl;
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode() << " )" << endl;
		return;
	}


	// Получим id текущего сеанса 
	prep_stmt = con->prepareStatement("INSERT INTO Manager(time) VALUES (?)");
	prep_stmt->setInt64(1, (long)t);
	prep_stmt->execute();

	delete prep_stmt;

	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT LAST_INSERT_ID ()");

	if (res->next()) {
		STATUS = 1;
		id = res->getInt(1);
	}
	else {
		STATUS = 0;
		cout << "Не получен ID!";
	}
	delete stmt;

}


HRESULT  DBase::GetConnector(sql::Connection **conget) {
	*conget = con;
	return S_OK;
}


int DBase::GetID(void) {
	return id;
}

