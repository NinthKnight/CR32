#pragma once

#include <ChakraCore.h>

#pragma comment(lib, "ChakraCore.lib")
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

class CChakra
{
public:
	CChakra();
	~CChakra();

	//执行js脚本
	wstring RunJScriptByFile(wstring fileName);

	wstring RunJScript(wstring jsCode);

	//调用函数前必须先执行InitScript
	bool InitScript(wstring jsCode);

	//执行指定函数名的js，这里只支持一个参数
	wstring RunFunc(wstring funcName, wstring arg);

	//加载文件获取js
	wstring LoadScript(wstring fileName);

private:
	JsRuntimeHandle runtime_;
	JsContextRef context_;
	int nJsRetCode_;
	unsigned currentSourceContext;

};

