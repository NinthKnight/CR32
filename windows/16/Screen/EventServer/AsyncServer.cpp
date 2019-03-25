// AsyncServer.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "AsyncServer.h"
#include <afx.h>
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <thread>
#include "../common/macro.h"
#include <sstream>
#include <vector>
#include "CBuffer.h"


#pragma comment(lib, "ws2_32.lib")

#define MAX_LOADSTRING 100
#define WM_MYSOCKMSG WM_USER + 1
#define WM_MYRSMSG WM_USER + 2



// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
SOCKET sServer;
HWND hWnd;
WSAEVENT  hAcceptEvent;

HANDLE hIOCP;

WSAEVENT hEventAry[MAXIMUM_WAIT_OBJECTS];
SOCKET  hSocketAry[MAXIMUM_WAIT_OBJECTS];

std::stringstream ss;
std::vector<char> vt;
CStringA strBuf;

CBuffer myBuf;
CBuffer mySendBuf;

int nCurCount = 0;


void ShowImage(char* pBuf, int nLength) {

  int nWidth = *(int*)pBuf;
  int nHeight = *((int*)pBuf+1);

  char* pData = pBuf + 8;
  int nScreenData = nLength - 8;

  RECT rc = { 0 };
  HDC hCurDC = NULL;
  HDC hMemDC = NULL;
  BOOL bRet = FALSE;
  HBITMAP  hBitmap = NULL;

  hCurDC = GetDC(hWnd);

  hMemDC = CreateCompatibleDC(hCurDC);
  if (hMemDC == NULL) {
    goto SAFE_EXIT;
  }

  hBitmap = CreateCompatibleBitmap(hCurDC, nWidth, nHeight);
  if (hBitmap == NULL) {
    goto SAFE_EXIT;
  }

  SelectObject(hMemDC, hBitmap);

  SetBitmapBits(hBitmap, nScreenData, pData);

  bRet = BitBlt(hCurDC, 0, 0, nWidth, nHeight, hMemDC, 0, 0, SRCCOPY);
  if (!bRet) {
    goto SAFE_EXIT;
  }

  //InvalidateRect(hWnd, NULL, TRUE);
  //UpdateWindow(hWnd);

SAFE_EXIT:
  if (hCurDC != NULL) {
    ReleaseDC(hWnd, hCurDC);
  }

  if (hBitmap != NULL) {
    DeleteObject(hBitmap);
  }

  if (hMemDC != NULL) {
    DeleteDC(hMemDC);
  }
}

//投递一个收包请求
void PostRecv(SOCKET sClient) {

  WSABUF buf;
  DWORD dwNumberOfBytesRecvd;
  DWORD dwFlags = 0;
  MyOverlapped* pOl = new MyOverlapped(IO_READ);

  buf.len = 8192;
  buf.buf = pOl->pRecvBuf;

  int nRet = WSARecv(sClient,
    &buf,
    1,
    &dwNumberOfBytesRecvd,
    &dwFlags,
    &pOl->ol,
    NULL);
  if (nRet == SOCKET_ERROR) {

    DWORD dwLastError = GetLastError();
    OutputDebugStringA("123");
  }

}

//发包
void PostSend(SOCKET sClient, char* pBuf, int nLength) {

  WSABUF buf;
  DWORD dwNumberOfBytesSended;
  DWORD dwFlags = 0;
  MyOverlapped* pOl = new MyOverlapped(IO_WRITE);

  buf.len = nLength;
  buf.buf = pBuf;

  int nRet = WSASend(sClient,
    &buf,
    1,
    &dwNumberOfBytesSended,
    dwFlags,
    &pOl->ol,
    NULL);
  if (nRet == SOCKET_ERROR) {
  
    DWORD dwLastError = GetLastError();
    OutputDebugStringA("123");
  }

}

void Send(SOCKET sClient, char* pBuf, int nLength) {

  mySendBuf.Write((PBYTE)pBuf, nLength);

  if (mySendBuf.GetBufferLen() == nLength) {
    PostSend(sClient, (char*)mySendBuf.GetBuffer(), mySendBuf.GetBufferLen());
  }
  

}


