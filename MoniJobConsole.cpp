#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include <iostream>
#pragma comment(lib, "IPHLPAPI.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

int __cdecl main()
{
    //выводим имя устройства
    char cName[256];
    DWORD c_size = 256;
    GetComputerNameA(cName, &c_size);
    printf("\tDevice name: \t%s\n", cName);

    //выводим имя текущего пользователя
    char uName[256];
    DWORD u_size = 256;
    GetUserNameA(uName, &u_size);
    printf("\tCurrent user: \t%s\n", uName);

    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;

    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    pAdapterInfo = (IP_ADAPTER_INFO*)MALLOC(sizeof(IP_ADAPTER_INFO));

    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        FREE(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO*)MALLOC(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            printf("Error allocating memory needed to call GetAdaptersinfo\n");
            return 1;
            std::cin.get();
            return 0;
        }
    }

    //выводим IP-адрес, маску подсети и шлюз устройства в локальной сети
    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
        pAdapter = pAdapterInfo;
            printf("\tIP-address: \t%s\n",
                pAdapter->IpAddressList.IpAddress.String);
            printf("\tMask: \t\t%s\n", pAdapter->IpAddressList.IpMask.String);
            printf("\tGateway: \t%s\n", pAdapter->GatewayList.IpAddress.String);
            std::cin.get();
            return 0;
    }
    else {
        printf("GetAdaptersInfo failed with error: %d\n", dwRetVal);
        std::cin.get();
        return 0;
    }

    //освобождаем память
    if (pAdapterInfo)
        FREE(pAdapterInfo);
    return 0;
}

