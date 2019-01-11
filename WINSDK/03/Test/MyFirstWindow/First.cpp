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

    }
    break;


    case WM_PAINT: {
        OutputDebugStringA("WM_PAINT");
        PAINTSTRUCT ps;

        HDC hDC = BeginPaint(hwnd, &ps);
        if (hDC == nullptr) {
            break;
        }
        //创建一个画刷
        HBRUSH hbrush, hbrushOld;
        hbrush = CreateSolidBrush(RGB(255, 0, 0));
        hbrushOld = (HBRUSH)SelectObject(hDC, hbrush);
        Rectangle(hDC, 100, 100, 200, 200);


        SelectObject(hDC, hbrushOld);
        DeleteObject(hbrush);

        //创建一个画笔
        //CreatePen();
        //画直线
        //LineTo


        DrawIcon(hDC, 0, 0, g_AppleIcon);

        EndPaint(hwnd, &ps);



        
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
        0,
        0,
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