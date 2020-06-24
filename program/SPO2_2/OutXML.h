#ifndef OutXML_H
#define OutXML_H

#define _WIN32_DCOM
using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>
#include <comdef.h>
#include <Wbemidl.h>
#include <algorithm>
#include <vector>

class OutXML
{
public:



	static OutXML& Instance()
	{
		static OutXML theSingleInstance;
		return theSingleInstance;
	}

	string XMLFile = "info.xml";
	std::ofstream out;

	HRESULT print(string s);


private:

	OutXML();
	OutXML(const OutXML& root) = delete;
	OutXML& operator=(const OutXML&) = delete;
};


#endif