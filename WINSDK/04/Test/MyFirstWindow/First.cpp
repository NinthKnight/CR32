#include <windows.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include "resource.h"
using namespace std;


//windows 中消息的分类
/*
    1. 普通消息
       WM_CREATE
       WM_DESTROY
       WM_CLOSE
       WM_QUIT
       WM_SIZE
       WM_PAINT
       WM_TIMER
       WM_KEYDOWN, WM_KEYUP
       WM_LBUTTONDOWN....

    2. command消息 WM_COMMAND
       菜单， 快捷键， 部分控件
    
    3. notify消息 WM_NOTIFY
       某些复杂的控件有关

    控件：
       编辑框
       check box
       radio box



*/

HICON g_AppleIcon = nullptr;

//DC
//BeginPaint/EndPaint, 在WM_PAINT消息中使用
//GetDC GetDesktopDC GetWindowDC... / ReleaseDC
//CreateCompatibleDC CreateDC / DeleteDC

int OnPaint(HWND hwnd,      // handle to window
    UINT uMsg,      // message identifier
    WPARAM wParam,  // first message parameter
    LPARAM lParam) {

    //截屏
    //获取屏幕的数据，并放入到内存DC中

    //从桌面的窗口DC中的数据放入到内存DC中

    //1. 首先获取桌面的窗口HWND
    HWND hDskWnd = GetDesktopWindow();

    //2. 获取桌面的窗口DC
    HDC hDskDC = GetDC(hDskWnd);

    //3. 创建一个内存DC（兼容DC），初始的bitmap是1*1
    //HDC hMemDC = CreateCompatibleDC(hDskDC);

    //// 位图 bitmap, jpg, png, gif, bmp
    ////4. 创建一个与内存DC相兼容的bitmap对象

    ////获取系统的屏幕宽高
    int nWidth = GetSystemMetrics(SM_CXSCREEN);
    int nHeight = GetSystemMetrics(SM_CYSCREEN);

    //HBITMAP hBitmap = CreateCompatibleBitmap(hDskDC,
    //                                        nWidth,
    //                                        nHeight);

    ////5. 设置内存DC的bitmap
    //SelectObject(hMemDC, hBitmap);


    ////6. 从桌面DC的Bitmap中的数据拷贝给内存DC中
    //BOOL bRet = BitBlt(hMemDC, 0, 0, nWidth, nHeight, hDskDC, 0, 0, SRCCOPY);
    //if (!bRet) {
    //    return 0;
    //}

    //int nBitSize = 4 * nWidth * nHeight;
    //char* pBuf = new char[nBitSize];
    //memset(pBuf, 0, nBitSize);

    //GetBitmapBits(hBitmap, nBitSize, pBuf);

    //if (pBuf != nullptr) {
    //    delete[] pBuf;
    //    pBuf = nullptr;
    //}

    //从内存DC中拿出数据，放入到窗口中
    //拿客户区的DC
    PAINTSTRUCT ps;

    HDC hCurDC = BeginPaint(hwnd, &ps);
    if (hCurDC == nullptr) {
        return 0;
    }

    BOOL bRet = BitBlt(hCurDC, 0, 0, nWidth, nHeight, hDskDC, 0, 0, SRCCOPY);
    if (!bRet) {
        return 0;
    }


    EndPaint(hwnd, &ps);

    ReleaseDC(hDskWnd, hDskDC);



    //PAINTSTRUCT ps;

    //HDC hDC = BeginPaint(hwnd, &ps);
    //if (hDC == nullptr) {
    //    break;
    //}
    ////创建一个画刷
    //HBRUSH hbrush, hbrushOld;
    //hbrush = CreateSolidBrush(RGB(255, 0, 0));
    //hbrushOld = (HBRUSH)SelectObject(hDC, hbrush);
    //Rectangle(hDC, 100, 100, 200, 200);


    //SelectObject(hDC, hbrushOld);
    //DeleteObject(hbrush);

    ////创建一个画笔
    ////CreatePen();
    ////画直线
    ////LineTo


    //DrawIcon(hDC, 0, 0, g_AppleIcon);

    //EndPaint(hwnd, &ps);

    return 1;
}

