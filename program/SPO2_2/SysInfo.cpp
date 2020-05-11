#include "SysInfo.h"

// Конструктор
SysInfo::SysInfo() {
	sql::PreparedStatement *prep_stmt;
	sql::Statement *stmt;
	sql::ResultSet *res;

	std::time_t t = std::time(0);

	driver = get_driver_instance();
	// Устанавливаем соединение с базой
	con = driver->connect(DB_HOST, DB_LOGIN, DB_PASSWORD);

	// Выбиаем рабочую БД
	con->setSchema(DB_BD);
	// Получим id текущего сеанса 
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
		cout << "Íå ïîëó÷åí ID!";
	}
	delete stmt;

	
	Info(&BIOS);
	/*
	Info(&CPU);
	Info(&DISK, &DISK_I);
	Info(&PARTITION, &PARTITION_I);
	Info(&KEYBOARD, &KEYBOARD_I);
	Info(&BaseBoard);
	Info(&DesktopMonitor, &DesktopMonitor_I);


	ManyWMIInfo(&NetworkAdapter, &NetworkAdapter_I);
	ManyWMIInfo(&NetworkAdapterConfiguration, &NetworkAdapterConfiguration_I);

	WMIInfoManyClassManyObject Networks = { NetworkAdapter, NetworkAdapterConfiguration };

	WMIData(&Networks);
	ShowWMIdata(&Networks);
	
	// Uptime
	UpTime(&UPTIME);
	ShowWMIdata(&UPTIME);
	PushMysql(&UPTIME);



	Info(&Process, &Process_info);

	*/

}


SysInfo::~SysInfo() {
	delete con;
}


HRESULT SysInfo::Info(WMIInfo *data) {
	WMIData(data);
	ShowWMIdata(data);
	PushMysql(data);
	return S_OK;
}

HRESULT SysInfo::Info(WMIInfoMany *data, WMIInfo *data_i) {
	ManyWMIInfo(data, data_i);
	WMIData(data);
	ShowWMIdata(data);
	PushMysql(data);
	return S_OK;

}

HRESULT SysInfo::Info(std::vector <WMIInfo> *data, WMIInfo *st) {
	WMIData(data, st);
	ShowWMIdata(data, st);
	PushMysql(data, st);
	return S_OK;
}

// Заполнение структуры WMIInfoMany из WMIInfo
HRESULT SysInfo::ManyWMIInfo(WMIInfoMany *many, WMIInfo *one) {
	many->Description = one->Description;
	many->WMIClass = one->WMIClass;
	many->Table = one->Table;

	for (int n = 0; n < MAX_INSTANCE; n++) {
		for (int i = 0; (i < MAX_PROPERTY) & (one->ATTR[i].Name != ""); i++) {
			many->ATTR[n][i] = one->ATTR[i];
		}
	}

	return S_OK;
}



HRESULT SysInfo::PushMysqlTest() {
	sql::PreparedStatement *prep_stmt;

	prep_stmt = con->prepareStatement("INSERT INTO test_table(test_char, time) VALUES (?, ?)");
	prep_stmt->setString(1, "a");
	prep_stmt->setInt64(2, 132132141);
	prep_stmt->execute();

	delete prep_stmt;

	return S_OK;
}
/*===================== Отправка в БД =====================*/
HRESULT SysInfo::PushMysql(WMIInfo *data) {

	try {

		sql::PreparedStatement *prep_stmt;

		std::string sql;
		sql = "INSERT INTO " + data->Table + "(";
		sql += "id,";
		for (int i = 0; (i < MAX_PROPERTY) & (data->ATTR[i].Name != ""); i++) {
			sql += data->ATTR[i].Property + ",";
		}
		// Удалим лишнюю запятую
		if (sql.size() > 0)  sql.resize(sql.size() - 1);

		sql += ") VALUES(?,";

		for (int i = 0; (i < MAX_PROPERTY) & (data->ATTR[i].Name != ""); i++) {
			sql += "?,";
		}
		// Удалим лишнюю запятую
		if (sql.size() > 0)  sql.resize(sql.size() - 1);

		sql += ")";


		prep_stmt = con->prepareStatement(sql::SQLString(sql.c_str()));
		prep_stmt->setInt64(1, id);
		for (int i = 0; (i < MAX_PROPERTY) & (data->ATTR[i].Name != ""); i++) {
			prep_stmt->setString(i + 2, sql::SQLString( cp1251_to_utf8(data->ATTR[i].Value.c_str()).c_str() ));
		}

		prep_stmt->execute();

		delete prep_stmt;

	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode() << " )" << endl;
	}

	return S_OK;

}

