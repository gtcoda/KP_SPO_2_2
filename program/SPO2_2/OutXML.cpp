#include "OutXML.h"


OutXML::OutXML() {
	out.open(XMLFile);
	out << "<?xml version=\"1.0\" encoding=\"UTF - 8\" standalone=\"no\" ?>" << endl;
}

HRESULT OutXML::print(string s) {
	if (out.is_open()) {
		out << s.c_str();
		return S_OK;
	}

	return S_FALSE;
}