// TestCharkraDll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <ChakraCore.h>
//#include <boost/uuid/uuid.hpp>
//#include <boost/uuid/uuid_io.hpp>
//#include <boost/uuid/uuid_generators.hpp>


#pragma comment(lib, "ChakraCore.lib")
#include <string>
#include <iostream>
#include <stdlib.h>

#include "Chakra.h"

using namespace std;

string str = R"(var navigator={};function LeyBc(t){n=compressToBase64(t);return n}base64Table="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";function compressToBase64(t){if(null==t)return"";var n=_compress(t,6,function(t){return base64Table.charAt(t)});switch(n.length%4){default:case 0:return n;case 1:return n+"===";case 2:return n+"==";case 3:return n+"="}};function _compress(t,e,n){if(null==t)return"";var r,i,o,a={},u={},s="",c="",f="",l=2,h=3,d=2,p=[],g=0,v=0;for(o=0;o<t.length;o+=1)if(s=t.charAt(o),Object.prototype.hasOwnProperty.call(a,s)||(a[s]=h++,u[s]=!0),c=f+s,Object.prototype.hasOwnProperty.call(a,c))f=c;else{if(Object.prototype.hasOwnProperty.call(u,f)){if(f.charCodeAt(0)<256){for(r=0;r<d;r++)g<<=1,v==e-1?(v=0,p.push(n(g)),g=0):v++;for(i=f.charCodeAt(0),r=0;r<8;r++)g=g<<1|1&i,v==e-1?(v=0,p.push(n(g)),g=0):v++,i>>=1}else{for(i=1,r=0;r<d;r++)g=g<<1|i,v==e-1?(v=0,p.push(n(g)),g=0):v++,i=0;for(i=f.charCodeAt(0),r=0;r<16;r++)g=g<<1|1&i,v==e-1?(v=0,p.push(n(g)),g=0):v++,i>>=1}0==--l&&(l=Math.pow(2,d),d++),delete u[f]}else for(i=a[f],r=0;r<d;r++)g=g<<1|1&i,v==e-1?(v=0,p.push(n(g)),g=0):v++,i>>=1;0==--l&&(l=Math.pow(2,d),d++),a[c]=h++,f=String(s)}if(""!==f){if(Object.prototype.hasOwnProperty.call(u,f)){if(f.charCodeAt(0)<256){for(r=0;r<d;r++)g<<=1,v==e-1?(v=0,p.push(n(g)),g=0):v++;for(i=f.charCodeAt(0),r=0;r<8;r++)g=g<<1|1&i,v==e-1?(v=0,p.push(n(g)),g=0):v++,i>>=1}else{for(i=1,r=0;r<d;r++)g=g<<1|i,v==e-1?(v=0,p.push(n(g)),g=0):v++,i=0;for(i=f.charCodeAt(0),r=0;r<16;r++)g=g<<1|1&i,v==e-1?(v=0,p.push(n(g)),g=0):v++,i>>=1}0==--l&&(l=Math.pow(2,d),d++),delete u[f]}else for(i=a[f],r=0;r<d;r++)g=g<<1|1&i,v==e-1?(v=0,p.push(n(g)),g=0):v++,i>>=1;0==--l&&(l=Math.pow(2,d),d++)}for(i=2,r=0;r<d;r++)g=g<<1|1&i,v==e-1?(v=0,p.push(n(g)),g=0):v++,i>>=1;for(;;){if(g<<=1,v==e-1){p.push(n(g));break}v++}return p.join("")};LeyBc(data))";
string strCode = R"+*({"uuid":"%s","version":"0.5.1","isTouchDevice":false,"keyStrokes":[{"id":"id","inputIntervalLogs":[{"a":0,"c":"%s","d":0}],"keyStrokeLogs":[{"a":0,"b":"d","c":"CTRL","d":"17"},{"a":127,"b":"d","c":"i0","d":"86"},{"a":151,"b":"u","c":"CTRL","d":"17"},{"a":162,"b":"u","c":"i0","d":"86"}],"initialValue":"jazz1065","completeValue":"nolbu333","e":false},{"id":"pw","inputIntervalLogs":[{"a":0,"c":"","d":0}],"keyStrokeLogs":[{"a":0,"b":"d","c":"CTRL","d":""},{"a":113,"b":"d","c":"i0","d":""},{"a":114,"b":"u","c":"CTRL","d":""},{"a":136,"b":"u","c":"i0","d":""}],"initialValue":"","completeValue":"","e":true}],"orientations":{"firstOrientation":{"a":444,"b":444,"c":444},"lastOrientation":{"a":444,"b":444,"c":444}},"motions":{"firstMotion":{"acceleration":{"a":444,"b":444,"c":444},"accelerationIncludingGravity":{"a":444,"b":444,"c":444}},"lastMotion":{"acceleration":{"a":444,"b":444,"c":444},"accelerationIncludingGravity":{"a":444,"b":444,"c":444}}},"mouse":["10|0|17|-7|4","11|0|19|-8|2","12|0|14|-8|1","13|0|19|-5|0","14|0|15|-2|0","15|0|49|-10|8","16|0|18|-4|6","17|0|15|-2|8","18|0|17|0|5","19|0|18|0|1","20|0|250|-1|1","21|0|16|-2|0","22|0|17|-2|-2","23|0|16|-4|-3","24|0|17|-9|-5","25|0|16|-11|-6","26|0|17|-10|-4","27|0|18|-9|-3","28|0|16|-2|-1","29|0|16|-8|-2","30|0|17|-8|-3","31|0|17|-7|-3","32|0|17|-5|0","33|0|16|-5|0","34|0|17|-5|2","35|0|16|-5|3","36|0|17|-3|6","37|0|17|-3|4","38|0|16|-1|4","39|0|18|-2|3","40|0|48|1|0","41|0|96|1|1","42|0|26|0|1","43|0|112|2|1","44|0|17|6|0","45|0|17|6|0","46|0|17|6|0","47|0|16|2|0","48|0|195|2|1","49|0|8|1|1","50|0|17|4|3","51|0|46|2|2","52|0|17|2|4","53|0|24|1|1","54|0|9|0|2","55|0|51|1|1","56|0|60|0|1","57|0|97|1|1","58|0|111|2|1","59|0|2379|20|131","60|0|20|-7|-19","61|0|16|-5|-20","62|0|34|-20|-56","63|0|16|-8|-21","64|0|17|-7|-14","65|0|17|-6|-8","66|0|16|-3|-3","67|0|18|-1|-2","68|0|16|-1|-2","69|0|15|-2|-3","70|0|18|-3|-7","71|0|16|-3|-5","72|0|17|-1|-1","73|0|50|-1|-7","74|0|17|-2|-6","75|0|17|-1|-8","76|0|16|-2|-7","77|0|17|-2|-6","78|0|17|-2|-7","79|0|16|-1|-7","80|0|18|-2|-8","81|0|15|-1|-2","82|1|83|0|0","83|2|127|0|0","84|0|152|-1|-1","85|0|39|-5|-2","86|0|16|-3|-1","87|1|138|0|0","88|0|112|-1|-1","89|0|17|-6|-1","90|0|16|-8|0","91|0|17|-12|0","92|0|18|-18|0","93|0|19|-14|-2","94|0|14|-11|-2","95|0|16|-6|-1","96|0|18|-4|-1","97|2|232|0|0","98|0|33|0|0","99|0|96|1|0","100|0|7|2|2","101|0|14|1|0","102|0|17|3|2","103|0|17|6|3","104|0|15|1|0","105|0|9|2|0","106|0|10|3|1","107|0|14|3|1","108|0|17|3|1","109|0|16|7|4","110|0|17|4|1","111|0|18|6|3","112|0|16|5|3","113|0|16|4|3","114|0|17|5|2","115|0|10|2|3","116|0|6|2|0","117|0|5|3|3","118|0|13|2|1","119|0|16|3|3","120|0|17|7|6","121|0|18|5|6","122|0|15|6|5","123|0|16|6|4","124|0|20|8|7","125|0|13|8|8","126|0|18|5|4","127|0|17|7|8","128|0|16|7|10","129|0|16|8|12","130|0|18|10|17","131|0|16|20|38","132|0|17|16|31","133|0|16|14|24","134|0|16|11|19","135|0|3320|-163|-3","136|0|17|0|-5","137|0|17|0|-10","138|0|14|0|-11","139|0|16|0|-3","140|0|17|0|-1","141|0|17|0|-1","142|0|16|0|-4","143|0|18|2|-6","144|0|16|0|-1","145|0|19|0|-2","146|0|14|2|-2","147|0|17|5|-8","148|0|17|8|-17","149|0|16|2|-13","150|0|17|1|-11","151|0|17|2|-11","152|0|16|0|-9","153|0|17|1|-11","154|0|19|2|-9","155|0|14|0|-5","156|0|17|-1|-4","157|0|16|-3|-3","158|0|18|-1|-1","159|0|16|-4|-2","160|0|17|-4|-4","161|0|16|-1|-1","162|1|108|0|0","163|0|25|0|0","164|2|84|0|0","165|0|479|2|4","166|0|8|4|8","167|0|14|4|8","168|0|15|12|15","169|0|17|11|13","170|0|16|15|15","171|0|18|11|8","172|0|15|11|9","173|0|18|12|12","174|0|17|6|9","175|0|17|6|6","176|0|16|2|4","177|0|16|2|2","178|0|17|4|2","179|0|28|1|1","180|0|8|1|1","181|0|14|2|2","182|0|17|2|5","183|0|16|3|6","184|0|17|3|4","185|0|16|1|2","186|0|64|1|1","187|0|16|1|1","188|0|10|1|1","189|0|11|1|1","190|0|16|3|3","191|0|19|1|0","192|0|18|2|0","193|0|46|2|2","194|0|17|1|0","195|0|17|5|1","196|0|17|4|1","197|0|17|4|1","198|0|28|1|0","199|0|17|1|0","200|0|39|2|0","201|0|49|2|1","202|0|133|1|1","203|0|155|2|0","204|0|12|1|0","205|0|18|1|0","206|1|947|0|0","207|0|2|0|0","208|0|28|1|-1","209|2|72|0|0"],"browserFingerprintHash":"310a1eae5e049d453e67e0d4b1ca5e86","browserFingerprintAttrs":[{"key":"user_agent","value":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36"},{"key":"language","value":"zh-CN"},{"key":"color_depth","value":24},{"key":"device_memory","value":8},{"key":"pixel_ratio","value":1},{"key":"hardware_concurrency","value":12},{"key":"resolution","value":[1920,1080]},{"key":"available_resolution","value":[1920,1040]},{"key":"timezone_offset","value":-480},{"key":"session_storage","value":1},{"key":"local_storage","value":1},{"key":"indexed_db","value":1},{"key":"open_database","value":1},{"key":"cpu_class","value":"unknown"},{"key":"navigator_platform","value":"Win32"},{"key":"do_not_track","value":"unknown"},{"key":"regular_plugins","value":["Chrome PDF Plugin::Portable Document Format::application/x-google-chrome-pdf~pdf","Chrome PDF Viewer::::application/pdf~pdf","Native Client::::application/x-nacl~,application/x-pnacl~"]},{"key":"canvas","value":"554f84483dc3ccfa4b0958af31f6f10a"},{"key":"webgl","value":"a1e2aff89afb2d292deee6c303d0ff81"},{"key":"webgl_vendor","value":"Google Inc.~ANGLE (NVIDIA GeForce GTX 750 Ti Direct3D11 vs_5_0 ps_5_0)"}, { "key":"adblock","value" : false }, { "key":"has_lied_languages","value" : false }, { "key":"has_lied_resolution","value" : false }, { "key":"has_lied_os","value" : false }, { "key":"has_lied_browser","value" : false }, { "key":"touch_support","value" : [0,false,false] }, { "key":"js_fonts","value" : ["Arial","Arial Black","Arial Narrow","Calibri","Cambria","Cambria Math","Comic Sans MS","Consolas","Courier","Courier New","Georgia","Helvetica","Impact","Lucida Console","Lucida Sans Unicode","Microsoft Sans Serif","MS Gothic","MS PGothic","MS Sans Serif","MS Serif","MYRIAD PRO","Palatino Linotype","Segoe Print","Segoe Script","Segoe UI","Segoe UI Light","Segoe UI Semibold","Segoe UI Symbol","Tahoma","Times","Times New Roman","Trebuchet MS","Verdana","Wingdings"] }]})+*";