HRESULT SysInfo::PushMysql(WMIInfoMany *data) {

	try {

		for (int i = 0; (i < MAX_INSTANCE) & (data->ATTR[i][0].Value != ""); i++) {

			sql::PreparedStatement *prep_stmt;

			std::string sql;
			sql = "INSERT INTO " + data->Table + "(";
			sql += "id,";
			for (int n = 0; (n < MAX_PROPERTY) & (data->ATTR[i][n].Name != ""); n++) {
				sql += data->ATTR[i][n].Property + ",";
			}
			// Удалим лишнюю запятую
			if (sql.size() > 0)  sql.resize(sql.size() - 1);

			sql += ") VALUES(?,";

			for (int n = 0; (n < MAX_PROPERTY) & (data->ATTR[i][n].Name != ""); n++) {
				sql += "?,";
			}
			// Удалим лишнюю запятую
			if (sql.size() > 0)  sql.resize(sql.size() - 1);

			sql += ")";


			prep_stmt = con->prepareStatement(sql::SQLString(sql.c_str()));
			prep_stmt->setInt64(1, id);
			for (int n = 0; (n < MAX_PROPERTY) & (data->ATTR[i][n].Name != ""); n++) {
				prep_stmt->setString(n + 2, sql::SQLString( cp1251_to_utf8( data->ATTR[i][n].Value.c_str()).c_str() ));
			}

			prep_stmt->execute();

			delete prep_stmt;


		}


	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode() << " )" << endl;
	}

	return S_OK;

}

HRESULT SysInfo::PushMysql(std::vector <WMIInfo> *data, WMIInfo * st) {

	try {



		sql::PreparedStatement *prep_stmt;
		std::string sql;
		sql = "INSERT INTO " + st->Table + "(";
		sql += "id,";
		for (int i = 0; (i < MAX_PROPERTY) & (st->ATTR[i].Name != ""); i++) {
			sql += st->ATTR[i].Property + ",";
		}
		// Удалим лишнюю запятую
		if (sql.size() > 0)  sql.resize(sql.size() - 1);

		sql += ") VALUES(?,";

		for (int i = 0; (i < MAX_PROPERTY) & (st->ATTR[i].Name != ""); i++) {
			sql += "?,";
		}
		// Удалим лишнюю запятую
		if (sql.size() > 0)  sql.resize(sql.size() - 1);

		sql += ")";

		for (WMIInfo inf : *data) {
			prep_stmt = con->prepareStatement(sql::SQLString(sql.c_str()));
			prep_stmt->setInt64(1, id);
			for (int i = 0; (i < MAX_PROPERTY) & (inf.ATTR[i].Name != ""); i++) {
				prep_stmt->setString(i + 2, sql::SQLString(inf.ATTR[i].Value.c_str()));
			}

			prep_stmt->execute();
			cout << "*";
		}





	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode() << " )" << endl;
	}

	return S_OK;





}

/*===================== Получение информации =====================*/

// Получение информации из WMI один экземпляр
HRESULT SysInfo::WMIData(WMIInfo *data) {
	HRESULT hr;
	IEnumWbemClassObject * pEnumerator = NULL;

	std::string q = "SELECT * FROM " + data->WMIClass;
	objWMI.Get((_bstr_t)ConvertMBSToBSTR(q), &pEnumerator);

	hr = WBEM_S_NO_ERROR;
	// Final Next will return WBEM_S_FALSE
	while (WBEM_S_NO_ERROR == hr)
	{
		ULONG            uReturned;
		IWbemClassObject*    apObj[10];

		hr = pEnumerator->Next(WBEM_INFINITE, 10, apObj, &uReturned);

		if (SUCCEEDED(hr)) {
			// Перебираем обьекты
			for (ULONG i = 0; i < uReturned; i++) {


				// Перебираем свойства
				for (ULONG n = 0; (n < MAX_PROPERTY) & (data->ATTR[n].Name != ""); n++) {
					VARIANT vtProp;
					HRESULT hro;
					_bstr_t prName = ConvertMBSToBSTR(data->ATTR[n].Property);
					hro = apObj[i]->Get(prName, 0, &vtProp, 0, 0);
					if (!FAILED(hro)) {
						// Преобразуем ответ в строку
						hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
						data->ATTR[n].Value =  (ConvertBSTRToMBS(vtProp.bstrVal));
					}


				}


				apObj[i]->Release();
			}

		}
	}

	return S_OK;

}

