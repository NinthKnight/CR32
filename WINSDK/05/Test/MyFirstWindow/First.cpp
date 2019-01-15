#include <windows.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include "resource.h"
#include <Commctrl.h>
using namespace std;


//windows ����Ϣ�ķ���
/*
    1. ��ͨ��Ϣ
       WM_CREATE
       WM_DESTROY
       WM_CLOSE
       WM_QUIT
       WM_SIZE
       WM_PAINT
       WM_TIMER
       WM_KEYDOWN, WM_KEYUP
       WM_LBUTTONDOWN....

    2. command��Ϣ WM_COMMAND
       �˵��� ��ݼ��� ���ֿؼ�

    3. notify��Ϣ WM_NOTIFY
       ĳЩ���ӵĿؼ��й�

    �ؼ���
       �༭��
       check box
       radio box



*/

HICON g_AppleIcon = nullptr;
HWND g_hStatusWnd = nullptr;
HWND g_hBtnWnd = nullptr;

//DC
//BeginPaint/EndPaint, ��WM_PAINT��Ϣ��ʹ��
//GetDC GetDesktopDC GetWindowDC... / ReleaseDC
//CreateCompatibleDC CreateDC / DeleteDC

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
        //��ʾ�ǿؼ�
        //��ʾ�ؼ�

        //��ʾ��ݼ�
        HWND hControlWnd = (HWND)lParam;

        int nNotifyCode = HIWORD(wParam);
        int nCtlId = LOWORD(wParam);

        if (nCtlId == 0x123) {
            switch (nNotifyCode)
            {
            case BN_CLICKED: {

                SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)_T("xxxx"));

            }
                             break;

            default:
                break;
            }

        }
    }
    else {
        if (HIWORD(wParam) == 0) {
            //��ʾ�ǲ˵�
            int nMenuID = LOWORD(wParam);

            switch (nMenuID)
            {
            case ID_OPEN: {
                OutputDebugStringA("��");
            }
                          break;

            default:
                break;
            }


        }
        else if (HIWORD(wParam) == 1) {
            //��ʾ��ݼ�
            int nID = LOWORD(wParam);

            switch (nID)
            {
            case ID_ACC_OPEN: {
                OutputDebugStringA("��ݼ� ��");
            }
                              break;

            default:
                break;
            }

        }
    
    }
    
  
    return 1;
}

//���ڻص�����
LRESULT CALLBACK MyWindowProc(HWND hwnd,      // handle to window
    UINT uMsg,      // message identifier
    WPARAM wParam,  // first message parameter
    LPARAM lParam)   // second message parameter);
{
    int nRet = 1;

    switch (uMsg)
    {
    case WM_CREATE: {
        //��һЩ���ڳ�ʼ���Ĳ���
        LPCREATESTRUCT lpCs = (LPCREATESTRUCT)lParam;


        g_AppleIcon = LoadIcon(lpCs->hInstance,
            MAKEINTRESOURCE(IDI_APPLE));

        //����״̬��
        g_hStatusWnd  =  ::CreateWindow(_T("msctls_statusbar32"),
            NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
            hwnd, NULL, lpCs->hInstance, NULL);

        //���ø���
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
            _T("ȷ��"), WS_CHILD | WS_VISIBLE, 0, 0, 50, 50,
            hwnd, (HMENU)0x123, lpCs->hInstance, NULL);


        //

        SendMessage(g_hBtnWnd, WM_SETTEXT, 0, (LPARAM)_T("ȡ��"));

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
    
    //��ʱ��
    case WM_TIMER: {

        //OutputDebugStringA("WM_TIMER");

        //InvalidateRect(hwnd, NULL, false);//����Ϊ��Ч������ϵͳ�ں��ʵ�ʱ�����´���
        //UpdateWindow(hwnd);     //�������£�����Ϊ��Ч

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
        //������������
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
        //����WM_QUIT��Ϣ
        //PostQuitMessage(0);

        PostMessage(hwnd, WM_QUIT, 0, 0);
    }
                     break;

    case WM_CLOSE: {
        int nRet = MessageBoxA(hwnd, "�Ƿ��˳�����", "��ʾ", MB_OKCANCEL);
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

    //������Ľṹ��
    WNDCLASSEX wcs = { 0 };

    wcs.cbSize = sizeof(WNDCLASSEX);
    wcs.lpszClassName = _T("CR32_WinCls"); // ָ������������Ϊ����Ĵ�����ע��ʹ���������׼��
    wcs.lpfnWndProc = MyWindowProc; //ָ�����ڻص�������Ϊ�������Ϣѭ����׼��
    wcs.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    //(HBRUSH)(COLOR_WINDOW + 1);

    wcs.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

    //����һ������
    //1. ע�ᴰ����

    //
    ATOM atom = RegisterClassEx(&wcs);
    if (atom == 0) {
        return 0;
    }


    //2. ���Լ�ע��Ĵ�������Ϊģ�壬����������
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

    //3. ��ʾ
    //
    ShowWindow(hWnd, SW_SHOWNORMAL);

    // ����
    UpdateWindow(hWnd);


    //4. ��Ϣѭ��
    //
    MSG msg = { 0 };

    //DestroyWindow

    while (true) {

        //����Ϣ
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