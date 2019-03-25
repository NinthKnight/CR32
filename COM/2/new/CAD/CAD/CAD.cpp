// CAD.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "CAD.h"
#include <list>
#include <stdlib.h>
#include "plugin.h"

using namespace std;

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];     


list<IPlugin*> g_plugins;


// 此代码模块中包含的函数的前向声明:
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

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CAD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CAD));

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
//  目标: 注册窗口类。
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CAD));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CAD);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


void ShowMenu(HWND hWnd) {
    HMENU hMenu = GetMenu(hWnd);
    BOOL b = InsertMenu(hMenu, 1, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hMenu, "图形(&S)");
    HMENU hSubMenu = GetSubMenu(hMenu, 1);

    for (list<IPlugin*>::iterator it = g_plugins.begin();
    it != g_plugins.end();
        it++) {
        IPlugin *pPlugin = *it;
        AppendMenu(hSubMenu, MF_STRING, pPlugin->CADGetID(), pPlugin->CADGetMenuName());
    }
}

void LoadAllPlugin() {
    //加载插件
    WIN32_FIND_DATA FileData;
    HANDLE hSearch;
    BOOL fFinished = true;
    char szDirPath[MAX_PATH];
    char szNewPath[MAX_PATH];

    GetCurrentDirectory(sizeof(szDirPath), szDirPath);
    strcat(szDirPath, "\\plugin\\");
    strcpy(szNewPath, szDirPath);
    strcat(szNewPath, "*.dll");



    hSearch = FindFirstFile(szNewPath, &FileData);
    if (hSearch == INVALID_HANDLE_VALUE) {
        return;
    }

    while (fFinished) {
        szNewPath[0] = '\0';
        strcpy(szNewPath, szDirPath);
        strcat(szNewPath, FileData.cFileName);

        HMODULE hDll = LoadLibrary(szNewPath);
        GET_PLUGIN pfnGetPlugin = (GET_PLUGIN)GetProcAddress(hDll, "GetPlugin");
        if (pfnGetPlugin == NULL) {//不是自己人
            FreeLibrary(hDll);
            fFinished = FindNextFile(hSearch, &FileData);
            continue;
        }
      

        //保存信息
        IPlugin *pPlugin = pfnGetPlugin();
        static int num = 100;
        pPlugin->CADSetID(num++);
        g_plugins.push_back(pPlugin);

        fFinished = FindNextFile(hSearch, &FileData);
    }

    FindClose(hSearch);
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//

LRESULT CALLBACK OnCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    //加载插件
    LoadAllPlugin();

    //显示菜单
    ShowMenu(hWnd);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static  IPlugin* pPlugin = NULL;
    switch (message)
    {
    case WM_LBUTTONDOWN:
    {
        WORD xPos = LOWORD(lParam);
        WORD yPos = HIWORD(lParam);
        if (pPlugin != NULL)
            pPlugin->CADOnLButtonDown(hWnd, xPos, yPos);
        break;
    }
    case WM_LBUTTONUP:
    {
        WORD xPos = LOWORD(lParam);
        WORD yPos = HIWORD(lParam);
        if (pPlugin != NULL)
            pPlugin->CADOnLButtonUp(hWnd, xPos, yPos);
        break;
    }
    case WM_MOUSEMOVE:
    {
        WORD xPos = LOWORD(lParam);
        WORD yPos = HIWORD(lParam);
        if (pPlugin != NULL)
            pPlugin->CADOnMouseMove(hWnd, xPos, yPos);
        break;
    }
    case WM_CREATE:
        OnCreate(hWnd, message, wParam, lParam);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);

            if (wmId >= 100) {
                for (list<IPlugin*>::iterator it = g_plugins.begin();
                it != g_plugins.end();
                    it++) {
                    pPlugin = *it;
                    if (pPlugin->CADGetID() == wmId) {
                        pPlugin->CADOnDraw(NULL, 0);
                    }
                
                }
            }

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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
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