// Получение информации из WMI несколько экземпляров
HRESULT SysInfo::WMIData(WMIInfoMany *data) {
	HRESULT hr;
	IEnumWbemClassObject * pEnumerator = NULL;

	std::string q = "SELECT * FROM " + data->WMIClass;

	objWMI.Get((_bstr_t)ConvertMBSToBSTR(q), &pEnumerator);

	hr = WBEM_S_NO_ERROR;
	// Final Next will return WBEM_S_FALSE
	while (WBEM_S_NO_ERROR == hr)
	{
		ULONG            uReturned;
		IWbemClassObject*    apObj[10];

		hr = pEnumerator->Next(WBEM_INFINITE, 10, apObj, &uReturned);

		if (SUCCEEDED(hr)) {
			// Перебираем обьекты
			for (ULONG i = 0; i < uReturned; i++) {


				// Перебираем свойства
				for (ULONG n = 0; (n < MAX_PROPERTY) & (data->ATTR[i][n].Name != ""); n++) {
					VARIANT vtProp;
					HRESULT hro;
					_bstr_t prName = ConvertMBSToBSTR(data->ATTR[i][n].Property);
					hro = apObj[i]->Get(prName, 0, &vtProp, 0, 0);
					if (!FAILED(hro)) {
						// Преобразуем ответ в строку
						hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
						data->ATTR[i][n].Value = ConvertBSTRToMBS(vtProp.bstrVal);
					}
				}
				apObj[i]->Release();
				data->Count++;
			}

		}
	}

	return S_OK;

}


// Получение информации из WMI множества экземпляров
HRESULT SysInfo::WMIData(std::vector <WMIInfo> *data, WMIInfo *st) {
	HRESULT hr;
	int count = 0;
	WMIInfo res;
	IEnumWbemClassObject * pEnumerator = NULL;

	std::string q = "SELECT * FROM " + st->WMIClass;

	objWMI.Get((_bstr_t)ConvertMBSToBSTR(q), &pEnumerator);

	hr = WBEM_S_NO_ERROR;
	// Final Next will return WBEM_S_FALSE
	while (WBEM_S_NO_ERROR == hr)
	{
		ULONG            uReturned;
		IWbemClassObject*    apObj[10];

		hr = pEnumerator->Next(WBEM_INFINITE, 10, apObj, &uReturned);

		if (SUCCEEDED(hr)) {
			// Перебираем объекты
			for (ULONG i = 0; i < uReturned; i++) {

				data->push_back(res);


				// перебираем свойства
				for (ULONG n = 0; (n < MAX_PROPERTY) & (st->ATTR[n].Property != ""); n++) {
					VARIANT vtProp;
					HRESULT hro;
					_bstr_t prName = ConvertMBSToBSTR(st->ATTR[n].Property);


					hro = apObj[i]->Get(prName, 0, &vtProp, 0, 0);
					if (!FAILED(hro)) {
						// Преобразуем ответ в строку
						hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);



						data->at(count).ATTR[n].Name = st->ATTR[n].Name;
						data->at(count).ATTR[n].Property = st->ATTR[n].Property;
						data->at(count).ATTR[n].Value = ConvertBSTRToMBS(vtProp.bstrVal);

					}
				}
				apObj[i]->Release();
				count++;
			}

		}
	}

	return S_OK;

}