void ThreadPoolFunc() {

  DWORD dwIOBytes;
  ULONG_PTR dwCompleteKey;
  LPOVERLAPPED lpOl;
  while (true) {
    BOOL bRet = GetQueuedCompletionStatus(hIOCP,
      &dwIOBytes,
      &dwCompleteKey,
      &lpOl,
      INFINITE);

    if (!bRet) {
      return;
    }
    
    SOCKET sClient = (SOCKET)dwCompleteKey;

    //处理消息（收包，发包）
    MyOverlapped* pOverlapPlus = CONTAINING_RECORD(lpOl, MyOverlapped, ol);

    if (pOverlapPlus->nType == IO_READ) {
      //表示当前收到了数据
      char* szBuf = pOverlapPlus->pRecvBuf;
      int nRecvedBytes = dwIOBytes;
    
      myBuf.Write((PBYTE)szBuf, nRecvedBytes);

      while (myBuf.GetBufferLen() >= 5) {
        tagPacket* pHead = (tagPacket*)myBuf.GetBuffer(0);

        if (pHead->length + 5 <= myBuf.GetBufferLen()) {
          //表示包收完整了，开始处理

          int nLength = pHead->length + 5;
          char* pData = new char[nLength];
          myBuf.Read((PBYTE)pData, nLength);

          //显示
          ShowImage(pData + 5, nLength - 5);

          if (pData != nullptr) {
            delete pData;
            pData = nullptr;
          }

          tagPacket pkt;
          pkt.code = SERVER_SCREEN_DATA;
          pkt.length = 0;
          //send(sClient,
          //  (char*)&pkt,
          //  sizeof(tagPacket),
          //  0);

          Send(sClient, (char*)&pkt, sizeof(tagPacket));
        }
        else {
          break;
        }

      }


      PostRecv(sClient);
    }
    else if (pOverlapPlus->nType == IO_WRITE) {
      
        //将mySendBuf中去掉头部dwIOBytes
      mySendBuf.Delete(dwIOBytes);

      if (mySendBuf.GetBufferLen() > 0) {
      
        PostSend(sClient, (char*)mySendBuf.GetBuffer(), mySendBuf.GetBufferLen());
      }

    
    }

    if (pOverlapPlus != NULL) {
      delete pOverlapPlus;
    }
  }
}

//用于连接
void AcceptFunc() {
  sockaddr_in ClientAddr = { 0 };
  ClientAddr.sin_family = AF_INET;
  int nAddrSize = sizeof(sockaddr_in);

  while (true) {
    SOCKET sClient = accept(sServer, (sockaddr*)&ClientAddr, &nAddrSize);
    if (sServer == SOCKET_ERROR) {
      return;
    }
  
    //将socket 与 iocp句柄绑定
    HANDLE hTmp = CreateIoCompletionPort(
      (HANDLE)sClient,
      hIOCP, 
      sClient,
       2);

    if (hTmp == 0) {
      continue;
    }

    PostRecv(sClient);

  }


}


// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int Init() {

  WORD wVersionRequested;
  WSADATA wsaData;
  int err;

  wVersionRequested = MAKEWORD(2, 2);

  err = WSAStartup(wVersionRequested, &wsaData);
  if (err != 0) {
    /* Tell the user that we could not find a usable */
    /* WinSock DLL.                                  */
    return 0;
  }

  sServer = socket(AF_INET,
    SOCK_STREAM,
    IPPROTO_TCP);

  //bind 绑定
  sockaddr_in addr = { 0 };

  DWORD dwIP;

  InetPton(AF_INET,
    _T("127.0.0.1"),
    &addr.sin_addr.S_un.S_addr);//INADDR_ANY;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(1234);

  int nRet = bind(sServer, (sockaddr*)&addr, sizeof(sockaddr));

  if (nRet == SOCKET_ERROR) {
    //WSAGetLastError();
    return 0;
  }

  nRet = listen(sServer, SOMAXCONN);
  if (nRet == SOCKET_ERROR) {
    //WSAGetLastError();
    return 0;
  }

  //IOCP
  //1. 创建IOCP对象

  hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE,
    NULL,
    0,
    2);

  if (hIOCP == NULL) {
    return 0;
  }

  //2.创建线程池
  for (int i = 0; i < 2; i++) {
    std::thread(ThreadPoolFunc).detach();
  }

  //首先创建一个连接的线程
  std::thread(AcceptFunc).detach();
}





int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    //创建socket，并开始监听
    Init();

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASYNCSERVER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 创建了窗口
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }



    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASYNCSERVER));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASYNCSERVER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASYNCSERVER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_MYSOCKMSG: {
    

      sockaddr_in ClientAddr = { 0 };
      ClientAddr.sin_family = AF_INET;
      int nAddrSize = sizeof(sockaddr_in);

      SOCKET sClient = accept(sServer, (sockaddr*)&ClientAddr, &nAddrSize);


      WSAAsyncSelect(sClient,
        hWnd,
        WM_MYRSMSG,
        FD_READ | FD_WRITE | FD_CLOSE);
    }
    break;

    case WM_MYRSMSG: {
      //从wparam/lparam 区分socket, 类型

      SOCKET sClient = (SOCKET)wParam;
      char szBuf[256] = { 0 };
      int nType = LOWORD(lParam);
      int nError = HIWORD(lParam);

      if (nType == FD_READ && nError == 0) {
        recv(sClient, szBuf, 256, 0);

        OutputDebugStringA(szBuf);

      }
      else if (nType == FD_WRITE) {
      

      }
      else if (nType == FD_CLOSE) {
      

      }

    }
    break;
    

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    //case WM_PAINT:
    //    {
    //        PAINTSTRUCT ps;
    //        HDC hdc = BeginPaint(hWnd, &ps);
    //        // TODO: 在此处添加使用 hdc 的任何绘图代码...


    //        EndPaint(hWnd, &ps);
    //    }
    //    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
