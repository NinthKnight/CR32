#include <windows.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include "resource.h"
#include <Commctrl.h>
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
HWND g_hStatusWnd = nullptr;
HWND g_hBtnWnd = nullptr;
HINSTANCE g_hInst = nullptr;
int g_nResult = 0;

//DC
//BeginPaint/EndPaint, 在WM_PAINT消息中使用
//GetDC GetDesktopDC GetWindowDC... / ReleaseDC
//CreateCompatibleDC CreateDC / DeleteDC

//对话框的回调函数
INT_PTR CALLBACK DialogProc(HWND hwndDlg,  // handle to dialog box
    UINT uMsg,     // message 
    WPARAM wParam, // first message parameter
    LPARAM lParam) // second message parameter;
{
    switch (uMsg)
    {
    case WM_INITDIALOG: {
        //插入数据

        //获取combo的窗口句柄
        HWND hComBo = GetDlgItem(hwndDlg, IDC_COMBO1);

        TCHAR szText1[] = _T("x86");
        TCHAR szText2[] = _T("x64");

        BOOL bRet = SendMessage(hComBo, CB_ADDSTRING, 0, (LPARAM)szText1);
        bRet =  SendMessage(hComBo, CB_ADDSTRING, 0, (LPARAM)szText2);
        bRet = SendMessage(hComBo, CB_ADDSTRING, 0, (LPARAM)_T("1"));
        bRet = SendMessage(hComBo, CB_ADDSTRING, 0, (LPARAM)_T("2"));
        bRet = SendMessage(hComBo, CB_ADDSTRING, 0, (LPARAM)_T("3"));
        bRet = SendMessage(hComBo, CB_ADDSTRING, 0, (LPARAM)_T("4"));

        //直接向控件发消息
        SendDlgItemMessage(hwndDlg,
            IDC_LIST1,
            LB_ADDSTRING,
            0,
            (LPARAM)_T("足球"));

        SendDlgItemMessage(hwndDlg,
            IDC_LIST1,
            LB_ADDSTRING,
            0,
            (LPARAM)_T("篮球"));

        
        //listview
        //获取ListView的窗口句柄
        HWND hListView = GetDlgItem(hwndDlg, IDC_LISTVIEW);
        
        //设置ListView的风格
        
        DWORD dwOldStyle = SendMessage(hListView, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);
        SendMessage(hListView,
                    LVM_SETEXTENDEDLISTVIEWSTYLE,
                    0, 
                    (LPARAM)dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

        //插入报表头
        LVCOLUMN lvCol1 = {0};
        lvCol1.pszText = _T("序号");
        lvCol1.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvCol1.iSubItem = 0;
        lvCol1.cx = 100;

        int nRet = ListView_InsertColumn(hListView, 0, &lvCol1);

        LVCOLUMN lvCol2 = { 0 };
        lvCol2.pszText = _T("类型");
        lvCol2.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvCol2.iSubItem = 1;
        lvCol2.cx = 100;

        ListView_InsertColumn(hListView, 1, &lvCol2);

        LVITEM lvI = {0};

        // Initialize LVITEM members that are common to all items.
        lvI.pszText = _T("足球"); // Sends an LVN_GETDISPINFO message.
        lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
        lvI.stateMask = 0;
        lvI.iSubItem = 0;
        lvI.state = 0;
        lvI.iImage = 0;

        ListView_InsertItem(hListView, &lvI);

        ListView_SetItemText(hListView, 0, 1, _T("100"));


        LVITEM lvI2 = { 0 };

        lvI2.pszText = _T("篮球"); // Sends an LVN_GETDISPINFO message.
        lvI2.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
        lvI2.stateMask = 0;
        lvI2.iSubItem = 0;
        lvI2.state = 0;

        ListView_InsertItem(hListView, &lvI2);

        ListView_SetItemText(hListView, 0, 1, _T("200"));
 
        return TRUE;
    }
    break;

    case WM_CLOSE: {
        EndDialog(hwndDlg, g_nResult);
        PostQuitMessage(0);
        return TRUE;
    }
    break;

    case WM_NOTIFY: {
   
        NMHDR* hdr = (NMHDR*)lParam;
        if (hdr->idFrom == IDC_LISTVIEW) {
        
            if (hdr->code == NM_CLICK) {
                NMITEMACTIVATE* hdr2 = (NMITEMACTIVATE*)lParam;

                TCHAR szBuf[256] = { 0 };
                ListView_GetItemText(hdr->hwndFrom,
                    hdr2->iItem,
                    0,
                    szBuf,
                    256);

                OutputDebugString(szBuf);

  

            
            }

        }


        return TRUE;
    }
    break;


    case WM_COMMAND: {
    
        if (lParam != NULL) {
            //表示是控件
            //表示控件

            //表示快捷键
            HWND hControlWnd = (HWND)lParam;

            int nNotifyCode = HIWORD(wParam);
            int nCtlId = LOWORD(wParam);

            if (nCtlId == IDC_BUTTON1) {
                switch (nNotifyCode)
                {
                case BN_CLICKED: {
                }
                 break;
                }
            }
            else if (nCtlId == IDC_COMBO1) {
                switch (nNotifyCode)
                {
                case CBN_SETFOCUS: {
                    OutputDebugStringA("CBN_SETFOCUS");
                }
                break;

                case CBN_KILLFOCUS: {
                    OutputDebugStringA("CBN_KILLFOCUS");
                }
                break;

                case CBN_SELCHANGE: {
                    int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
                        (WPARAM)0, (LPARAM)0);
                    TCHAR  ListItem[256];
                    (TCHAR)SendMessage((HWND)lParam, (UINT)CB_GETLBTEXT,
                        (WPARAM)ItemIndex, (LPARAM)ListItem);
                    OutputDebugString(ListItem);

                }
                break;

                }
            }
            else if (nCtlId == IDC_LIST1) {
                switch (nNotifyCode)
                {
                case LBN_SELCHANGE: {
                    int ItemIndex = SendMessage((HWND)lParam, (UINT)LB_GETCURSEL,
                        (WPARAM)0, (LPARAM)0);
                    TCHAR  ListItem[256];
                    (TCHAR)SendMessage((HWND)lParam, (UINT)LB_GETTEXT,
                        (WPARAM)ItemIndex, (LPARAM)ListItem);
                    OutputDebugString(ListItem);

                }
                break;

                }
            }

        }

    }
                     break;

    case WM_DESTROY: {
        
        return TRUE;
    }
    break;

    default:
        break;
    }

    return FALSE;
}


