#include "UPTIME.h"

HRESULT UPTIME::Go(void) {
	UpTime(&UPTIMEstr);
	ShowWMIdata(&UPTIMEstr);
	PushMysql(&UPTIMEstr);

	return S_OK;
}


HRESULT  UPTIME::UpTime(WMIInfo *upt) {
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


