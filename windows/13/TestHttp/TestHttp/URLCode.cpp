#include "stdafx.h"
#include "URLCode.h"
#include <windows.h>


//byte* ×ª×Ö·û´®
void CURLCode::StringToHex(BYTE *in, string& str, int nLength)
{
	str = "";
	BYTE high, low;
	while (nLength-- > 0)
	{
		high = (*in) >> 4;
		low = (*in) & 0xF;
		str += high > 9 ? high - 10 + 'a' : high + '0';
		str += low > 9 ? low - 10 + 'a' : low + '0';
		in++;
	}
	str += '\0';
}

string CURLCode::Encode(const wchar_t* lpszData)
{
	string strResult = "";

	unsigned char* pInTmp = (unsigned char*)lpszData;
	// do encoding
	while (*pInTmp)
	{
		if (isalnum(*pInTmp))
			strResult += *pInTmp;
		else
		if (isspace(*pInTmp))
			strResult += '+';
		else
		{
			strResult += '%';
			strResult += toHex(*pInTmp >> 4);
			strResult += toHex(*pInTmp % 16);
		}
		pInTmp++;
	}
	return strResult;
}

string CURLCode::MyEncode(const char* lpszData)
{
	string strResult = "";

	unsigned char* pInTmp = (unsigned char*)lpszData;
	// do encoding
	while (*pInTmp)
	{
		if (isalnum(*pInTmp))
			strResult += *pInTmp;
		else
		if (isspace(*pInTmp))
			strResult += '+';
		else
		{
			strResult += "%25";
			strResult += toHex(*pInTmp >> 4);
			strResult += toHex(*pInTmp % 16);
		}
		pInTmp++;
	}
	return strResult;
}

string CURLCode::Decode(string inTmp)
{
	string strResult = "";
	int inlen = inTmp.length();
	for (int i = 0; i<inlen; i++)
	{
		if (inTmp.at(i) == '%')
		{
			i++;
			char c = fromHex(inTmp.at(i++));
			c = c << 4;
			c += fromHex(inTmp.at(i));
			strResult += c;
		}
		else if (inTmp.at(i) == '+')
			strResult += ' ';
		else
			strResult += inTmp.at(i);
	}
	return strResult;
}

string CURLCode::myDecode(const wchar_t* lpszData)
{
	string strResult = "";
	int nLength = wcslen(lpszData) * 2 + 1;

	unsigned char* pInTmp = (unsigned char*)lpszData;

	while (*pInTmp)
	{
		strResult += *pInTmp;

		pInTmp++;
		pInTmp++;
	}

	return strResult;
}