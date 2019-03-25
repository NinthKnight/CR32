//////////////////////////////////////////////////
// iphlpapi.h文件
//

/**++

修改自 Borland C++ 中的iphlpapi.h文件
    因为VC++ 6.0 不支持这些函数
    
--*/

#define MAX_ADAPTER_DESCRIPTION_LENGTH  128 // arb.
#define MAX_ADAPTER_NAME_LENGTH         256 // arb.
#define MAX_ADAPTER_ADDRESS_LENGTH      8   // arb.
#define MAXLEN_PHYSADDR 8

//
// IP_ADDRESS_STRING - store an IP address as a dotted decimal string
//

typedef struct {
    char String[4 * 4];
} IP_ADDRESS_STRING, *PIP_ADDRESS_STRING, IP_MASK_STRING, *PIP_MASK_STRING;

//
// IP_ADDR_STRING - store an IP address with its corresponding subnet mask,
// both as dotted decimal strings
//

typedef struct _IP_ADDR_STRING {
    struct _IP_ADDR_STRING* Next;
    IP_ADDRESS_STRING IpAddress;
    IP_MASK_STRING IpMask;
    DWORD Context;
} IP_ADDR_STRING, *PIP_ADDR_STRING;

//
// ADAPTER_INFO - per-adapter information. All IP addresses are stored as
// strings
//

typedef struct _IP_ADAPTER_INFO {
    struct _IP_ADAPTER_INFO* Next;
    DWORD ComboIndex;
    char AdapterName[MAX_ADAPTER_NAME_LENGTH + 4];
    char Description[MAX_ADAPTER_DESCRIPTION_LENGTH + 4];
    UINT AddressLength;
    BYTE Address[MAX_ADAPTER_ADDRESS_LENGTH];
    DWORD Index;
    UINT Type;
    UINT DhcpEnabled;
    PIP_ADDR_STRING CurrentIpAddress;
    IP_ADDR_STRING IpAddressList;
    IP_ADDR_STRING GatewayList;
    IP_ADDR_STRING DhcpServer;
    BOOL HaveWins;
    IP_ADDR_STRING PrimaryWinsServer;
    IP_ADDR_STRING SecondaryWinsServer;
    time_t LeaseObtained;
    time_t LeaseExpires;
} IP_ADAPTER_INFO, *PIP_ADAPTER_INFO;

typedef struct _MIB_IPNETROW
{
    DWORD		dwIndex;
    DWORD		dwPhysAddrLen;
    BYTE		bPhysAddr[MAXLEN_PHYSADDR];
    DWORD		dwAddr;
    DWORD		dwType;
} MIB_IPNETROW, *PMIB_IPNETROW;

typedef struct _MIB_IPFORWARDROW
{
    DWORD		dwForwardDest;
    DWORD		dwForwardMask;
    DWORD		dwForwardPolicy;
    DWORD		dwForwardNextHop;
    DWORD		dwForwardIfIndex;
    DWORD		dwForwardType;
    DWORD		dwForwardProto;
    DWORD		dwForwardAge;
    DWORD       dwForwardNextHopAS;
    DWORD		dwForwardMetric1;
    DWORD		dwForwardMetric2;
    DWORD		dwForwardMetric3;
    DWORD		dwForwardMetric4;
    DWORD		dwForwardMetric5;
}MIB_IPFORWARDROW, *PMIB_IPFORWARDROW;


typedef unsigned long   IPAddr;     // An IP address.


typedef DWORD (CALLBACK * CRIPENY) (IN PMIB_IPNETROW pArpEntry); // CreateIpNetEntry
typedef DWORD (CALLBACK * SENDARP) (IPAddr, IPAddr, PULONG,PULONG); // SendARP
typedef DWORD (CALLBACK * GBESTRT) (IN  DWORD, IN  DWORD, OUT PMIB_IPFORWARDROW); // GetBestRoute
typedef DWORD (CALLBACK * PGAINFO) (PIP_ADAPTER_INFO,PULONG); //GetAdaptersInfo

HINSTANCE hInst = LoadLibrary("iphlpapi.dll");
CRIPENY CreateIpNetEntry = (CRIPENY) GetProcAddress(hInst,"CreateIpNetEntry");
GBESTRT GetBestRoute = (GBESTRT) GetProcAddress(hInst,"GetBestRoute");
PGAINFO GetAdaptersInfo=(PGAINFO) GetProcAddress(hInst,"GetAdaptersInfo");
SENDARP SendARP = (SENDARP) GetProcAddress(hInst,"SendARP");

//
// 表态绑定ARP函数，操作ARP表
//

BOOL StaticARP(unsigned char szIPAddr[], BYTE bPhysAddr[])
{
	MIB_IPFORWARDROW ipfrow;
	MIB_IPNETROW iprow;
	DWORD dwIPAddr = inet_addr((char *) szIPAddr);
	if (GetBestRoute(dwIPAddr, ADDR_ANY, &ipfrow) != NO_ERROR)
		return (-1);
	memset(&iprow, 0, sizeof(iprow));
	iprow.dwIndex = ipfrow.dwForwardIfIndex;
	iprow.dwPhysAddrLen = 6;
	memcpy(iprow.bPhysAddr, bPhysAddr, 6);
	iprow.dwAddr = dwIPAddr;
	iprow.dwType = 4;	/* - static */

	if (CreateIpNetEntry(&iprow) != NO_ERROR)
		return TRUE;
	return FALSE;
}

//
// 由网卡的名子得到网卡地址相关信息，IP地址、网卡地址、网关IP地址
// 入口参数: 网卡ID ListAdapter()所得
// 出口参数: szIPAddr ==> 自身IP地址 ucPhysical ==> 网卡地址 szGateIPAddr ==> 网关地址 
//

BOOL Getadapterbyname(char szAdapterName[], char szIPAddr[],
					  unsigned char ucPhysicalAddr[],  char szGateIPAddr[])
{
	PIP_ADAPTER_INFO pInfo = NULL, pInfoTemp = NULL;
	ULONG ulSize = 0;
	GetAdaptersInfo(pInfo, &ulSize); // First call get buff size
	pInfo = (PIP_ADAPTER_INFO) new(char[ulSize]);
	GetAdaptersInfo(pInfo, &ulSize);
	while(pInfo)
	{
		if (strcmp(szAdapterName, pInfo->AdapterName) ==0)
		{
			
			for(int i=0; i < (int)pInfo->AddressLength; i++)
				ucPhysicalAddr[i] = pInfo->Address[i];
			// Get Last Ip Address To szIPAddr
			PIP_ADDR_STRING pAddTemp=&(pInfo->IpAddressList);
			while(pAddTemp)
			{
				strcpy(szIPAddr,pAddTemp->IpAddress.String);
				pAddTemp=pAddTemp->Next;
			}
			if (strlen(pInfo->GatewayList.IpAddress.String) > 0)
				strcpy(szGateIPAddr, pInfo->GatewayList.IpAddress.String);
			else
				strcpy(szGateIPAddr, "N/A"); // Not Applicable
			return TRUE;
		}
		pInfo = pInfo->Next; 
	}
	delete pInfo;
	return FALSE;
}

