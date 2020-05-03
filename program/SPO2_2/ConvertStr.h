#ifndef ConvertStr_H
#define ConvertStr_H
#pragma once
#include <iostream>
#include <iomanip>
#include <comdef.h>
#include <Wbemidl.h>

std::string ConvertBSTRToMBS(BSTR bstr);
std::string ConvertWCSToMBS(const wchar_t* pstr, long wslen);
BSTR ConvertMBSToBSTR(const std::string& str);

std::string utf8_to_cp1251(const char *str);
std::string cp1251_to_utf8(const char *str);


#endif