int OnPaint(HWND hwnd,      // handle to window
    UINT uMsg,      // message identifier
    WPARAM wParam,  // first message parameter
    LPARAM lParam) {

   
    return 1;
}

int OnCommand(HWND hwnd,      // handle to window
    UINT uMsg,      // message identifier
    WPARAM wParam,  // first message parameter
    LPARAM lParam) {

    if (lParam != NULL) {
        //表示是控件
        //表示控件

        //表示快捷键
        HWND hControlWnd = (HWND)lParam;

        int nNotifyCode = HIWORD(wParam);
        int nCtlId = LOWORD(wParam);

        if (nCtlId == 0x123) {
            switch (nNotifyCode)
            {
            case BN_CLICKED: {
                //创建一个对话框

                //1. 模态对话框
                g_nResult = DialogBox(g_hInst,
                    MAKEINTRESOURCE(IDD_MYDLG),
                    hwnd,
                    DialogProc);

                //MessageBox(NULL, NULL, NULL, NULL);


                //2. 非模态对话框
                //HWND hDlg = CreateDialog(g_hInst,
                //    MAKEINTRESOURCE(IDD_MYDLG),
                //    hwnd,
                //    DialogProc);

                //if (hDlg == nullptr){
                //    int n = 0;
                //}

                //ShowWindow(hDlg, SW_SHOWNORMAL);
                ////SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)_T("xxxx"));

                //MSG msg = { 0 };

                ////DestroyWindow

                //while (true) {

                //    //拿消息
                //    BOOL bRet = GetMessage(&msg,
                //        nullptr,
                //        0,
                //        0);

                //    if (!bRet) {
                //        break;
                //    }
                //    
                //    if (!IsDialogMessage(hDlg, &msg)) {
                //        DispatchMessage(&msg);
                //    }
                //}







            }
            break;

            default:
                break;
            }

        }
    }
    else {
        if (HIWORD(wParam) == 0) {
            //表示是菜单
            int nMenuID = LOWORD(wParam);

            switch (nMenuID)
            {
            case ID_OPEN: {
                OutputDebugStringA("打开");
            }
                          break;

            default:
                break;
            }


        }
        else if (HIWORD(wParam) == 1) {
            //表示快捷键
            int nID = LOWORD(wParam);

            switch (nID)
            {
            case ID_ACC_OPEN: {
                OutputDebugStringA("快捷键 打开");
            }
                              break;

            default:
                break;
            }

        }
    
    }
    
  
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

        //绘制状态栏
        g_hStatusWnd  =  ::CreateWindow(_T("msctls_statusbar32"),
            NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
            hwnd, NULL, lpCs->hInstance, NULL);

        //设置个数
        int nPartAry[] = { 100, 200, 300 , -1 };
        BOOL bRet = SendMessage(g_hStatusWnd,
                    SB_SETPARTS,
                    (WPARAM)sizeof(nPartAry)/sizeof(int),
                    (LPARAM)nPartAry);
        //
        //PostMessage(g_hStatusWnd, SB_SETTEXT, 0, (LPARAM)_T("Hello World!"));
        //SendMessage();
        SendMessage(g_hStatusWnd, SB_SETTEXT, 0, (LPARAM)_T("Hello World!"));
        SendMessage(g_hStatusWnd, SB_SETTEXT, 1, (LPARAM)_T("1"));
        SendMessage(g_hStatusWnd, SB_SETTEXT, 2, (LPARAM)_T("2"));
        SendMessage(g_hStatusWnd, SB_SETTEXT, 3, (LPARAM)_T("3"));


        g_hBtnWnd = ::CreateWindow(_T("BUTTON"),
            _T("创建对话框"), WS_CHILD | WS_VISIBLE, 0, 0, 50, 50,
            hwnd, (HMENU)0x123, lpCs->hInstance, NULL);


        //

        //SendMessage(g_hBtnWnd, WM_SETTEXT, 0, (LPARAM)_T("取消"));

        int n = 0;
    }
    break;

    case WM_SIZE: {
    
        int nHeight = HIWORD(lParam);
        int nWidth = LOWORD(lParam);

        RECT rc;

        GetWindowRect(g_hStatusWnd,
                      &rc);

        int nStatusWndHeight = rc.bottom - rc.top;

        int nX = 0;
        int nY = nHeight - nStatusWndHeight;

        MoveWindow(g_hStatusWnd, nX, nY,
            nWidth,
            rc.bottom - rc.top,
            TRUE);


    }
    break;

    case WM_COMMAND: {
        OnCommand(hwnd, uMsg, wParam, lParam);

    }
    break;
    
    //定时器
    case WM_TIMER: {

        //OutputDebugStringA("WM_TIMER");

        //InvalidateRect(hwnd, NULL, false);
        //UpdateWindow(hwnd);     

    }
                   break;

    case WM_PAINT: {
        OutputDebugStringA("WM_PAINT");
        BeginPaint(hwnd, NULL);
        EndPaint(hwnd, NULL);
        //ValidateRect(hwnd, NULL);
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

    case WM_DESTROY: {
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

    g_hInst = hInstance;

    //窗口类的结构体
    WNDCLASSEX wcs = { 0 };

    wcs.cbSize = sizeof(WNDCLASSEX);
    wcs.lpszClassName = _T("CR32_WinCls"); // 指定窗口类名，为后面的窗口类注册和创建窗口做准备
    wcs.lpfnWndProc = MyWindowProc; //指定窗口回调函数，为后面的消息循环做准备
    wcs.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    //(HBRUSH)(COLOR_WINDOW + 1);

    wcs.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

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
        100,
        100,
        800,
        600,
        NULL,
        NULL,
        hInstance,
        NULL);
    if (hWnd == nullptr) {

        return 0;
    }

    HACCEL haccel = LoadAccelerators(hInstance, 
                              MAKEINTRESOURCE(IDR_ACCELERATOR1));

    //3. 显示
    //
    ShowWindow(hWnd, SW_SHOWNORMAL);

    // 更新
    UpdateWindow(hWnd);


    //4. 消息循环
    //
    MSG msg = { 0 };

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

        if (!TranslateAccelerator(
            hWnd,  // handle to receiving window 
            haccel,    // handle to active accelerator table 
            &msg))         // message data 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    }


    return 0;
}