#include "USERS.h"








HRESULT USERS::Go(void){
	ManyWMIInfo(&USERSstr, &USERS_I);




	LPUSER_INFO_0 pBuf_0 = NULL;
	LPUSER_INFO_0 pTmpBuf;
	DWORD dwLevel = 0;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD dwResumeHandle = 0;
	
	DWORD dwTotalCount = 0;
	NET_API_STATUS nStatus;
	LPTSTR pszServerName = NULL;


	LPCWSTR user[10];
	uint8_t n = 0;
	uint8_t i;



	do {
		nStatus = NetUserEnum(NULL,
			dwLevel,
			FILTER_NORMAL_ACCOUNT, // global users
			(LPBYTE*)&pBuf_0,
			dwPrefMaxLen,
			&dwEntriesRead,
			&dwTotalEntries,
			&dwResumeHandle);

		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA)) {
			if ((pTmpBuf = pBuf_0) != NULL) {
				//
				// Loop through the entries.
				//
				for (i = 0; (i < dwEntriesRead); i++) {
					assert(pTmpBuf != NULL);

					if (pTmpBuf == NULL) 	break;
					
					user[n] = pTmpBuf->usri0_name;
					n++;

					pTmpBuf++;
					dwTotalCount++;
				}
			}
		}


		if (pBuf_0 != NULL) {
			NetApiBufferFree(pBuf_0);
			pBuf_0 = NULL;
		}
	} while (nStatus == ERROR_MORE_DATA); // end do


	if (pBuf_0 != NULL) NetApiBufferFree(pBuf_0);

	for (uint8_t j = 0; n > 0; n--, j++) {


		LPUSER_INFO_2 pBuf2 = NULL;
		LPTSTR sStringSid = NULL;

		wchar_t usersname[255];

		wcscpy_s(usersname, 255, user[n - 1]);


		nStatus = NetUserGetInfo(NULL, usersname, 2, (LPBYTE *)&pBuf2);


		if (nStatus == NERR_Success) {
			if (pBuf2 != NULL && pBuf2->usri2_last_logon != 0) {
								
				time_t t = time(0);

				LONGLONG uptime = t - pBuf2->usri2_last_logon;

				const long day_t = 60 * 60 * 24;
				const long hours_t = 60 * 60;
				const long min_t = 60;
				const long second_t = 0;

				int64_t day = uptime / day_t;
				uptime = uptime % day_t;

				int64_t hours = uptime / hours_t;
				uptime = uptime % hours_t;

				int64_t min = uptime / min_t;
				uptime = uptime % min_t;

				int64_t second = uptime;

				for (int i = 0; i < MAX_PROPERTY; i++) {
					if (USERSstr.ATTR[j][i].Property == "Day") {
						USERSstr.ATTR[j][i].Value = to_string(day);
						continue;
					}
					if (USERSstr.ATTR[j][i].Property == "Hours") {
						USERSstr.ATTR[j][i].Value = to_string(hours);
						continue;
					}
					if (USERSstr.ATTR[j][i].Property == "Min") {
						USERSstr.ATTR[j][i].Value = to_string(min);
						continue;
					}
					if (USERSstr.ATTR[j][i].Property == "Second") {
						USERSstr.ATTR[j][i].Value = to_string(second);
						continue;
					}
				}


				wchar_t name[255];
				wcscpy_s(name, 255, pBuf2->usri2_name);

				USERSstr.ATTR[j][0].Value = WstrToUtf8Str(name);
				


			}
		}
		else return S_FALSE;
			
		if (pBuf2 != NULL) NetApiBufferFree(pBuf2);

		
	}



	ShowWMIdata(&USERSstr);


	return S_OK;
}






/*
				pBuf2 = (LPUSER_INFO_2)pBuf2;
				wprintf(L"\tUser account name: %s\n", pBuf2->usri2_name);
				wprintf(L"\tPassword: %s\n", pBuf2->usri2_password);
				wprintf(L"\tPassword age (seconds): %d\n",
					pBuf2->usri2_password_age);
				wprintf(L"\tPrivilege level: %d\n", pBuf2->usri2_priv);
				wprintf(L"\tHome directory: %s\n", pBuf2->usri2_home_dir);
				wprintf(L"\tComment: %s\n", pBuf2->usri2_comment);
				wprintf(L"\tFlags (in hex): %x\n", pBuf2->usri2_flags);
				wprintf(L"\tScript path: %s\n", pBuf2->usri2_script_path);
				wprintf(L"\tAuth flags (in hex): %x\n",
					pBuf2->usri2_auth_flags);
				wprintf(L"\tFull name: %s\n", pBuf2->usri2_full_name);
				wprintf(L"\tUser comment: %s\n", pBuf2->usri2_usr_comment);
				wprintf(L"\tParameters: %s\n", pBuf2->usri2_parms);
				wprintf(L"\tWorkstations: %s\n", pBuf2->usri2_workstations);
				wprintf
				(L"\tLast logon (seconds since January 1, 1970 GMT): %d\n",
					pBuf2->usri2_last_logon);
				wprintf
				(L"\tLast logoff (seconds since January 1, 1970 GMT): %d\n",
					pBuf2->usri2_last_logoff);
				wprintf
				(L"\tAccount expires (seconds since January 1, 1970 GMT): %d\n",
					pBuf2->usri2_acct_expires);
				wprintf(L"\tMax storage: %d\n", pBuf2->usri2_max_storage);
				wprintf(L"\tUnits per week: %d\n",
					pBuf2->usri2_units_per_week);
				wprintf(L"\tLogon hours:");
				for (j = 0; j < 21; j++) {
					printf(" %x", (BYTE)pBuf2->usri2_logon_hours[j]);
				}
				wprintf(L"\n");
				wprintf(L"\tBad password count: %d\n",
					pBuf2->usri2_bad_pw_count);
				wprintf(L"\tNumber of logons: %d\n",
					pBuf2->usri2_num_logons);
				wprintf(L"\tLogon server: %s\n", pBuf2->usri2_logon_server);
				wprintf(L"\tCountry code: %d\n", pBuf2->usri2_country_code);
				wprintf(L"\tCode page: %d\n", pBuf2->usri2_code_page);
*/