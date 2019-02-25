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

	// ����cookie�ļ�
	void sc_setCookieFile( const char * sFilename );
	// ����COOKIES
	void sc_setCookie( const char * sName, const char * sValue );
    // ����COOKIES��ֵ,�����sName�Ļ�
    void sc_replaceCookie(const char * sName, const char * sValue);
	// ���COOKIES
	void sc_cleanExCookie();
	// ��ȡָ��Cookieֵ
	std::string sc_getCookie( const char * sCookieName );
	// ��ȡ���е�Cookies
	std::string sc_getCookie();
	// ɾ��Cookies�ļ�
	void sc_delCookieFile(void);

    string sc_convertCookie(string& strSrc);

    //ȡ���ض���302
    void sc_cancelFollowaction();

    //�����ض���302
    void sc_setFollowaction();

    CURLcode sc_getInfo(CURLINFO info, char*& url);

	// ���Httpͷ
	void sc_cleanHeader();
	// ���Httpͷ
	void sc_appendHeader( const char * sHeader );
	//ɾ��Httpͷ
	void sc_deleteHeader(const char * sHeader);
	bool curl_header_delete(struct curl_slist **csl_head, const char *data);

	// GET  sFileName == NULL ? �����ܷ�������
	CURLcode sc_get( const char * sURL, const wchar_t * sFileName = NULL, bool bCaseRepHdr = false );
	// GET
	CURLcode sc_get( const char * sURL, std::string & sRet, bool bCaseRepHdr = false );
	// POST  sFileName == NULL ? �����ܷ�������
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

	// ���ó�ʱʱ��
	void sc_setTimeOut( int nTimeOutMillisecond );
	// ���ô���
	void sc_setProxy( const char * sProxy, char * sPass = NULL, curl_proxytype ntype = CURLPROXY_HTTP );
	
	// ��ȡ�ļ���string
	static bool sc_readTextFile( const wchar_t * sFileName, string & sRet );
	// ��ȡʱ���
	static std::string sc_getTimeStamp( int nOffest = 0 );
	// д��־�ļ�
	static bool sc_writeLog( const wchar_t * sFile, const char * sText );
	// ��ȡ�м��ַ���
	static int sc_getMidString( string src, string & dst, const char * sLeft, const char * sRight, int nStart );
	// �ַ����ָ��
	static int sc_split( string str, string pattern, vector<string> & xRet );
	// �滻
	static void sc_replace( string & str, const char * sRp, const char * sTo );

	// ת��
	static void sc_utf8ToAnsi( string & str );
	static void sc_ansiToUtf8( string & str );
	static void sc_ansiToUnicode( const string & str, wstring & sUnicode );
	static void sc_unicodeToAnsi( const wstring & sUnicode, string & str );
	static void sc_utf8ToUnicode( const string & sUtf8, wstring & sUnicode );
	static void sc_unicodeToUtf8( const wstring & sUnicode, string & sUtf8 );

	// URL����/����
	static bool sc_urlEncodeUtf8( string & strUtf8Data, bool bUpperCase = true );
	static bool sc_urlEncodeAnsi( string & strAnsiData, bool bUpperCase = true );
	static bool sc_urlDecodeUtf8( string & strUtf8Data );
	static bool sc_urlDecodeAnsi( string & strAnsiData );

	// BASE 64
	static string sc_base64Decode( const char *s, int len );
	static string sc_base64Encode( const char *b, int len );

	//����OPENSSL���߳�ͬ������
#ifdef USE_OPENSSL  
	#define NUMT 4
	static unsigned long __cdecl thread_id(void);
	static CRITICAL_SECTION* lockarray;
	static void __cdecl lock_callback(int mode, int type, char *file, int line);
	static void __cdecl init_locks(void);
	static void __cdecl kill_locks(void);
#endif  

	// �첽����
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

	// �첽����
	bool m_isMulti;
};

#endif