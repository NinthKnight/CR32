// TestHttp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SkyChaserHttp.h"
#include "URLCode.h"

#include <algorithm>
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

int test()
{
	CSkyChaserHttp http;
	string strRet;

	http.sc_setProxy("127.0.0.1:8081");

	http.sc_appendHeader("Connection: close");
	http.sc_appendHeader("Pragma: no-cache");
	http.sc_appendHeader("Cache-Control: no-cache");
	http.sc_appendHeader("Upgrade-Insecure-Requests: 1");
	http.sc_appendHeader("User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.84 Safari/537.36");
	http.sc_appendHeader("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*; q = 0.8");
	http.sc_appendHeader("Accept-Encoding: gzip, deflate");
	http.sc_appendHeader("Accept-Language: zh-CN,zh;q=0.9");

	string strPost = "account=123&password=202cb962ac59075b964b07152d234b70&NECaptchaValidate=rbzEMGyh0tGuQWWV8rCAXy7l4RX5kOVp2Ne2eeyURD_mSa99RDtd7Lc6Co-LHb2wZBqlPXyrq0lO060Q8bfZcmVcHR1aQtGKMePHog_sJWbqdNGJH2jqoDkmrWqEv5C8nhd9Q2OqKRueUgN_pos-PvvO72joGWRYz4T7XqB..ZIMoaAJAgn9fpS-LsJlqiL77Wto.9Gs5sDTP0KwKvzcGlN1dEdYDMn-.24M-r1cQQGP609iuFUyaAoRRkOF1vJyKgkJkQbzL4ned_WBwav7gQJuSvzLul4MQRZ5w7M2hy5paloKlz5XpraCrJrhJXrDp1z4xJoT-hrsqhZkNQEyZdXxVd1VqcbMxinVD2pYSo1ude0QQ8kfMMpr.jTEGI_5TBBOY4PN-w61MhNWJL7klX1djIXnraqFSPHSjodmiZkhlwG7VzVD2d2BSNt0EmGoVQ_HT801Z0R7IViG-drtaI8VD2616i7Mv7JPJ6Kbo0N_7B1QvlLMeXwdYnm3";

	CURLcode code = http.sc_get("https://kms.app/", strRet);
	if (code != CURLE_OK)
	{
		return 0;
	}

	//查找
	string strDst;
	int nIndex = CSkyChaserHttp::sc_getMidString(strRet, strDst, "<form id=\"Login_form\" action=\"", "\"", 0);
	if (nIndex == std::string::npos) {
		return 0;
	}

	strPost = "name=11231231&password=1221312321&referer=https%3A%2F%2Fkms.app";

	code = http.sc_post(strDst.c_str(), strPost.c_str(), strRet);
	if (code != CURLE_OK)
	{
		return 0;
	}
}

void StringToHex(BYTE *in, string& str, int nLength)
{
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


//获取RSA加密后的KEY
bool GetEncryptHashByC(string& strEncrypt, string pwd)
{
	unsigned char szDest[128] = { 0 };

	//这里AES key 首先写死...
	char szPlainText[16] = { 0x61, 0x6C, 0xFB, 0xBA, 0xAD, 0x80, 0x8C, 0x2A, 0x3D, 0x02, 0x70, 0xAF, 0xDE, 0xA0, 0x10, 0x97 };

	//MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDY7mpaUysvgQkbp0iIn2ezoUyhi1zPFn0HCXloLFWT7uoNkqtrphpQ/63LEcPz1VYzmDuDIf3iGxQKzeoHTiVMSmW6FlhDeqVOG094hFJvZeK4OzA6HVwzwnEW5vIZ7d+u61RV1bsFxmB68+8JXs3ycGcE4anY+YzZJcyOcEGKVQIDAQAB


	string strPublicKey =
		"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDY7mpaUysvgQkbp0iIn2ezoUyh\n"
		"i1zPFn0HCXloLFWT7uoNkqtrphpQ/63LEcPz1VYzmDuDIf3iGxQKzeoHTiVMSmW6\n"
		"FlhDeqVOG094hFJvZeK4OzA6HVwzwnEW5vIZ7d+u61RV1bsFxmB68+8JXs3ycGcE\n"
		"4anY+YzZJcyOcEGKVQIDAQAB";

	int nPublicKeyLen = strPublicKey.size();      //strPublicKey为base64编码的公钥字符串


	strPublicKey.insert(0, "-----BEGIN PUBLIC KEY-----\n");
	strPublicKey.append("\n-----END PUBLIC KEY-----\n");

	BIO *bio = NULL;
	RSA *rsa = NULL;
	char *chPublicKey = const_cast<char *>(strPublicKey.c_str());
	if ((bio = BIO_new_mem_buf(chPublicKey, -1)) == NULL)       //从字符串读取RSA公钥
	{
		//cout << "BIO_new_mem_buf failed!" << endl;
		OutputDebugStringA("BIO_new_mem_buf failed!");
	}
	rsa = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);   //从bio结构中得到rsa结构
	if (!rsa)
	{
		//ERR_load_crypto_strings();
		//char errBuf[512];
		//ERR_error_string_n(ERR_get_error(), errBuf, sizeof(errBuf));
		//cout << "load public key failed[" << errBuf << "]" << endl;
		BIO_free_all(bio);
		return false;
	}

	int flen = RSA_size(rsa); // RSA密钥长度

							  //公钥加密
							  //最后一个参数是补齐方式，文档中一共四种（头文件里宏比四种多）
	RSA_public_encrypt(pwd.length(), (unsigned char*)pwd.c_str(), (unsigned char*)szDest, rsa, RSA_PKCS1_PADDING);

	StringToHex(szDest, strEncrypt, flen);

	//释放资源
	RSA_free(rsa);

	return true;
}

