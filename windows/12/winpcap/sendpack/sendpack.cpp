#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wpcap.lib")

#include "iphlpapi.h"
#include "protoinfo.h"
#include "spoof.h"
#include "tcp.h"
#include "scan.h"
#include "replace.h"

char  szGateIPAddr[16];
char szIPAddr[16];
unsigned char ucPhysicalAddr[6];
unsigned char ucGatePhysicalAddr[6] = {0x78, 0x44, 0xfd, 0x22, 0xf7, 0x41};


//����Arp���ݰ�
BOOL SendArpPkt(pcap_t* adhandle)
{
    u_char ucFrame[ARP_LEN];

    //������̫��֡ͷ
    ETHeader eh = { 0 };

    memset(eh.dhost, 0xff, 6);//ARP�㲥��Ŀ�ĵ�ַΪffffffffffff

    memcpy(eh.shost, ucPhysicalAddr, 6);

    eh.type = htons(ETHERTYPE_ARP);//֡����ΪARP

    memcpy(ucFrame, &eh, sizeof(eh));


    // ����Arpͷ
    ARPHeader ah = { 0 };

    ah.hrd = htons(ARPHRD_ETHER);

    ah.eth_type = htons(ETHERTYPE_IP);

    ah.maclen = 6;//Ӳ����ַ����

    ah.iplen = 4;//IP��ַ����

    ah.opcode = htons(ARP_REQUEST);//ARP���������

    memcpy(ah.smac, ucPhysicalAddr, 6);

    ah.saddr = inet_addr(szIPAddr);

    memset(ah.dmac, 0x00, 6);//ARP�������Ŀ��MAC��ַ����0

    ah.daddr = inet_addr(szGateIPAddr);   //ARP�����Ŀ��IP��ַ

    memcpy(&ucFrame[sizeof(ETHeader)], &ah, sizeof(ah));


    if (pcap_sendpacket(adhandle,	// Adapter
        ucFrame,				// buffer with the packet
        ARP_LEN // size
        ) != 0)
    {
        fprintf(stderr, "\nError sending the packet: %s\n", pcap_geterr(adhandle));
        return FALSE;
    }

    return TRUE;
}



