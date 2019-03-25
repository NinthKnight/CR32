// 网段内主机信息双向链表
typedef struct _LAN_HOST_INFO {
	char IpAddr[4 * 4]; /* 主机IP地址 */
	char HostName[25]; /* 主机名 */
	unsigned char ucMacAddr[4]; /* 主机网卡地址 */
	BOOL bIsOnline; /* 是否在线 */
	struct _LAN_HOST_INFO *prev; /* 上一个主机的指针 */
	struct _LAN_HOST_INFO *next; /* 下一个主机的指针 */
}LAN_HOST_INFO, *PLAN_HOST_INFO;

void EnumLanHost(char IpAddr[], char SubMask[]);

void scan_lan(LPVOID lparam)
{
	char IpAddr[16];
	u_char ucMacAddr[6];
	PLAN_HOST_INFO pInfo;
	unsigned long nRemoteAddr;
	struct hostent *pHostent; 
	memset(IpAddr, 0, sizeof(IpAddr));
	memset(ucMacAddr, 0xff, sizeof(ucMacAddr));

	// 拷贝参数
	pInfo = (PLAN_HOST_INFO) lparam;
	memcpy(IpAddr, pInfo->IpAddr, sizeof(IpAddr));

	if (GetMac(IpAddr, ucMacAddr))
	{
		// 存活主机信息保存至链表
		pInfo->bIsOnline = TRUE;
		memcpy(pInfo->ucMacAddr, ucMacAddr, sizeof(ucMacAddr));

		// 得到主机名
		nRemoteAddr = inet_addr(IpAddr);
		pHostent = (struct hostent*) malloc(sizeof(struct hostent));
		memset(pHostent, 0, sizeof(struct hostent));
		pHostent = gethostbyaddr((char*)&nRemoteAddr, 4, AF_INET);
		if (pHostent)
			memcpy(pInfo->HostName, pHostent->h_name, strlen(pHostent->h_name));
	}
	else
		pInfo->bIsOnline = FALSE;
}
//
// 得到网段内所有主机的信息
// 入口参数: 自身IP地址、子网掩码
//

void EnumLanHost(char IpAddr[], char SubMask[])
{

	unsigned int uHostByte; // 主机位
	int i, uHostNum;

	ULONG uMacLength = 6;

	// 两个临时变量
	char TempIpAddr[4 * 4];

	PLAN_HOST_INFO pLanHostInfo, pNextHostInfo; // 永远指向链表接尾部

	HANDLE *hThread; // 线程数组指针
	DWORD dwThreadID; // 线程ID
	WSADATA wsaData;

	WSAStartup(MAKEWORD(2,1), &wsaData);
	printf("[+] Start scan lan ......\n");

	// 由IP地址得到主机位
	uHostByte = htonl(inet_addr(IpAddr)) & 0xffffff00;

	// 由子网掩码得到网段内的主机数量
	// 子网主机个数 = ~ MASK - 1
	uHostNum = ~ htonl(inet_addr(SubMask)) - 1;

	// 初始化线程句柄数组
	hThread = (HANDLE *)malloc(sizeof(HANDLE) * uHostNum);
	
	// 初始化链表
	pLanHostInfo = (PLAN_HOST_INFO) malloc(sizeof(LAN_HOST_INFO));
	memset(pLanHostInfo, 0, sizeof(LAN_HOST_INFO));
	pLanHostInfo->prev = NULL;

	
	printf("[+] Scan for adresses from %d.%d.%d.1-%d\n\n",
		(uHostByte & 0xff000000) >> 0x18,
		(uHostByte & 0x00ff0000) >> 0x10,
		(uHostByte & 0x0000ff00) >> 0x08, uHostNum);

	// 开始进行多线程ARP扫描,创建uHostNum个线程扫描
	// Scan Range: 1 ~ uHostNum
	for (i = 0, uHostByte ++; i < uHostNum; i ++, uHostByte ++)
	{
		// 构造IP地址
		memset(TempIpAddr, 0, strlen(TempIpAddr));
		sprintf(TempIpAddr, "%d.%d.%d.%d", 
			(uHostByte & 0xff000000) >> 0x18,
			(uHostByte & 0x00ff0000) >> 0x10,
			(uHostByte & 0x0000ff00) >> 0x08,
			(uHostByte & 0x000000ff));
		// 构造链表
		pNextHostInfo = (PLAN_HOST_INFO) malloc(sizeof(LAN_HOST_INFO));
		memset(pNextHostInfo, 0, sizeof(LAN_HOST_INFO));
		memcpy(pLanHostInfo->IpAddr, TempIpAddr, sizeof(TempIpAddr));
		pLanHostInfo->next = pNextHostInfo;
		pNextHostInfo->prev = pLanHostInfo;
		pNextHostInfo->next = NULL;

		if ((hThread[i]=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) scan_lan, 
			pLanHostInfo, 0, &dwThreadID))==NULL)
		{
			printf("[!] Create thread error! IP is %s\n",TempIpAddr);
		}
		pLanHostInfo = pLanHostInfo->next;

		Sleep(2); // 等待参数传递完毕，再重新赋值
	}
	
	// 等待线程返回,退出函数
	WaitForMultipleObjects(uHostNum,hThread,TRUE,-1);

	// 显示存活主机信息
	printf("IP address        MAC address        NetBIOS Name\n");
	printf("------------------------------------------------------------------------------\n");

	for (i=0; pLanHostInfo->prev != NULL; )
	{
		pLanHostInfo = pLanHostInfo->prev;
		if (pLanHostInfo->bIsOnline)
		{
			printf("%-16s  %.2X-%.2X-%.2X-%.2X-%.2X-%.2X  %s\n", 
				pLanHostInfo->IpAddr,
				pLanHostInfo->ucMacAddr[0], pLanHostInfo->ucMacAddr[1],
				pLanHostInfo->ucMacAddr[2], pLanHostInfo->ucMacAddr[3], 
				pLanHostInfo->ucMacAddr[4], pLanHostInfo->ucMacAddr[5],
				strlen(pLanHostInfo->HostName) > 0 ? pLanHostInfo->HostName : "N/A");
			i++;
		}
	}
	printf("------------------------------------------------------------------------------\n");
	printf("\n[*] Tatol %d host alive, scan finished\n", i);
	WSACleanup();
}