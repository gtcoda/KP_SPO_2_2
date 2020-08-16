#include "SysInfo.h"

// Конструктор
SysInfo::SysInfo() {
	
	DBase &base = DBase::Instance();
	// Получим ID
	id = base.GetID();
	base.GetConnector(&con);
}


SysInfo::~SysInfo() {
	delete con;
}


HRESULT SysInfo::Info(WMIInfo *data) {
	WMIData(data);
	ShowWMIdata(data);
	PushMysql(data);
	OutWMIdata(data);
	return S_OK;
}

HRESULT SysInfo::Info(WMIInfoMany *data, WMIInfo *data_i) {
	ManyWMIInfo(data, data_i);
	WMIData(data);
	ShowWMIdata(data);
	PushMysql(data);
	OutWMIdata(data);
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


/*===================== Отправка в БД =====================*/
HRESULT SysInfo::PushMysql(WMIInfo *data) {
	// Если соединенния с базой нет. Не отправляем.
	DBase &base = DBase::Instance();
	if (!(base.STATUS)) {
		return S_FALSE;
	}


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
//			prep_stmt->setString(i + 2, sql::SQLString( cp1251_to_utf8(data->ATTR[i].Value.c_str()).c_str() ));
			prep_stmt->setString(i + 2, sql::SQLString(data->ATTR[i].Value.c_str()));
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
	// Если соединенния с базой нет. Не отправляем.
	DBase &base = DBase::Instance();
	if (!(base.STATUS)) {
		return S_FALSE;
	}

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
	// Если соединенния с базой нет. Не отправляем.
	DBase &base = DBase::Instance();
	if (!(base.STATUS)) {
		return S_FALSE;
	}

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
	hr = objWMI.Get((_bstr_t)ConvertMBSToBSTR(q), &pEnumerator);

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
						WMIDataExtruder(&(data->ATTR[n].Value), &vtProp);	
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

	hr = objWMI.Get((_bstr_t)ConvertMBSToBSTR(q), &pEnumerator);

	 
	
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
						WMIDataExtruder(&(data->ATTR[i][n].Value),&vtProp);
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

	hr = objWMI.Get((_bstr_t)ConvertMBSToBSTR(q), &pEnumerator);

	
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
						data->at(count).ATTR[n].Name = st->ATTR[n].Name;
						data->at(count).ATTR[n].Property = st->ATTR[n].Property;
						WMIDataExtruder(&(data->at(count).ATTR[n].Value), &vtProp);
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


// Преобразуем информацию из VARIANT в строку 
HRESULT SysInfo::WMIDataExtruder(string * str, VARIANT *vtProp) {
	HRESULT hr;
	// Если ответ число
	if (vtProp->vt == VT_I4) {
		hr = VariantChangeType(vtProp, vtProp, 0, VT_I4);
		string res;
		res = std::to_string((_int64)(vtProp->uintVal));
		*str = cp1251_to_utf8(res.c_str());
	}
	else {
		// Преобразуем ответ в строку
		hr = VariantChangeType(vtProp, vtProp, 0, VT_BSTR);
		*str = cp1251_to_utf8(ConvertBSTRToMBS(vtProp->bstrVal).c_str());
	}

	return hr;

}






/*===================== Отображение информации =====================*/
HRESULT SysInfo::ShowWMIdata(WMIInfo *data) {
	cout << endl;
	cout << "=======    " << data->Description << "   =======" << endl;

	for (ULONG n = 0; (n < MAX_PROPERTY) & (data->ATTR[n].Name != ""); n++) {
		if (data->ATTR[n].Value == "") { continue; }
		cout << data->ATTR[n].Name << ": " << data->ATTR[n].Value << ";" << endl;
	}

	return S_OK;
}

HRESULT SysInfo::ShowWMIdata(WMIInfoMany *data) {
	cout << endl;
	cout << "=======    " << data->Description << "   =======" << endl;
	for (int i = 0; (i < MAX_INSTANCE) & (data->ATTR[i][0].Value != ""); i++) {

		cout << data->DescriptionIterator << " " << i << endl;

		for (int n = 0; (n < MAX_PROPERTY) & (data->ATTR[i][n].Name != ""); n++) {
			if (data->ATTR[i][n].Value == "") { continue; }
			cout <<  data->ATTR[i][n].Name << ": " << data->ATTR[i][n].Value << ";" << endl;
		}
		cout << endl;

	}
	return S_OK;
}

HRESULT SysInfo::ShowWMIdata(std::vector <WMIInfo> *data, WMIInfo *st) {
	cout << endl;
	cout << "=======    " << st->Description << "   =======" << endl;

	for (WMIInfo inf : *data) {
		inf.ATTR;
		std::string str = "";

		for (int n = 0; (n < MAX_PROPERTY) & (inf.ATTR[n].Name != ""); n++) {
			str += inf.ATTR[n].Value;
			str += "\t";
		}
		str.erase(str.length() - 1, 1);

		str += ";";

		cout << str << endl;
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

/*===================== Запись информации в файл =====================*/
HRESULT SysInfo::OutWMIdata(WMIInfo *data) {
	OXML.print( "<" + data->Table + ">" );
			
	for (ULONG n = 0; (n < MAX_PROPERTY) & (data->ATTR[n].Name != ""); n++) {
		if (data->ATTR[n].Value == "") { continue; }
		OXML.print ( "	<row property='" + data->ATTR[n].Property + "' Name='" + data->ATTR[n].Name + "'> " + data->ATTR[n].Value + " </row>" );
	}
				
	OXML.print("</" + data->Table + ">");
		
	return S_OK;
	
}


HRESULT  SysInfo::OutWMIdata(WMIInfoMany *data) {


	OXML.print ( "<" + data->Table + ">" );

	for (int i = 0; (i < MAX_INSTANCE) & (data->ATTR[i][0].Value != ""); i++) {

		OXML.print("<coll number='" + to_string(i) + "'>");

		for (int n = 0; (n < MAX_PROPERTY) & (data->ATTR[i][n].Name != ""); n++) {
			if (data->ATTR[i][n].Value == "") { continue; }
			OXML.print("<row property='" + data->ATTR[i][n].Property + "' Name='" + data->ATTR[i][n].Name + "'> " + data->ATTR[i][n].Value + " </row>" );
		}
		OXML.print ("<\coll>");

	}
	OXML.print ( "</" + data->Table + ">");

	return S_OK;



}

