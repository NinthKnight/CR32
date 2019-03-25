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

	//ִ��js�ű�
	wstring RunJScriptByFile(wstring fileName);

	wstring RunJScript(wstring jsCode);

	//���ú���ǰ������ִ��InitScript
	bool InitScript(wstring jsCode);

	//ִ��ָ����������js������ֻ֧��һ������
	wstring RunFunc(wstring funcName, wstring arg);

	//�����ļ���ȡjs
	wstring LoadScript(wstring fileName);

private:
	JsRuntimeHandle runtime_;
	JsContextRef context_;
	int nJsRetCode_;
	unsigned currentSourceContext;

};

