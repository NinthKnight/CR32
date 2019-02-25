#ifndef  _LIB_SKY_CHASER_HTTP_
#define _LIB_SKY_CHASER_HTTP_

#ifdef	 _SKY_CHASER_HTTP_IMP_
#define _SKY_CHASER_HTTP_API_		__declspec(dllimport)
#else
#define _SKY_CHASER_HTTP_API_		__declspec(dllexport)
#endif

#include "stdafx.h"
#ifdef USE_OPENSSL  
#include <openssl/crypto.h> 
#endif  

#include "curl/curl.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <map>
using std::string;
using std::wstring;
using std::vector;
using std::map;



class _SKY_CHASER_HTTP_API_ CSkyChaserHttp
{
public:
	//CSkyChaserHttp(void);
	~CSkyChaserHttp(void);
	CSkyChaserHttp(bool isMulti = false);

	// 设置cookie文件
	void sc_setCookieFile( const char * sFilename );
	// 设置COOKIES
	void sc_setCookie( const char * sName, const char * sValue );
    // 重置COOKIES的值,如果有sName的话
    void sc_replaceCookie(const char * sName, const char * sValue);
	// 清除COOKIES
	void sc_cleanExCookie();
	// 获取指定Cookie值
	std::string sc_getCookie( const char * sCookieName );
	// 获取所有的Cookies
	std::string sc_getCookie();
	// 删除Cookies文件
	void sc_delCookieFile(void);

    string sc_convertCookie(string& strSrc);

    //取消重定向302
    void sc_cancelFollowaction();

    //设置重定向302
    void sc_setFollowaction();

    CURLcode sc_getInfo(CURLINFO info, char*& url);

	// 清空Http头
	void sc_cleanHeader();
	// 添加Http头
	void sc_appendHeader( const char * sHeader );
	//删除Http头
	void sc_deleteHeader(const char * sHeader);
	bool curl_header_delete(struct curl_slist **csl_head, const char *data);

	// GET  sFileName == NULL ? 不接受返回数据
	CURLcode sc_get( const char * sURL, const wchar_t * sFileName = NULL, bool bCaseRepHdr = false );
	// GET
	CURLcode sc_get( const char * sURL, std::string & sRet, bool bCaseRepHdr = false );
	// POST  sFileName == NULL ? 不接受返回数据
	CURLcode sc_post( const char * sURL, const char * sData, const wchar_t * sFileName = NULL, bool bCaseRepHdr = false );
	// POST
	CURLcode sc_post( const char * sURL, const char * sData, std::string & sRet, bool bCaseRepHdr = false );
	// POST PIC
	CURLcode sc_post( const char * sURL, const char * sFieldName, const char * sFileName, std::string & sRet, bool bCaseRepHdr = false );
	// PUT
	CURLcode sc_put( const char * sURL, const char * sData, std::string & sRet, bool bCaseRepHdr = false );

    long sc_getResponseCode() {
        long retcode = 0;
        curl_easy_getinfo(m_hCurl, CURLINFO_RESPONSE_CODE, &retcode);
        return retcode;
    }

	// 设置超时时间
	void sc_setTimeOut( int nTimeOutMillisecond );
	// 设置代理
	void sc_setProxy( const char * sProxy, char * sPass = NULL, curl_proxytype ntype = CURLPROXY_HTTP );
	
	// 读取文件到string
	static bool sc_readTextFile( const wchar_t * sFileName, string & sRet );
	// 获取时间戳
	static std::string sc_getTimeStamp( int nOffest = 0 );
	// 写日志文件
	static bool sc_writeLog( const wchar_t * sFile, const char * sText );
	// 截取中间字符串
	static int sc_getMidString( string src, string & dst, const char * sLeft, const char * sRight, int nStart );
	// 字符串分割函数
	static int sc_split( string str, string pattern, vector<string> & xRet );
	// 替换
	static void sc_replace( string & str, const char * sRp, const char * sTo );

	// 转码
	static void sc_utf8ToAnsi( string & str );
	static void sc_ansiToUtf8( string & str );
	static void sc_ansiToUnicode( const string & str, wstring & sUnicode );
	static void sc_unicodeToAnsi( const wstring & sUnicode, string & str );
	static void sc_utf8ToUnicode( const string & sUtf8, wstring & sUnicode );
	static void sc_unicodeToUtf8( const wstring & sUnicode, string & sUtf8 );

	// URL编码/解码
	static bool sc_urlEncodeUtf8( string & strUtf8Data, bool bUpperCase = true );
	static bool sc_urlEncodeAnsi( string & strAnsiData, bool bUpperCase = true );
	static bool sc_urlDecodeUtf8( string & strUtf8Data );
	static bool sc_urlDecodeAnsi( string & strAnsiData );

	// BASE 64
	static string sc_base64Decode( const char *s, int len );
	static string sc_base64Encode( const char *b, int len );

	//处理OPENSSL多线程同步问题
#ifdef USE_OPENSSL  
	#define NUMT 4
	static unsigned long __cdecl thread_id(void);
	static CRITICAL_SECTION* lockarray;
	static void __cdecl lock_callback(int mode, int type, char *file, int line);
	static void __cdecl init_locks(void);
	static void __cdecl kill_locks(void);
#endif  

	// 异步新增
	inline void* get_handle()
	{
		return m_hCurl;
	}

private:
	void			*		m_hCurl;
	char			*		m_szCookie;
	struct curl_slist	*	m_header;
	map<string, string> * m_pCookieEx;
	static size_t _callBackWriteFile( void * buffer, size_t size, size_t nmemb, void * usrFp );
	static size_t _callBackWriteString(void * buffer, size_t size, size_t nmemb, void * usrFp);
	static size_t _callBackNotCase(void * buffer, size_t size, size_t nmemb, void * usrFp);

	static string _base64DecodeRaw( const char *b, const char *e );
	static string _base64EncodeRaw( const char *b, const char *e );
	void _checkExCookies();

	// 异步新增
	bool m_isMulti;
};

#endif