void sc_ansiToUnicode(const string & str, wstring & sUnicode)
{
	if (str.empty())
		return;

	DWORD dwLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t * strUnicode = new wchar_t[dwLen];
	if (strUnicode == NULL)
		return;

	memset(strUnicode, 0, dwLen);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, strUnicode, dwLen);
	sUnicode = strUnicode;
	delete[] strUnicode;
}

int _cdecl wmain(int argc, wchar_t *argv[])
{

	//boost::uuids::uuid a_uuid = boost::uuids::random_generator()(); // 这里是两个() ，因为这里是调用的 () 的运算符重载
	//const string tmp_uuid = oost::uuids::to_string(a_uuid);


	CChakra chakra;
	//wstring strRet = chakra.RunJScriptByFile(L"bvsd.js");
	//wstring strCode = chakra.LoadScript(L"bvsd.js");
	wstring wstrJsCode;
	sc_ansiToUnicode(str, wstrJsCode);

	wstring wstrCode;
	sc_ansiToUnicode(strCode, wstrCode);

	//开始转换

	chakra.InitScript(wstrJsCode);
	wstring strRet = chakra.RunFunc(L"LeyBc", wstrCode.c_str());

//	try
//	{
//		JsRuntimeHandle runtime;
//		JsContextRef context;
//		int nJsRetCode = JsNoError;
//
//		wstring script = LoadScript(L"bvsd.js");
//		if (script.empty())
//		{
//			goto error;
//		}
//		JsValueRef result;
//		unsigned currentSourceContext = 0;
//
//		// Create a runtime. 
//		JsCreateRuntime(JsRuntimeAttributeNone, nullptr, &runtime);
//
//		// Create an execution context. 
//		JsCreateContext(runtime, &context);
//
//		// Now set the execution context as being the current one on this thread.
//		JsSetCurrentContext(context);
//		JsValueRef JsRst = NULL;
//		nJsRetCode = JsRunScript(script.c_str(), currentSourceContext++, L"", &JsRst);
//
//	
//
//		JsPropertyIdRef applyId;
//		JsValueRef globalObj;
//
//		JsGetGlobalObject(&globalObj);
//		nJsRetCode = JsGetPropertyIdFromName(L"LeyBc", &applyId);
//
//		JsValueRef LeyBcObj = JS_INVALID_REFERENCE;
//		JsValueRef exception;
//
//		nJsRetCode = JsGetProperty(globalObj, applyId, &LeyBcObj);
//		if (nJsRetCode != JsNoError)
//		{
//			return 0;
//		}
//		
//		JsValueRef stringValue = JS_INVALID_REFERENCE;
//
//		nJsRetCode = JsPointerToString(L"hello world!", _countof(L"hello world"), &stringValue);
//		JsValueRef callbackArgs[2] = { globalObj,  stringValue };
//		nJsRetCode = JsCallFunction(LeyBcObj, callbackArgs, 2, &result);
//		if (nJsRetCode != JsNoError)
//		{
//			return 0;
//		}
//
//		// Run the script.
//		//JsRunScript(script.c_str(), currentSourceContext++, L"", &result);
//		JsValueRef resultJSString;
//		JsConvertValueToString(result, &resultJSString);
//
//		// Project script result in JS back to C++.
//		const wchar_t *resultWC;
//		size_t stringLength;
//		JsStringToPointer(resultJSString, &resultWC, &stringLength);
//
//		wstring resultW(resultWC);
//		cout << string(resultW.begin(), resultW.end()) << endl;
//		// Convert your script result to String in JavaScript; redundant if your script returns a String
//		
//		system("pause");
//
//		// Dispose runtime
//		JsSetCurrentContext(JS_INVALID_REFERENCE);
//		JsDisposeRuntime(runtime);
//	}
//	catch (...)
//	{
//		fwprintf(stderr, L"chakrahost: fatal error: internal error.\n");
//	}
//
//error:
//	return 0;
}


