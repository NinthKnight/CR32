// AsyncServer.cpp : ����Ӧ�ó������ڵ㡣
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
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

#define MAX_LOADSTRING 100
#define WM_MYSOCKMSG WM_USER + 1
#define WM_MYRSMSG WM_USER + 2



// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������
SOCKET sServer;
HWND hWnd;


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


class session
  : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket socket)
    : socket_(std::move(socket))
  {
   
  }

  void start()
  {
    do_read();
  }

private:
  void Send(char* pBuf, int nLength) {

    mySendBuf.Write((PBYTE)pBuf, nLength);

    if (mySendBuf.GetBufferLen() == nLength) {
        do_write();
    }
  }


  void do_read()
  {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
      [this, self](boost::system::error_code ec, std::size_t length)
    {
      if (!ec)
      {
        myBuf.Write((PBYTE)data_, length);

        while (myBuf.GetBufferLen() >= 5) {
          tagPacket* pHead = (tagPacket*)myBuf.GetBuffer(0);

          if (pHead->length + 5 <= myBuf.GetBufferLen()) {
            //��ʾ���������ˣ���ʼ����

            int nLength = pHead->length + 5;
            char* pData = new char[nLength];
            myBuf.Read((PBYTE)pData, nLength);

            //��ʾ
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

            Send((char*)&pkt, sizeof(tagPacket));
          }
          else {
            break;
          }

        }
      
        do_read();
      }
    });
  }

  void do_write()
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(mySendBuf.GetBuffer(), mySendBuf.GetBufferLen()),
      [this, self](boost::system::error_code ec, std::size_t length)
    {
      if (!ec)
      {
        //��mySendBuf��ȥ��ͷ��dwIOBytes
        mySendBuf.Delete(length);

        if (mySendBuf.GetBufferLen() > 0) {
          do_write();
        }

      }
    });
  }

  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];

  CBuffer myBuf;
  CBuffer mySendBuf;

};

//��������
void do_accept(tcp::acceptor& acceptor_)
{
  acceptor_.async_accept(
    [&](boost::system::error_code ec, tcp::socket socket)
  {
    if (!ec)
    {
      std::make_shared<session>(std::move(socket))->start();
    }

    do_accept(acceptor_);
  });
}

void AcceptFunc() {

  boost::asio::io_context io_context;
  tcp::acceptor acceptor_(io_context, tcp::endpoint(tcp::v4(), 1234));

  do_accept(acceptor_);

  io_context.run();
}


// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //���ȴ���һ�����ӵ��߳�
    std::thread(AcceptFunc).detach();

    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASYNCSERVER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // �����˴���
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }



    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASYNCSERVER));

    MSG msg;

    // ����Ϣѭ��: 
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
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
      //��wparam/lparam ����socket, ����

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
            // �����˵�ѡ��: 
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
    //        // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...


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

// �����ڡ������Ϣ�������
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
