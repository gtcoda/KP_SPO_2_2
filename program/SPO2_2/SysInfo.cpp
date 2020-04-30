#include "SysInfo.h"

// Конструктор
SysInfo::SysInfo(){
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
		cout << "Не получен ID!";
	}
	delete stmt;


	// BIOS
	WMIData(&BIOS);
	ShowWMIdata(&BIOS);
	PushMysql(&BIOS);

	// CPU
	WMIData(&CPU);
	ShowWMIdata(&CPU);
	PushMysql(&CPU);

	// DISK
	ManyWMIInfo(&DISK, &DISK_I);
	WMIData(&DISK);
	ShowWMIdata(&DISK);
	PushMysql(&DISK);


	// PARTITION
	ManyWMIInfo(&PARTITION, &PARTITION_I);
	WMIData(&PARTITION);
	ShowWMIdata(&PARTITION);
	PushMysql(&PARTITION);

	// KEYBOARD
	ManyWMIInfo(&KEYBOARD, &KEYBOARD_I);
	WMIData(&KEYBOARD);
	ShowWMIdata(&KEYBOARD);
	PushMysql(&KEYBOARD);

	// BaseBoard
	WMIData(&BaseBoard);
	ShowWMIdata(&BaseBoard);
	PushMysql(&BaseBoard);

	// BaseBoard
	WMIData(&Pointer);
	ShowWMIdata(&Pointer);
	PushMysql(&Pointer);

	//Monitor
	ManyWMIInfo(&DesktopMonitor, &DesktopMonitor_I);
	WMIData(&DesktopMonitor);
	ShowWMIdata(&DesktopMonitor);
	PushMysql(&DesktopMonitor);
	

	WMIData(&Process, &Process_info);
	ShowWMIdata(&Process, &Process_info);
}

// Деструктор
SysInfo::~SysInfo() {
	delete con;
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
			prep_stmt->setString(i+2, sql::SQLString(data->ATTR[i].Value.c_str()));
		}
		
		prep_stmt->execute();

		delete prep_stmt;

	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
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
				prep_stmt->setString(n + 2, sql::SQLString(data->ATTR[i][n].Value.c_str()));
			}

			prep_stmt->execute();

			delete prep_stmt;


		}


	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
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

		if (SUCCEEDED(hr)){
			// Перебираем обьекты
			for (ULONG i = 0; i < uReturned; i++){
				
				
				// Перебираем свойства
				for (ULONG n = 0; (n < MAX_PROPERTY) & (data->ATTR[n].Name != ""); n++) {
					VARIANT vtProp;
					HRESULT hro;
					_bstr_t prName = ConvertMBSToBSTR(data->ATTR[n].Property);
					hro = apObj[i]->Get(prName, 0, &vtProp, 0, 0);
					if (!FAILED(hro)) {
						// Преобразуем ответ в строку
						hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
						data->ATTR[n].Value = ConvertBSTRToMBS(vtProp.bstrVal);
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
			// Перебираем обьекты
			for (ULONG i = 0; i < uReturned; i++) {

				data->push_back(res);


				// Перебираем свойства
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


/*===================== Отображение информации =====================*/
HRESULT SysInfo::ShowWMIdata(WMIInfo *data) {
	cout << endl;
	cout << "=======    " << data->Description << "   =======" << endl;

	for (ULONG n = 0; (n < MAX_PROPERTY) & (data->ATTR[n].Name != ""); n++) {
		cout << data->ATTR[n].Name << " : " << data->ATTR[n].Value << ";" << endl;
	}

	return S_OK;
}


HRESULT SysInfo::ShowWMIdata(WMIInfoMany *data) {
	cout << endl;
	cout << "=======    " << data->Description << "   =======" << endl;
	for (int i = 0; (i < MAX_INSTANCE) & (data->ATTR[i][0].Value != ""); i++) {
		
		cout << data->DescriptionIterator << " "<< i << endl;
		
		for (int n = 0; (n < MAX_PROPERTY) & (data->ATTR[i][n].Name != ""); n++) {
			cout << data->ATTR[i][n].Name << " : " << data->ATTR[i][n].Value << ";" << endl;
		}

	}
	return S_OK;
}


HRESULT SysInfo::ShowWMIdata(std::vector <WMIInfo> *data, WMIInfo *st) {
	cout << endl;
	cout << "=======    " << st->Description << "   =======" << endl;

	int count = data->size();

	for (WMIInfo inf : *data) {
		inf.ATTR;

		for (int n = 0; (n < MAX_PROPERTY) & (inf.ATTR[n].Name != ""); n++) {
			cout  << inf.ATTR[n].Value << ";" ;
		}
		cout << endl;
	}
		




	return S_OK;
}