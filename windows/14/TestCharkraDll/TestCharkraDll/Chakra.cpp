#include "Chakra.h"



CChakra::CChakra()
{
	// Create a runtime. 
	JsCreateRuntime(JsRuntimeAttributeNone, nullptr, &runtime_);

	// Create an execution context. 
	JsCreateContext(runtime_, &context_);

	// Now set the execution context as being the current one on this thread.
	JsSetCurrentContext(context_);

	currentSourceContext = 0;
}


CChakra::~CChakra()
{
	JsSetCurrentContext(JS_INVALID_REFERENCE);
	JsDisposeRuntime(runtime_);
}

wstring CChakra::LoadScript(wstring fileName)
{
	FILE *file;
	if (_wfopen_s(&file, fileName.c_str(), L"rb"))
	{
		fwprintf(stderr, L"chakrahost: unable to open file: %s.\n", fileName.c_str());
		return wstring();
	}

	unsigned int current = ftell(file);
	fseek(file, 0, SEEK_END);
	unsigned int end = ftell(file);
	fseek(file, current, SEEK_SET);
	unsigned int lengthBytes = end - current;
	char *rawBytes = (char *)calloc(lengthBytes + 1, sizeof(char));

	if (rawBytes == nullptr)
	{
		fwprintf(stderr, L"chakrahost: fatal error.\n");
		return wstring();
	}

	fread((void *)rawBytes, sizeof(char), lengthBytes, file);

	wchar_t *contents = (wchar_t *)calloc(lengthBytes + 1, sizeof(wchar_t));
	if (contents == nullptr)
	{
		free(rawBytes);
		fwprintf(stderr, L"chakrahost: fatal error.\n");
		return wstring();
	}

	if (MultiByteToWideChar(CP_UTF8, 0, rawBytes, lengthBytes + 1, contents, lengthBytes + 1) == 0)
	{
		free(rawBytes);
		free(contents);
		fwprintf(stderr, L"chakrahost: fatal error.\n");
		return wstring();
	}

	wstring result = contents;
	free(rawBytes);
	free(contents);
	return result;
}

wstring CChakra::RunJScript(wstring jscode) {
	try {
		JsValueRef JsRst = NULL;
		nJsRetCode_ = JsRunScript(jscode.c_str(), currentSourceContext++, L"", &JsRst);
		if (nJsRetCode_ != JsNoError)
		{
			return NULL;
		}

		JsValueRef resultJSString;
		JsConvertValueToString(JsRst, &resultJSString);

		// Project script result in JS back to C++.
		const wchar_t *resultWC;
		size_t stringLength;
		nJsRetCode_ = JsStringToPointer(resultJSString, &resultWC, &stringLength);
		if (nJsRetCode_ != JsNoError)
		{
			return NULL;
		}

		return resultWC;
	}
	catch (...)
	{
		fwprintf(stderr, L"chakrahost: fatal error: internal error.\n");
	}

	return NULL;
}

bool CChakra::InitScript(wstring jsCode) {
	try{
		JsValueRef JsRst = NULL;
		nJsRetCode_ = JsRunScript(jsCode.c_str(), currentSourceContext++, L"", &JsRst);
		if (nJsRetCode_ != JsNoError)
		{
			return false;
		}
		return true;
    }
	catch (...)
	{
		fwprintf(stderr, L"chakrahost: fatal error: internal error.\n");
	}

	return false;
}

wstring CChakra::RunJScriptByFile(wstring fileName) {

	wstring script = LoadScript(fileName);
	if (script.empty())
	{
		return NULL;
	}

	return RunJScript(script.c_str());
}

wstring CChakra::RunFunc(wstring funcName, wstring arg) {
	JsPropertyIdRef applyId;
	JsValueRef globalObj;
	JsValueRef result;

	try {
		JsGetGlobalObject(&globalObj);
		nJsRetCode_ = JsGetPropertyIdFromName(funcName.c_str(), &applyId);
		if (nJsRetCode_ != JsNoError)
		{
			return NULL;
		}

		JsValueRef funcObj = JS_INVALID_REFERENCE;

		nJsRetCode_ = JsGetProperty(globalObj, applyId, &funcObj);
		if (nJsRetCode_ != JsNoError)
		{
			return NULL;
		}

		JsValueRef stringValue = JS_INVALID_REFERENCE;

		nJsRetCode_ = JsPointerToString(arg.c_str(), arg.length(), &stringValue);
		if (nJsRetCode_ != JsNoError)
		{
			return NULL;
		}

		JsValueRef callbackArgs[2] = { globalObj,  stringValue };
		nJsRetCode_ = JsCallFunction(funcObj, callbackArgs, 2, &result);
		if (nJsRetCode_ != JsNoError)
		{
			return NULL;
		}

		// Run the script.
		JsValueRef resultJSString;
		nJsRetCode_ = JsConvertValueToString(result, &resultJSString);
		if (nJsRetCode_ != JsNoError)
		{
			return NULL;
		}

		// Project script result in JS back to C++.
		const wchar_t *resultWC;
		size_t stringLength;
		nJsRetCode_ = JsStringToPointer(resultJSString, &resultWC, &stringLength);
		if (nJsRetCode_ != JsNoError)
		{
			return NULL;
		}

		return resultWC;
	}
	catch (...)
	{
		fwprintf(stderr, L"chakrahost: fatal error: internal error.\n");
	}
    
	return NULL;
}