// Получение информации из WMI несколько экземпляров
HRESULT SysInfo::WMIData(WMIInfoManyClassManyObject *data) {
	for (int i = 0; i< MAX_CLASS; i++)
	{
		WMIData(&data->Inf[i]);
	}
	return S_OK;
}
/*===================== Отображение информации =====================*/
HRESULT SysInfo::ShowWMIdata(WMIInfo *data) {
	cout << endl;
	cout << "=======    " << utf8_to_cp1251(data->Description.c_str()) << "   =======" << endl;

	for (ULONG n = 0; (n < MAX_PROPERTY) & (data->ATTR[n].Name != ""); n++) {
		if (data->ATTR[n].Value == "") { continue; }
		cout << utf8_to_cp1251( data->ATTR[n].Name.c_str()) << ": " << data->ATTR[n].Value << ";" << endl;
	}

	return S_OK;
}


HRESULT SysInfo::ShowWMIdata(WMIInfoMany *data) {
	cout << endl;
	cout << "=======    " << utf8_to_cp1251(data->Description.c_str()) << "   =======" << endl;
	for (int i = 0; (i < MAX_INSTANCE) & (data->ATTR[i][0].Value != ""); i++) {

		cout << utf8_to_cp1251(data->DescriptionIterator.c_str()) << " " << i << endl;

		for (int n = 0; (n < MAX_PROPERTY) & (data->ATTR[i][n].Name != ""); n++) {
			if (data->ATTR[i][n].Value == "") { continue; }
			cout << utf8_to_cp1251( data->ATTR[i][n].Name.c_str()) << ": " << data->ATTR[i][n].Value << ";" << endl;
		}
		cout << endl;

	}
	return S_OK;
}


HRESULT SysInfo::ShowWMIdata(std::vector <WMIInfo> *data, WMIInfo *st) {
	cout << endl;
	cout << "=======    " << utf8_to_cp1251(st->Description.c_str()) << "   =======" << endl;


	for (WMIInfo inf : *data) {
		inf.ATTR;
		std::string str = "";

		for (int n = 0; (n < MAX_PROPERTY) & (inf.ATTR[n].Name != ""); n++) {
			str += inf.ATTR[n].Value;
			str += "\t";
		}
		str.erase(str.length() - 1, 1);

		str += ";";

		cout << utf8_to_cp1251(str.c_str()) << endl;
	}





	return S_OK;
}

HRESULT  SysInfo::UpTime(WMIInfo *upt) {
	LONGLONG uptime = GetTickCount64();

	const long day_t = 1000 * 60 * 60 * 24;
	const long hours_t = 1000 * 60 * 60;
	const long min_t = 1000 * 60;
	const long second_t = 1000;

	int64_t day = uptime / day_t;
	uptime = uptime % day_t;

	int64_t hours = uptime / hours_t;
	uptime = uptime % hours_t;

	int64_t min = uptime / min_t;
	uptime = uptime % min_t;

	int64_t second = uptime / second_t;
	uptime = uptime % second_t;

	for (int i = 0; i < MAX_PROPERTY; i++) {
		if (upt->ATTR[i].Property == "Day") {
			upt->ATTR[i].Value = to_string(day);
			continue;
		}
		if (upt->ATTR[i].Property == "Hours") {
			upt->ATTR[i].Value = to_string(hours);
			continue;
		}
		if (upt->ATTR[i].Property == "Min") {
			upt->ATTR[i].Value = to_string(min);
			continue;
		}
		if (upt->ATTR[i].Property == "Second") {
			upt->ATTR[i].Value = to_string(second);
			continue;
		}
	}


	return S_OK;
}


HRESULT SysInfo::ShowWMIdata(WMIInfoManyClassManyObject *data) {

	info ATTR[25];




	
		// Прохожим по всем экземпляром
		for (int i = 0; i < MAX_INSTANCE; i++) {
		
			// Пройдем по экземпляру каждого класса
			for (int n = 0; n < MAX_CLASS; n++ ) {
			
				for (int m = 0; m < 25; m++) {
					ATTR[m].Name = data->Inf[i].ATTR[n]->Name;
					ATTR[m].Property = data->Inf[i].ATTR[n]->Property;
					ATTR[m].Value = data->Inf[i].ATTR[n]->Value;
				}
			}

		}




	return S_OK;
}

/*
	cout << "UpTime: " << day << "d " << hours << "h " << min << "m " << second << "s;"  << endl  ;
*/