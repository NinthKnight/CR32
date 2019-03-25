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

	http.sc_setProxy("127.0.0.1:8888");

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

typedef int(__stdcall  *PFN_OCR)(char* pBuf, int nLength, char* pOut);

int main()
{
	//1. 获取image token
    //加载dll
    HMODULE hDll = LoadLibraryA("21cnOCR.dll");
     
    PFN_OCR pfn = (PFN_OCR)GetProcAddress(hDll, "OCR_E");

    //获取验证码图片，并开始识别

    

    CSkyChaserHttp http;
	string strRet;

	http.sc_setProxy("127.0.0.1:8080");

	http.sc_appendHeader("Connection: close");
	http.sc_appendHeader("Pragma: no-cache");
	http.sc_appendHeader("Cache-Control: no-cache");
	http.sc_appendHeader("Upgrade-Insecure-Requests: 1");
	http.sc_appendHeader("User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.84 Safari/537.36");
	http.sc_appendHeader("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*; q = 0.8");
	http.sc_appendHeader("Accept-Encoding: gzip, deflate");
	http.sc_appendHeader("Accept-Language: zh-CN,zh;q=0.9");

    string captchaToken;
    string paramId;
    string lt;

    http.sc_get("http://mail.21cn.com/w2/logon/UnifyLogin.do?t=1551949065466", strRet);
    http.sc_getMidString(strRet, captchaToken, "'captchaToken' value='", "'", 0);

    http.sc_getMidString(strRet, paramId, "var paramId = \"", "\"", 0);

    http.sc_getMidString(strRet, lt, "var lt = \"", "\"", 0);

    //拿验证码
    http.sc_appendHeader("Referer: https://open.e.189.cn/api/logbox/oauth2/unifyAccountLogin.do?appId=8013411507&version=v1.5&clientType=10010&paras=8406BF4796D2CFF09B59DD5D6720AFD2A97017FC5C1F5B4A754C5BBCBBCDA4E29442097E2D31890C5CC5B1DCA7FD749BF47B440E51756566536E960E2C9431EF32F6CF1D498D299A2F253D3B070EFCC3AE49036193FC8A07672F0A49B770CBBD9ECC777EF66375EA39CCF3829B7C2A5BFD5BC2A556BAF3B2DEF498421DEA9970E829F0B0583BFA4EBC428DB7330C7CC2AD026D567A98A05C3B4D783B6C2254A98B8D0AF9A8058AE91E1CAABEF63D5D7F3EEA8C332B02E5AD1D89AA8E037E6B1757CF79A3&sign=8DCD11D89698F164F39F04B653D66FAA216730C0&format=redirect");
    string strurl = "https://open.e.189.cn/api/logbox/oauth2/picCaptcha.do?token=";
    strurl += captchaToken;
    strurl += "&rnd=1551952984204";
    http.sc_get(strurl.c_str(), strRet);

    char pCode[256];
    pfn((char*)strRet.c_str(), strRet.length(), pCode);

    string encPwd;

    bool bRet = GetEncryptHashByC(encPwd, "yangsw92099");

    string strPostData = "appKey=8013411507&accountType=02&userName=juhuai4070%4021cn.com";
    strPostData += "&validateCode=";
    strPostData += pCode;
    strPostData += "&captchaToken=";
    strPostData += captchaToken;
    strPostData += "&returnUrl=http%3A%2F%2Fmail.21cn.com%2Fw2%2Flogon%2FunifyPlatformLogonReturn.do%3FLSID%3DavPrIJ-fvyr_ZSkexL&mailSuffix=&dynamicCheck=FALSE&clientType=10010&cb_SaveName=0&isOauth2=false&state=&paramId=";
    strPostData += paramId;
    strPostData += "&lt=";
    strPostData += lt;
    strPostData += "&password=%7BRSA%7D";
    strPostData += encPwd;

    http.sc_post("https://open.e.189.cn/api/logbox/oauth2/loginSubmit.do", strPostData.c_str(), strRet);

	return 0;
}