//窗口回调函数
LRESULT CALLBACK MyWindowProc(HWND hwnd,      // handle to window
    UINT uMsg,      // message identifier
    WPARAM wParam,  // first message parameter
    LPARAM lParam)   // second message parameter);
{
    int nRet = 1;

    switch (uMsg)
    {
    case WM_CREATE: {
        //做一些窗口初始化的操作
        LPCREATESTRUCT lpCs = (LPCREATESTRUCT)lParam;
        

        g_AppleIcon = LoadIcon(lpCs->hInstance,
            MAKEINTRESOURCE(IDI_APPLE));


        SetTimer(hwnd, 1, 1000, nullptr);

        int n = 0;
    }
    break;

    //定时器
    case WM_TIMER: {
    
        OutputDebugStringA("WM_TIMER");

        InvalidateRect(hwnd, NULL, false);
        UpdateWindow(hwnd);

    }
    break;


    case WM_PAINT: {
        OutputDebugStringA("WM_PAINT");

        ValidateRect(hwnd, NULL);
        //OnPaint(hwnd, uMsg, wParam, lParam);
    }
    break;

    case WM_CHAR: {
        TCHAR ch = wParam;

        stringstream ss;
        ss << ch;
        ss << " CHAR";

        OutputDebugStringA(ss.str().c_str());
    }
    break;

    case WM_LBUTTONDOWN: {
        //鼠标左键被按下
        int xPos = LOWORD(lParam);
        int yPos = HIWORD(lParam);

        stringstream ss;
        ss << "xPos: " << xPos << "yPos: " << yPos;

        OutputDebugStringA(ss.str().c_str());

    }
    break;

    case WM_KEYDOWN: {
        int nVirCode = wParam;

        stringstream ss;
        ss << nVirCode;
        ss << " KEY DOWN";

        if (nVirCode == 'A') {
            OutputDebugStringA(ss.str().c_str());
        }

    }
    break;
    
    case WM_KEYUP: {
        int nVirCode = wParam;


        stringstream ss;
        ss << nVirCode;
        ss << " KEY UP";

        OutputDebugStringA(ss.str().c_str());
    }
    break;

    case WM_DESTROY:{
        //发送WM_QUIT消息
        //PostQuitMessage(0);

        PostMessage(hwnd, WM_QUIT, 0, 0);
    }
    break;

    case WM_CLOSE: {
        int nRet = MessageBoxA(hwnd, "是否退出程序？", "提示", MB_OKCANCEL);
        if (nRet == IDOK) {
            DestroyWindow(hwnd);
        }
    }
    break;


    default:
        nRet = DefWindowProc(hwnd, uMsg, wParam, lParam);
        break;
    }

    return nRet;
}


//InvalidateRect
//UpdateWindow

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPreInstance,
    LPSTR lpCmdLine,
    int nShow) {

    //获取任意窗口的窗口句柄

    HWND hCalcWnd =  FindWindow(_T("Notepad"), NULL);




    //在桌面上绘制
    HWND hDskWnd = GetDesktopWindow();

    HDC hDC = GetWindowDC(hCalcWnd);

    RECT rc;
    rc.top = 200;
    rc.left = 0;
    rc.right = 100;
    rc.bottom = 400;

    DrawText(hDC, _T("Hello WOrld!"), -1, &rc, DT_LEFT);


    ReleaseDC(hCalcWnd, hDC);


    //窗口类的结构体
    WNDCLASSEX wcs = {0};

    wcs.cbSize = sizeof(WNDCLASSEX);
    wcs.lpszClassName = _T("CR32_WinCls"); // 指定窗口类名，为后面的窗口类注册和创建窗口做准备
    wcs.lpfnWndProc = MyWindowProc; //指定窗口回调函数，为后面的消息循环做准备
    wcs.hbrBackground =  (HBRUSH)GetStockObject(WHITE_BRUSH);
    //(HBRUSH)(COLOR_WINDOW + 1);

    //创建一个窗口
    //1. 注册窗口类

    //
    ATOM atom = RegisterClassEx(&wcs);
    if (atom == 0) {
        return 0;
    }


    //2. 用自己注册的窗口类作为模板，来创建窗口
    //
    HWND hWnd = CreateWindowA("CR32_WinCls",
        "CR32",
        WS_OVERLAPPEDWINDOW,
        500,
        500,
        800,
        600,
        NULL,
        NULL,
        hInstance,
        NULL);
    if (hWnd == nullptr) {
    
        return 0;
    }


    //3. 显示
    //
    ShowWindow(hWnd, SW_SHOWNORMAL);

    // 更新
    UpdateWindow(hWnd);


    //4. 消息循环
    //
    MSG msg = {0};

    //DestroyWindow

    while (true) {

        //拿消息
        BOOL bRet = GetMessage(&msg,
                   nullptr,
                   0,
                   0);

        if (!bRet) {
            break;
        }

        //翻译消息 WM_KEYDOWN--> WM_CHAR
        TranslateMessage(&msg);

        //派发消息
        DispatchMessage(&msg);
    }
    

    return 0;
}