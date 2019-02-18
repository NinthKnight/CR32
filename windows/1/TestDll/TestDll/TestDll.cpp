// TestDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

//#pragma comment(linker, "/EXPORT:LpkInitialize=lpkOrg.LpkInitialize")
//#pragma comment(linker, "/EXPORT:LpkTabbedTextOut=lpkOrg.LpkTabbedTextOut")
//#pragma comment(linker, "/EXPORT:LpkDllInitialize=lpkOrg.LpkDllInitialize")
//#pragma comment(linker, "/EXPORT:LpkDrawTextEx=lpkOrg.LpkDrawTextEx")
//#pragma comment(linker, "/EXPORT:LpkEditControl=lpkOrg.LpkEditControl")
//#pragma comment(linker, "/EXPORT:LpkExtTextOut=lpkOrg.LpkExtTextOut")
//#pragma comment(linker, "/EXPORT:LpkGetCharacterPlacement=lpkOrg.LpkGetCharacterPlacement")
//#pragma comment(linker, "/EXPORT:LpkGetTextExtentExPoint=lpkOrg.LpkGetTextExtentExPoint")
//#pragma comment(linker, "/EXPORT:LpkPSMTextOut=lpkOrg.LpkPSMTextOut")
//#pragma comment(linker, "/EXPORT:LpkUseGDIWidthCache=lpkOrg.LpkUseGDIWidthCache")
//#pragma comment(linker, "/EXPORT:ftsWordBreak=lpkOrg.ftsWordBreak")

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
#pragma comment(linker, "/EXPORT:adler32=zlib1Org.adler32,@1")
#pragma comment(linker, "/EXPORT:compress=zlib1Org.compress,@2")
#pragma comment(linker, "/EXPORT:compress2=zlib1Org.compress2,@3")
#pragma comment(linker, "/EXPORT:compressBound=zlib1Org.compressBound,@4")
#pragma comment(linker, "/EXPORT:crc32=zlib1Org.crc32,@5")
#pragma comment(linker, "/EXPORT:deflate=zlib1Org.deflate,@6")
#pragma comment(linker, "/EXPORT:deflateBound=zlib1Org.deflateBound,@7")
#pragma comment(linker, "/EXPORT:deflateCopy=zlib1Org.deflateCopy,@8")
#pragma comment(linker, "/EXPORT:deflateEnd=zlib1Org.deflateEnd,@9")
#pragma comment(linker, "/EXPORT:deflateInit2_=zlib1Org.deflateInit2_,@10")
#pragma comment(linker, "/EXPORT:deflateInit_=zlib1Org.deflateInit_,@11")
#pragma comment(linker, "/EXPORT:deflateParams=zlib1Org.deflateParams,@12")
#pragma comment(linker, "/EXPORT:deflatePrime=zlib1Org.deflatePrime,@13")
#pragma comment(linker, "/EXPORT:deflateReset=zlib1Org.deflateReset,@14")
#pragma comment(linker, "/EXPORT:deflateSetDictionary=zlib1Org.deflateSetDictionary,@15")
#pragma comment(linker, "/EXPORT:get_crc_table=zlib1Org.get_crc_table,@16")
#pragma comment(linker, "/EXPORT:gzclearerr=zlib1Org.gzclearerr,@17")
#pragma comment(linker, "/EXPORT:gzclose=zlib1Org.gzclose,@18")
#pragma comment(linker, "/EXPORT:gzdopen=zlib1Org.gzdopen,@19")
#pragma comment(linker, "/EXPORT:gzeof=zlib1Org.gzeof,@20")
#pragma comment(linker, "/EXPORT:gzerror=zlib1Org.gzerror,@21")
#pragma comment(linker, "/EXPORT:gzflush=zlib1Org.gzflush,@22")
#pragma comment(linker, "/EXPORT:gzgetc=zlib1Org.gzgetc,@23")
#pragma comment(linker, "/EXPORT:gzgets=zlib1Org.gzgets,@24")
#pragma comment(linker, "/EXPORT:gzopen=zlib1Org.gzopen,@25")
#pragma comment(linker, "/EXPORT:gzprintf=zlib1Org.gzprintf,@26")
#pragma comment(linker, "/EXPORT:gzputc=zlib1Org.gzputc,@27")
#pragma comment(linker, "/EXPORT:gzputs=zlib1Org.gzputs,@28")
#pragma comment(linker, "/EXPORT:gzread=zlib1Org.gzread,@29")
#pragma comment(linker, "/EXPORT:gzrewind=zlib1Org.gzrewind,@30")
#pragma comment(linker, "/EXPORT:gzseek=zlib1Org.gzseek,@31")
#pragma comment(linker, "/EXPORT:gzsetparams=zlib1Org.gzsetparams,@32")
#pragma comment(linker, "/EXPORT:gztell=zlib1Org.gztell,@33")
#pragma comment(linker, "/EXPORT:gzungetc=zlib1Org.gzungetc,@34")
#pragma comment(linker, "/EXPORT:gzwrite=zlib1Org.gzwrite,@35")
#pragma comment(linker, "/EXPORT:inflate=zlib1Org.inflate,@36")
#pragma comment(linker, "/EXPORT:inflateBack=zlib1Org.inflateBack,@37")
#pragma comment(linker, "/EXPORT:inflateBackEnd=zlib1Org.inflateBackEnd,@38")
#pragma comment(linker, "/EXPORT:inflateBackInit_=zlib1Org.inflateBackInit_,@39")
#pragma comment(linker, "/EXPORT:inflateCopy=zlib1Org.inflateCopy,@40")
#pragma comment(linker, "/EXPORT:inflateEnd=zlib1Org.inflateEnd,@41")
#pragma comment(linker, "/EXPORT:inflateInit2_=zlib1Org.inflateInit2_,@42")
#pragma comment(linker, "/EXPORT:inflateInit_=zlib1Org.inflateInit_,@43")
#pragma comment(linker, "/EXPORT:inflateReset=zlib1Org.inflateReset,@44")
#pragma comment(linker, "/EXPORT:inflateSetDictionary=zlib1Org.inflateSetDictionary,@45")
#pragma comment(linker, "/EXPORT:inflateSync=zlib1Org.inflateSync,@46")
#pragma comment(linker, "/EXPORT:inflateSyncPoint=zlib1Org.inflateSyncPoint,@47")
#pragma comment(linker, "/EXPORT:uncompress=zlib1Org.uncompress,@48")
#pragma comment(linker, "/EXPORT:zError=zlib1Org.zError,@49")
#pragma comment(linker, "/EXPORT:zlibCompileFlags=zlib1Org.zlibCompileFlags,@50")
#pragma comment(linker, "/EXPORT:zlibVersion=zlib1Org.zlibVersion,@51")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//dllmain

BOOL WINAPI DllMain(HINSTANCE hinstDLL,  // handle to the DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpvReserved)   // reserved);
{
	OutputDebugStringA("Faked Dll:DllMain!\r\n");

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH: {
		OutputDebugStringA("Faked Dll:DLL_PROCESS_ATTACH!\r\n");
		return true;
	}
	break;

	case DLL_PROCESS_DETACH: {
		OutputDebugStringA("Faked Dll:DLL_PROCESS_DETACH!\r\n");
		return true;
	}
	break;

	default:
		break;
	}

	return true;
}