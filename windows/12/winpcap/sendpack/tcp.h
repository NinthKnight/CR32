
//����Ч��ͺ������Ȱ�IP�ײ���Ч����ֶ���Ϊ0(IP_HEADER.checksum=0)
//Ȼ���������IP�ײ��Ķ����Ʒ���ĺ͡�
USHORT checksum(USHORT *buffer, int size)
{
       unsigned long cksum=0;
       while (size >1) {
              cksum+=*buffer++;
              size-=sizeof(USHORT);
       }
       if (size) cksum += *(UCHAR*) buffer;
       cksum = (cksum >> 16) + (cksum&0xffff);
       cksum += (cksum >> 16);
       return (USHORT) (~cksum); 
}

//
// ����TCP����͵ĺ���
// ���������������,��ؼ��Ե�����
// 
void ComputeTcpPseudoHeaderChecksum(IPHeader    *pIphdr, TCPHeader *pTcphdr,
    char *payload, int payloadlen)
{
	
	char *buff = (char *) malloc(1024+payloadlen);
	char *ptr=buff;

	int chksumlen = 0;
	ULONG zero = 0;
	
	// αͷ
	// ����ԴIP��ַ��Ŀ��IP��ַ
	memcpy(ptr, &pIphdr->ipSource, sizeof(pIphdr->ipSource));
	ptr += sizeof(pIphdr->ipSource);
	chksumlen += sizeof(pIphdr->ipSource);

	memcpy(ptr, &pIphdr->ipDestination, sizeof(pIphdr->ipDestination));
	ptr += sizeof(pIphdr->ipDestination);
	chksumlen += sizeof(pIphdr->ipDestination);

	// ����8λ0��
	memcpy(ptr, &zero, 1);
	ptr += 1;
	chksumlen += 1;

	// Э��
	memcpy(ptr, &pIphdr->ipProtocol, sizeof(pIphdr->ipProtocol));
	ptr += sizeof(pIphdr->ipProtocol);
	chksumlen += sizeof(pIphdr->ipProtocol);

	// TCP����
	USHORT tcp_len = htons(sizeof(TCPHeader) + payloadlen);
	memcpy(ptr, &tcp_len, sizeof(tcp_len));
	ptr += sizeof(tcp_len);
	chksumlen += sizeof(tcp_len);

		// TCPͷ
	memcpy(ptr, pTcphdr, sizeof(TCPHeader));
	ptr += sizeof(TCPHeader);
	chksumlen += sizeof(TCPHeader);

		// ����
	memcpy(ptr, payload, payloadlen);
	ptr += payloadlen;
	chksumlen += payloadlen;

	// ���뵽��һ��16λ�߽�
	for(int i=0; i < payloadlen % 2; i++)
	{
		*ptr = 0;
		ptr ++;
		chksumlen ++;
	}

	// �������У��ͣ��������䵽TCPͷ
	pTcphdr->checksum = checksum((USHORT*) buff, chksumlen);
}