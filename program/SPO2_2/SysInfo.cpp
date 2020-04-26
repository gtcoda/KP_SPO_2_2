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


	// Получение информации о процессоре
	CPUInfo();

	// Получение информации о BIOS
	BIOSInfo();
}

// Деструктор
SysInfo::~SysInfo() {
	delete con;
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

// Отправить в базу CPU
HRESULT SysInfo::PushMysqlCPU() {

	try {

		sql::PreparedStatement *prep_stmt;

		prep_stmt = con->prepareStatement("INSERT INTO CPU(id,Name,Arc,AddressWidth,MaxCS,CurCS,BusS,NCore,EnCore,LogicCore,L2,L3) VALUES (?,?,?,?,?,?,?,?,?,?,?,?)");
		prep_stmt->setInt64(1, id);
		prep_stmt->setString(2, sql::SQLString(CPU.Name.c_str()));
		prep_stmt->setString(3, sql::SQLString(CPU.Arc.c_str()));
		prep_stmt->setInt64(4, CPU.AddressWidth);
		prep_stmt->setInt64(5, CPU.MaxCS);
		prep_stmt->setInt64(6, CPU.CurCS);
		prep_stmt->setInt64(7, CPU.BusS);
		prep_stmt->setInt64(8, CPU.NCore);
		prep_stmt->setInt64(9, CPU.EnCore);
		prep_stmt->setInt64(10, CPU.LogicCore);
		prep_stmt->setInt64(11, CPU.L2);
		prep_stmt->setInt64(12, CPU.L3);

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
// Отправить в базу BIOS
HRESULT SysInfo::PushMysqlBIOS() {
	
	try {
		sql::PreparedStatement *prep_stmt;
		prep_stmt = con->prepareStatement("INSERT INTO BIOS(id,Version,Caption,Manufacturer) VALUES (?, ?, ?, ?)");

		prep_stmt->setInt64(1, id);
		prep_stmt->setString(2, sql::SQLString(BIOS.Version.c_str()));
		prep_stmt->setString(3, sql::SQLString(BIOS.Caption.c_str()));
		prep_stmt->setString(4, sql::SQLString(BIOS.Manufacturer.c_str()));

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

/*===================== Получение информации =====================*/

// Получение информации о процессоре
HRESULT SysInfo::CPUInfo() {
	HRESULT hr;
	IEnumWbemClassObject * pEnumerator = NULL;

	objWMI.Get((_bstr_t)"SELECT * FROM Win32_Processor", &pEnumerator);

	hr = WBEM_S_NO_ERROR;
	// Final Next will return WBEM_S_FALSE
	while (WBEM_S_NO_ERROR == hr)
	{
		ULONG            uReturned;
		IWbemClassObject*    apObj[2];

		hr = pEnumerator->Next(WBEM_INFINITE, 2, apObj, &uReturned);

		if (SUCCEEDED(hr))
		{
			for (ULONG n = 0; n < uReturned; n++)
			{
				VARIANT vtProp;

				hr = apObj[n]->Get((_bstr_t)"AddressWidth", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					CPU.AddressWidth = vtProp.intVal;
				}

				hr = apObj[n]->Get((_bstr_t)"Architecture", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					switch (vtProp.intVal) {
					case 0: CPU.Arc = (std::string)"x86"; break;
					case 1: CPU.Arc = (std::string)"MIPS"; break;
					case 2: CPU.Arc = (std::string)"Alpha"; break;
					case 3: CPU.Arc = (std::string)"PowerPC"; break;
					case 5: CPU.Arc = (std::string)"ARM"; break;
					case 6: CPU.Arc = (std::string)"ia64"; break;
					case 9: CPU.Arc = (std::string)"x64"; break;
					}
				}

				hr = apObj[n]->Get((_bstr_t)"Name", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					CPU.Name = ConvertBSTRToMBS(vtProp.bstrVal);
				}

				hr = apObj[n]->Get((_bstr_t)"MaxClockSpeed", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					CPU.MaxCS = vtProp.intVal;
				}

				hr = apObj[n]->Get((_bstr_t)"CurrentClockSpeed", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					CPU.CurCS = vtProp.intVal;
				}

				hr = apObj[n]->Get((_bstr_t)"ExtClock", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					CPU.BusS = vtProp.intVal;
				}

				hr = apObj[n]->Get((_bstr_t)"NumberOfCores", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					CPU.NCore = vtProp.intVal;
				}

				hr = apObj[n]->Get((_bstr_t)"NumberOfEnabledCore", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					CPU.EnCore = vtProp.intVal;
				}

				hr = apObj[n]->Get((_bstr_t)"NumberOfLogicalProcessors", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					CPU.LogicCore = vtProp.intVal;
				}

				hr = apObj[n]->Get((_bstr_t)"L2CacheSize", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					CPU.L2 = vtProp.intVal;
				}

				hr = apObj[n]->Get((_bstr_t)"L3CacheSize", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					CPU.L3 = vtProp.intVal;
				}

				apObj[n]->Release();
			}

		}
	}

	return S_OK;

}
// Получение информации о BIOS
HRESULT SysInfo::BIOSInfo() {
	HRESULT hr;
	IEnumWbemClassObject * pEnumerator = NULL;

	objWMI.Get((_bstr_t)"SELECT * FROM Win32_BIOS", &pEnumerator);

	hr = WBEM_S_NO_ERROR;
	// Final Next will return WBEM_S_FALSE
	while (WBEM_S_NO_ERROR == hr)
	{
		ULONG            uReturned;
		IWbemClassObject*    apObj[10];

		hr = pEnumerator->Next(WBEM_INFINITE, 10, apObj, &uReturned);

		if (SUCCEEDED(hr))
		{
			for (ULONG n = 0; n < uReturned; n++)
			{
				VARIANT vtProp;

				apObj[n]->Get((_bstr_t)"Manufacturer", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					BIOS.Manufacturer = ConvertBSTRToMBS(vtProp.bstrVal);

				}

				apObj[n]->Get((_bstr_t)"Version", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					BIOS.Version = ConvertBSTRToMBS(vtProp.bstrVal);
				}

				apObj[n]->Get((_bstr_t)"Caption", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					BIOS.Caption = ConvertBSTRToMBS(vtProp.bstrVal);
				}
				
				apObj[n]->Release();
			}

		}
	}

	return S_OK;
}

HRESULT SysInfo::PartitionInfo() {}

HRESULT SysInfo::DiskInfo() {}

HRESULT SysInfo::KeyboardInfo() {}

HRESULT SysInfo::MBInfo() {}

HRESULT SysInfo::MouseInfo() {}

HRESULT SysInfo::VAInfo() {}

HRESULT SysInfo::DisplayInfo() {}

HRESULT SysInfo::IfInfo() {}

HRESULT SysInfo::AppInfo() {}


/*===================== Отображение информации =====================*/

// Отобразить информацию о процессоре
HRESULT SysInfo::ShowProcessor() {
	
	cout << "CPU Info" << endl;
	cout << "Разрядность: " << CPU.AddressWidth << endl;
	cout << "Архитектура: " << CPU.Arc << endl;
	cout << "Имя: " << CPU.Name << endl;
	cout << "Максимальная частота: " << CPU.MaxCS << " МГц" << endl;
	cout << "Текущая частота: " << CPU.CurCS << " МГц" << endl;
	cout << "Частота шины: " << CPU.BusS << " МГц" << endl;
	cout << "Количество ядер: " << CPU.NCore << endl;
	cout << "Количество активных ядер: " << CPU.EnCore << endl;
	cout << "Количество логических ядер: " << CPU.LogicCore << endl;
	cout << "Размер L2: " << CPU.L2 << " Кб" << endl;
	cout << "Размер L3: " << CPU.L3 << " Кб" << endl;
	return S_OK;
}

// Отобразить информацию о BIOS
HRESULT SysInfo::ShowBIOS() {

	cout << "Caption: " <<  BIOS.Caption << endl;
	cout << "Произведено: " << BIOS.Manufacturer << endl;			
	cout << "Версия: " << BIOS.Version << endl;
	return S_OK;
}

// Отобразить информацию о DISK
HRESULT SysInfo::ShowDISK() {
	HRESULT hr;
	cout << "DISK Info" << endl;
	IEnumWbemClassObject * pEnumerator = NULL;
	
	objWMI.Get((_bstr_t)"SELECT * FROM Win32_DiskDrive", &pEnumerator);
	

	hr = WBEM_S_NO_ERROR;
	// Final Next will return WBEM_S_FALSE
	while (WBEM_S_NO_ERROR == hr)
	{
		ULONG            uReturned;
		IWbemClassObject*    apObj[10];

		hr = pEnumerator->Next(WBEM_INFINITE, 10, apObj, &uReturned);

		if (SUCCEEDED(hr))
		{
			for (ULONG n = 0; n < uReturned; n++)
			{

				VARIANT vtProp;
				VARIANT Caption = {}, Model = {}, Size = {};

				apObj[n]->Get((_bstr_t)"Caption", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "Название: " << vtProp.bstrVal  << endl;
				}

				apObj[n]->Get((_bstr_t)"Model", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "Модель: " << vtProp.bstrVal << endl;
				}

				apObj[n]->Get((_bstr_t)"Size", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << "Размер: " << vtProp.intVal << endl;
				}



				apObj[n]->Release();
			}

		}    
	}    


	return S_OK;
}

// Отобразить информацию о разделах
HRESULT SysInfo::ShowPartition() {
	HRESULT hr;
	cout << "Partition Info" << endl;
	IEnumWbemClassObject * pEnumerator = NULL;

	objWMI.Get((_bstr_t)"SELECT * FROM Win32_LogicalDisk", &pEnumerator);


	hr = WBEM_S_NO_ERROR;

	while (WBEM_S_NO_ERROR == hr)
	{
		ULONG            uReturned;
		IWbemClassObject*    apObj[10];

		hr = pEnumerator->Next(WBEM_INFINITE, 10, apObj, &uReturned);

		if (uReturned > 0)
		{
			std::cout << "Caption \t"
				<< "FileSystem \t"
				<< "Size \t"
				<< "FreeSize \t"
				<< std::endl;


			for (ULONG n = 0; n < uReturned; n++)
			{

				VARIANT vtProp;
				
				apObj[n]->Get((_bstr_t)"Caption", 0, &vtProp, 0, 0);
				if (!FAILED(hr)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout << vtProp.bstrVal << "\t\t";
				}


				apObj[n]->Get((_bstr_t)"FileSystem", 0, &vtProp, 0, 0);
				if (!FAILED(hr) & (vtProp.bstrVal != NULL)) {
					// Преобразуем ответ в строку
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_BSTR);
					wcout  << vtProp.bstrVal << "\t\t";
				}

				apObj[n]->Get((_bstr_t)"Size", 0, &vtProp, 0, 0);
				if (!FAILED(hr) & (vtProp.bstrVal != NULL)) {
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_UI8);
					cout << vtProp.llVal / 1000000000 << "\t";
				}

				apObj[n]->Get((_bstr_t)"FreeSpace", 0, &vtProp, 0, 0);
				if (!FAILED(hr) & (vtProp.bstrVal != NULL)) {
					hr = VariantChangeType(&vtProp, &vtProp, 0, VT_UI8);
					cout << vtProp.llVal / 1000000000 << "\t";
				}

				cout << endl;
				apObj[n]->Release();
			}

		}
	}


	return S_OK;
}