BOOL SendSYN(pcap_t* adhandle, char* pszDestIP, WORD dst_port)
{
    u_char ucFrame[SYN_LEN];

    u_char *pkt_data = ucFrame;
    ETHeader *eh;
    IPHeader *ih;
    TCPHeader *th;
    u_int ip_len;

    eh = (ETHeader *)pkt_data;
    ih = (IPHeader *)(pkt_data + 14);



    //������̫��֡ͷ
    memset(eh, 0, sizeof(ETHeader));
    memcpy(eh->dhost, ucGatePhysicalAddr, 6);//�������ص�mac��ַ

    memcpy(eh->shost, ucPhysicalAddr, 6);
    eh->type = htons(ETHERTYPE_IP);//֡����ΪIP

    // ����ipͷ��
    memset(ih, 0, sizeof(IPHeader));
    ih->iphVerLen = 0x45; //Э��汾��ͷ��
    ih->ipTOS = 0x00;//��������
    ih->ipLength = htons(SYN_LEN - sizeof(ETHeader));//�������ĳ���
    ih->ipID = 123;   //��ʶ
    ih->ipFlags = 0x0000; //��־λ����ƫ��
    ih->ipTTL = 128;  // ����ʱ�䣬��TTL
    ih->ipProtocol = PROTO_TCP;
    ih->ipChecksum = 0;//У���������0
    ih->ipSource = inet_addr(szIPAddr);  //Դip
    ih->ipDestination = inet_addr(pszDestIP); //Ŀ��ip

    ih->ipChecksum = htons(checksum((USHORT*)&ih, sizeof(ih))); //����������д��������дУ���

    ip_len = (ih->iphVerLen & 0xf) * 4;
    th = (TCPHeader *)((u_char*)ih + ip_len);

    // ����tcpͷ��
    memset(th, 0, sizeof(TCPHeader));
    
    srand(time(NULL));

    th->sourcePort = htons(rand() % 65535);//α�������Դ�˿�
    th->destinationPort = htons(dst_port);//Ŀ��˿�
    th->sequenceNumber = htonl(rand() % 65535);//���к�
    th->acknowledgeNumber = 0; //ȷ�Ϻ�
    th->dataoffset = 0x60;//��4λ��ʾ����ƫ��
    th->flags = 0x02; //��ʾSYN
    th->windows = htons(0x0c00);//���մ��ڴ�С
    th->checksum = 0; //tcpУ���������0
    th->urgentPointer = 0;//����ָ��

    // �õ�TCP���ݰ���ָ��ͳ���
    unsigned char *datatcp = (unsigned char *)ih + sizeof(_IPHeader)+sizeof(struct _TCPHeader);
    int lentcp = ntohs(ih->ipLength) - (sizeof(_IPHeader)+sizeof(_TCPHeader));

    //���ÿ�ѡͷ�����ݣ����а���MSS��ֵ
    char szOption[20] = {
                         0x02, 0x04, 0x05, 0xb4, 0x01,
                         0x03, 0x03, 0x02, 0x04, 0x02,
                         0x08, 0x0a, 0x00, 0x1c, 0xb4,
                         0x32, 0x00, 0x00, 0x00, 0x00
                        };
    memcpy(datatcp, szOption, 20);

    //���������У���
    ih->ipChecksum = 0;
    th->checksum = 0;
    ih->ipChecksum = checksum((USHORT *)ih, sizeof(_IPHeader));
    ComputeTcpPseudoHeaderChecksum(ih, th, (char *)datatcp, lentcp);

    //����һ��tcp SYN���ݰ�
    if (pcap_sendpacket(adhandle,	// Adapter
        ucFrame,				// buffer with the packet
        SYN_LEN // size
        ) != 0)
    {
        fprintf(stderr, "\nError sending the packet: %s\n", pcap_geterr(adhandle));
        return FALSE;
    }


    return TRUE;


}


int main(int argc, char **argv)
{
    pcap_if_t *alldevs;
    pcap_if_t *d;
    int inum;
    int i = 0;
    pcap_t *adhandle;
    char errbuf[PCAP_ERRBUF_SIZE];
    u_int netmask;
    //char packet_filter[] = "ip and tcp";
    struct bpf_program fcode;

    /* Retrieve the device list */
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
        exit(1);
    }

    /* Print the list */
    for (d = alldevs; d; d = d->next)
    {
        printf("%d. %s", ++i, d->name);
        if (d->description)
            printf(" (%s)\n", d->description);
        else
            printf(" (No description available)\n");
    }

    if (i == 0)
    {
        printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
        return -1;
    }

    printf("Enter the interface number (1-%d):", i);
    scanf("%d", &inum);

    /* Check if the user specified a valid adapter */
    if (inum < 1 || inum > i)
    {
        printf("\nAdapter number out of range.\n");

        /* Free the device list */
        pcap_freealldevs(alldevs);
        return -1;
    }

    /* Jump to the selected adapter */
    for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);

    char *p;
    if (d->addresses != NULL && (p = strchr(d->name, '{')) != NULL
        && Getadapterbyname(p, szIPAddr, ucPhysicalAddr, szGateIPAddr))
    {

        /* Open the adapter */
        if ((adhandle = pcap_open_live(d->name,	// name of the device
            65536,			// portion of the packet to capture. 
            // 65536 grants that the whole packet will be captured on all the MACs.
            1,				// promiscuous mode (nonzero means promiscuous)
            1000,			// read timeout
            errbuf			// error buffer
            )) == NULL)
        {
            fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n");
            /* Free the device list */
            pcap_freealldevs(alldevs);
            return -1;
        }
    }


    //
    //SendArpPkt(adhandle);

    //SendTcpPkt(adhandle);
    SendSYN(adhandle, "116.255.168.147", 80);

    pcap_close(adhandle);

	return 0;
}

