#include "OutXML.h"


OutXML::OutXML() {
	std::ofstream out;
	out.open(XMLFile); // окрываем файл для записи
	if (out.is_open()){
		string d = "<?xml version=\"1.0\"?>";
		out << d << endl;

	}

	out.close();
}

HRESULT OutXML::print(string s) {
	
	std::ofstream out;
	out.open(XMLFile, std::ios::app); // окрываем файл для записи
	if (out.is_open()){
		out << s << endl;
		out.close();
		return S_OK;
	}

	out.close();
	return S_FALSE;
	
}