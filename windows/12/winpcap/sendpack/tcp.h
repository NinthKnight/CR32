
//计算效验和函数，先把IP首部的效验和字段设为0(IP_HEADER.checksum=0)
//然后计算整个IP首部的二进制反码的和。
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
// 计算TCP检验和的函数
// 这个函数超级有用,起关键性的作用
// 
void ComputeTcpPseudoHeaderChecksum(IPHeader    *pIphdr, TCPHeader *pTcphdr,
    char *payload, int payloadlen)
{
	
	char *buff = (char *) malloc(1024+payloadlen);
	char *ptr=buff;

	int chksumlen = 0;
	ULONG zero = 0;
	
	// 伪头
	// 包含源IP地址和目的IP地址
	memcpy(ptr, &pIphdr->ipSource, sizeof(pIphdr->ipSource));
	ptr += sizeof(pIphdr->ipSource);
	chksumlen += sizeof(pIphdr->ipSource);

	memcpy(ptr, &pIphdr->ipDestination, sizeof(pIphdr->ipDestination));
	ptr += sizeof(pIphdr->ipDestination);
	chksumlen += sizeof(pIphdr->ipDestination);

	// 包含8位0域
	memcpy(ptr, &zero, 1);
	ptr += 1;
	chksumlen += 1;

	// 协议
	memcpy(ptr, &pIphdr->ipProtocol, sizeof(pIphdr->ipProtocol));
	ptr += sizeof(pIphdr->ipProtocol);
	chksumlen += sizeof(pIphdr->ipProtocol);

	// TCP长度
	USHORT tcp_len = htons(sizeof(TCPHeader) + payloadlen);
	memcpy(ptr, &tcp_len, sizeof(tcp_len));
	ptr += sizeof(tcp_len);
	chksumlen += sizeof(tcp_len);

		// TCP头
	memcpy(ptr, pTcphdr, sizeof(TCPHeader));
	ptr += sizeof(TCPHeader);
	chksumlen += sizeof(TCPHeader);

		// 净荷
	memcpy(ptr, payload, payloadlen);
	ptr += payloadlen;
	chksumlen += payloadlen;

	// 补齐到下一个16位边界
	for(int i=0; i < payloadlen % 2; i++)
	{
		*ptr = 0;
		ptr ++;
		chksumlen ++;
	}

	// 计算这个校验和，将结果填充到TCP头
	pTcphdr->checksum = checksum((USHORT*) buff, chksumlen);
}