#include "DB.h"

// �����������
DBase::DBase() {
	sql::PreparedStatement *prep_stmt;
	sql::Statement *stmt;
	sql::ResultSet *res;

	std::time_t t = std::time(0);

	driver = get_driver_instance();
	// ������������� ���������� � �����
	con = driver->connect(DB_HOST, DB_LOGIN, DB_PASSWORD);

	// ������� ������� ��
	con->setSchema(DB_BD);
	// ������� id �������� ������ 
	prep_stmt = con->prepareStatement("INSERT INTO Manager(time) VALUES (?)");
	prep_stmt->setInt64(1, (long)t);
	prep_stmt->execute();

	delete prep_stmt;

	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT LAST_INSERT_ID ()");

	if (res->next()) {
		id = res->getInt(1);
	}
	else {
		cout << "�� ������� ID!";
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