#include "NETWORK.h"


HRESULT NETWORK::Go(void) {
	
	ManyWMIInfo(&NetworkAdapter, &NetworkAdapter_I);
	GetNetworkInfo(&NetworkAdapter);
	ShowWMIdata(&NetworkAdapter);
	PushMysql(&NetworkAdapter);
	OutWMIdata(&NetworkAdapter);
	
	return S_OK;
}



HRESULT NETWORK::GetNetworkInfo(WMIInfoMany *NetworkAdapter) {

	IP_ADAPTER_INFO * AdapterInfo;
	ULONG    ulOutBufLen;
	DWORD    dwRetVal;
	IP_ADDR_STRING * pIPAddr;

	// Запросим информацию
	AdapterInfo = (IP_ADAPTER_INFO *)GlobalAlloc(GPTR, sizeof(IP_ADAPTER_INFO));
	ulOutBufLen = sizeof(IP_ADAPTER_INFO);

	// Не влезли в буфер. Вызовем еще раз с правильным буфером. 
	if (ERROR_BUFFER_OVERFLOW == GetAdaptersInfo(AdapterInfo, &ulOutBufLen)) {
		GlobalFree(AdapterInfo);
		AdapterInfo = (IP_ADAPTER_INFO *)GlobalAlloc(GPTR, ulOutBufLen);
	}

	if (dwRetVal = GetAdaptersInfo(AdapterInfo, &ulOutBufLen)) {
		return S_FALSE;
	}
	else {

		for (uint8_t i = 0; i < MAX_INSTANCE != NULL; i++) {
			
			NetworkAdapter->ATTR[i][0].Value = AdapterInfo->AdapterName;
			NetworkAdapter->ATTR[i][1].Value = AdapterInfo->Description;

			char mac[20];

			for (uint8_t m = 0; m < AdapterInfo->AddressLength; m++) {
				if (m == (AdapterInfo->AddressLength - 1))
					sprintf(&mac[m*3],"%.2X", (int)AdapterInfo->Address[m]);
				else
					sprintf(&mac[m*3],"%.2X-", (int)AdapterInfo->Address[m]);
			}
			NetworkAdapter->ATTR[i][2].Value = mac;

			NetworkAdapter->ATTR[i][3].Value = AdapterInfo->IpAddressList.IpAddress.String;
			NetworkAdapter->ATTR[i][4].Value = AdapterInfo->GatewayList.IpAddress.String;
			
			if (AdapterInfo->DhcpEnabled) {
				NetworkAdapter->ATTR[i][5].Value = "Yes";
			}
			else {
				NetworkAdapter->ATTR[i][5].Value = "No";
			}

			NetworkAdapter->ATTR[i][6].Value = AdapterInfo->DhcpServer.IpAddress.String;

			NetworkAdapter->Count = i + 1;

			AdapterInfo = AdapterInfo->Next;
			if (AdapterInfo == NULL) break;
		}
		
	}

	return S_OK;


}