int main()
{
	InitDll();

	//1. 获取image token
	CSkyChaserHttp http;
	string strRet;

	http.sc_setProxy("127.0.0.1:8081");

	http.sc_appendHeader("Connection: close");
	http.sc_appendHeader("Pragma: no-cache");
	http.sc_appendHeader("Cache-Control: no-cache");
	http.sc_appendHeader("Upgrade-Insecure-Requests: 1");
	http.sc_appendHeader("User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.84 Safari/537.36");
	http.sc_appendHeader("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*; q = 0.8");
	http.sc_appendHeader("Accept-Encoding: gzip, deflate");
	http.sc_appendHeader("Accept-Language: zh-CN,zh;q=0.9");

	
	CURLcode code = http.sc_get("https://mail.21cn.com/w2/logon/UnifyLogin.do?t=1541754779154", strRet);
	if (code != CURLE_OK)
	{
		return 0;
	}

	string strDst;
	int nIndex = CSkyChaserHttp::sc_getMidString(strRet, strDst, "'captchaToken' value='", "'", 0);
	if (nIndex == std::string::npos) {
		return 0;
	}

	//获取验证码的图片
	//Referer: https://open.e.189.cn/api/logbox/oauth2/unifyAccountLogin.do?appId=8013411507&version=v1.5&clientType=10010&paras=389B3EC24E8E36F6857C85FC30658492C88932ACA80689E5178CA3E2D814F083E16200A5139D0F6C7D26748FB76965CF82F2B99085129BB021EA5D86635F80212B27FB654790F8B9A83B9D8CA39033BA718CF3541383711025161AA44194FAC8A47EC9E00E973EF5F36AD35E655ECAF4CB4FACE653FA7343E526AEC10D8D76CCEF141EDC5B2E6D180430FCBC52002CC5E0B2E8D8C09FF862EA86FCDF3EADCA2DF03295A147C7F4CCD338E3EA0383E3F0F03F91197727B19C95946C384D0EE8426F7C6D2C&sign=E70330EF7887CB39D487491762C030DBE1A56EE5&format=redirect
	
	http.sc_appendHeader("Referer: https://open.e.189.cn/api/logbox/oauth2/unifyAccountLogin.do?appId=8013411507&version=v1.5&clientType=10010&paras=389B3EC24E8E36F6857C85FC30658492C88932ACA80689E5178CA3E2D814F083E16200A5139D0F6C7D26748FB76965CF82F2B99085129BB021EA5D86635F80212B27FB654790F8B9A83B9D8CA39033BA718CF3541383711025161AA44194FAC8A47EC9E00E973EF5F36AD35E655ECAF4CB4FACE653FA7343E526AEC10D8D76CCEF141EDC5B2E6D180430FCBC52002CC5E0B2E8D8C09FF862EA86FCDF3EADCA2DF03295A147C7F4CCD338E3EA0383E3F0F03F91197727B19C95946C384D0EE8426F7C6D2C&sign=E70330EF7887CB39D487491762C030DBE1A56EE5&format=redirect");
	
	string strUrl;
	strUrl = "https://open.e.189.cn/api/logbox/oauth2/picCaptcha.do?token=" + strDst + "&rnd=1541756274298";

	code = http.sc_get(strUrl.c_str(), strRet);
	if (code != CURLE_OK)
	{
		return 0;
	}

	//http.sc_deleteHeader("Referer:");

	char aryCode[256] = {0};
	int n = g_Func21Ocr((BYTE*)strRet.c_str(), strRet.length(), aryCode);


	string strPwd = "paocn4507";
	string strEncodedPwd = "";
	bool bRet = GetEncryptHashByC(strEncodedPwd, strPwd);

	//发送登录包

	//查找
	string strPost = "appKey=8013411507&accountType=02&userName=";
	strPost += "dafen54945%4021cn.com";
	strPost += "&validateCode=";
	strPost += aryCode;
	strPost += "&captchaToken=";
	strPost += strDst;
	strPost += "&returnUrl=http%3A%2F%2Fmail.21cn.com%2Fw2%2Flogon%2FunifyPlatformLogonReturn.do%3FLSID%3DaIFFFdArUGA_OlbT3B&mailSuffix=&dynamicCheck=FALSE&clientType=10010&cb_SaveName=0&isOauth2=false&state=&password=%7BRSA%7D";
	//strPost += "caedb7d33059e099f2a32cc0938af4f4da06e65d56f12165e9d24d0bbd6b1c353fdefb4748b3884ecf29b1d1d5fb63ea37cc3ccc39947b9f219c8a57aae07500c80bc2ad982a446cee650f986910282405af79987668f85e5a4fcd2e496741ec3a1fb56e52f5cc24be9cf593d7d34650b302264fdb6963fb8745e9e01432db72";
	strPost += strEncodedPwd;
	code = http.sc_post("https://open.e.189.cn/api/logbox/oauth2/loginSubmit.do", strPost.c_str(), strRet);
	if (code != CURLE_OK)
	{
		return 0;
	}


	return 0;
}

