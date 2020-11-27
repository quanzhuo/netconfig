#include <windows.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "Iphlpapi.lib")

void main(void)
{

    DWORD Err, AdapterInfoSize = 0;
    PIP_ADAPTER_INFO pAdapterInfo, pAdapt;
    PIP_ADDR_STRING pAddrStr;

    if ((Err = GetAdaptersInfo(NULL, &AdapterInfoSize)) != 0)
    {
        if (Err != ERROR_BUFFER_OVERFLOW)
        {
            printf("GetAdaptersInfo sizing failed with error %d\n", Err);
            return;
        }
    }

    if ((pAdapterInfo = (PIP_ADAPTER_INFO)GlobalAlloc(GPTR, AdapterInfoSize)) == NULL)
    {
        printf("Memory allocation error\n");
        return;
    }

    if ((Err = GetAdaptersInfo(pAdapterInfo, &AdapterInfoSize)) != 0)
    {
        printf("GetAdaptersInfo failed with error %d\n", Err);
        return;
    }

    pAdapt = pAdapterInfo;

    while (pAdapt)
    {
        pAddrStr = &(pAdapt->IpAddressList);
        while (pAddrStr)
        {
            printf("IP Address. . . . . . . . . : %s\n", pAddrStr->IpAddress.String);
            printf("Subnet Mask . . . . . . . . : %s\n", pAddrStr->IpMask.String);
            pAddrStr = pAddrStr->Next;
        }

        printf("Default Gateway . . . . . . : %s\n", pAdapt->GatewayList.IpAddress.String);
        pAddrStr = pAdapt->GatewayList.Next;
        while (pAddrStr)
        {
            printf("%52s\n", pAddrStr->IpAddress.String);
            pAddrStr = pAddrStr->Next;
        }

        printf("DHCP Server . . . . . . . . : %s\n", pAdapt->DhcpServer.IpAddress.String);
        printf("Primary WINS Server . . . . : %s\n", pAdapt->PrimaryWinsServer.IpAddress.String);
        printf("Secondary WINS Server . . . : %s\n", pAdapt->SecondaryWinsServer.IpAddress.String);

        pAdapt = pAdapt->Next;
    }
}
