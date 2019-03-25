//////////////////////////////////////////////////
// protoinfo.h�ļ�

/*

����Э���ʽ
����Э����ʹ�õĺ�

*/


#ifndef __PROTOINFO_H__
#define __PROTOINFO_H__


#define ETHERTYPE_IP    0x0800
#define ETHERTYPE_ARP   0x0806
#define ARP_REQUEST  0x0001
#define	ARP_REPLY	 0x0002			/* ARP reply */
#define ARPHRD_ETHER 	1
#define ARP_LEN		 48
#define SYN_LEN      74
// Э��
#define PROTO_TCP     6

typedef struct ip_address
{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
}ip_address;

#pragma pack(push, 1)//ȡ���ڴ��С�Զ�����

typedef struct _ETHeader         // 14�ֽڵ���̫ͷ
{
	UCHAR	dhost[6];			// Ŀ��MAC��ַdestination mac address
	UCHAR	shost[6];			// ԴMAC��ַsource mac address
	USHORT	type;				// �²�Э�����ͣ���IP��ETHERTYPE_IP����ARP��ETHERTYPE_ARP����
} ETHeader, *PETHeader;

typedef struct _ARPHeader		// 28�ֽڵ�ARPͷ
{
	USHORT	hrd;				//	Ӳ����ַ�ռ䣬��̫����ΪARPHRD_ETHER
	USHORT	eth_type;			//  ��̫�����ͣ�ETHERTYPE_IP ����
	UCHAR	maclen;				//	MAC��ַ�ĳ��ȣ�Ϊ6
	UCHAR	iplen;				//	IP��ַ�ĳ��ȣ�Ϊ4
	USHORT	opcode;				//	�������룬ARPOP_REQUESTΪ����ARPOP_REPLYΪ��Ӧ
	UCHAR	smac[6];			//	ԴMAC��ַ
	ULONG	saddr;			//	ԴIP��ַ
	UCHAR	dmac[6];			//	Ŀ��MAC��ַ
	ULONG	daddr;			//	Ŀ��IP��ַ
} ARPHeader, *PARPHeader;

typedef struct _IPHeader		// 20�ֽڵ�IPͷ
{
    UCHAR     iphVerLen;      // �汾�ź�ͷ���ȣ���ռ4λ��
    UCHAR     ipTOS;          // �������� 
    USHORT    ipLength;       // ����ܳ��ȣ�������IP���ĳ���
    USHORT    ipID;			  // �����ʶ��Ωһ��ʶ���͵�ÿһ�����ݱ�
    USHORT    ipFlags;	      // ��־
    UCHAR     ipTTL;	      // ����ʱ�䣬����TTL
    UCHAR     ipProtocol;     // Э�飬������TCP��UDP��ICMP��
    USHORT    ipChecksum;     // У���
	union {
		unsigned int   ipSource;
		ip_address ipSourceByte;
	};
	union {
		unsigned int   ipDestination;
		ip_address ipDestinationByte;
	};
} IPHeader, *PIPHeader; 

typedef struct _TCPHeader		// 20�ֽڵ�TCPͷ
{
	USHORT	sourcePort;			// 16λԴ�˿ں�
	USHORT	destinationPort;	// 16λĿ�Ķ˿ں�
	ULONG	sequenceNumber;		// 32λ���к�
	ULONG	acknowledgeNumber;	// 32λȷ�Ϻ�
	UCHAR	dataoffset;			// ��4λ��ʾ����ƫ��
	UCHAR	flags;				// 6λ��־λ
								//FIN - 0x01
								//SYN - 0x02
								//RST - 0x04 
								//PUSH- 0x08
								//ACK- 0x10
								//URG- 0x20
								//ACE- 0x40
								//CWR- 0x80

	USHORT	windows;			// 16λ���ڴ�С
	USHORT	checksum;			// 16λУ���
	USHORT	urgentPointer;		// 16λ��������ƫ���� 
} TCPHeader, *PTCPHeader;

#endif // __PROTOINFO_H__
#pragma pack(pop)

