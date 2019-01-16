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
HINSTANCE g_hInst = nullptr;
int g_nResult = 0;

//DC
//BeginPaint/EndPaint, ��WM_PAINT��Ϣ��ʹ��
//GetDC GetDesktopDC GetWindowDC... / ReleaseDC
//CreateCompatibleDC CreateDC / DeleteDC

//�Ի���Ļص�����
INT_PTR CALLBACK DialogProc(HWND hwndDlg,  // handle to dialog box
    UINT uMsg,     // message 
    WPARAM wParam, // first message parameter
    LPARAM lParam) // second message parameter;
{
    switch (uMsg)
    {
    case WM_CLOSE: {
        EndDialog(hwndDlg, g_nResult);
        PostQuitMessage(0);
        return TRUE;
    }
    break;

    case WM_COMMAND: {
    
        if (lParam != NULL) {
            //��ʾ�ǿؼ�
            //��ʾ�ؼ�

            //��ʾ��ݼ�
            HWND hControlWnd = (HWND)lParam;

            int nNotifyCode = HIWORD(wParam);
            int nCtlId = LOWORD(wParam);

            if (nCtlId == IDC_BUTTON1) {
                switch (nNotifyCode)
                {
                case BN_CLICKED: {

                    OPENFILENAME ofn = { 0 };        // common dialog box structure
                    TCHAR szFile[260] = {0};       // buffer for file name
                   
                    HANDLE hf;              // file handle

                                            // Initialize OPENFILENAME
                    ZeroMemory(&ofn, sizeof(OPENFILENAME));
                    ofn.lStructSize = sizeof(OPENFILENAME);
                    ofn.hwndOwner = hwndDlg;
                    ofn.lpstrFile = szFile;
                    ofn.nMaxFile = sizeof(szFile);
                    ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0");
                    ofn.nFilterIndex = 1;
                    ofn.lpstrFileTitle = NULL;
                    ofn.nMaxFileTitle = 0;
                    ofn.lpstrInitialDir = NULL;
                    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                    // Display the Open dialog box. 
                    BOOL b = GetOpenFileName(&ofn);
                    if (b) {
                    
                        OutputDebugString(szFile);
                    }






                    //MessageBox(0, 0, 0, 0);
                    //��ȡ��Դ
                    HRSRC hRes = FindResource(g_hInst,
                                        MAKEINTRESOURCE(IDR_EXE2),
                                        _T("EXE"));
                    if (hRes == NULL)
                    {
                        OutputDebugStringA("Could not locate dialog box.");
                        break;
                    }

                    HGLOBAL hResLoad = LoadResource(g_hInst, hRes);
                    if (hResLoad == NULL)
                    {
                        OutputDebugStringA("Could not load dialog box.");
                        break;
                    }
                    
                    LPVOID lpAddr = LockResource(hResLoad);

                    size_t nResSize = SizeofResource(g_hInst, hRes);

                    //���Ȼ�ȡ��ʱ·��
                    TCHAR szTmpPath[MAX_PATH];

                    int nRet = GetTempPath(MAX_PATH, szTmpPath);
                    if (nRet == 0) {
                        break;
                    }
                   
                    TCHAR szTmpNamePath[MAX_PATH];

                    wsprintf(szTmpNamePath, _T("%s%s"), szTmpPath, _T("tmp.zip"));

                    HANDLE hFile =  CreateFile(szTmpNamePath,
                               GENERIC_WRITE | GENERIC_READ,
                               FILE_SHARE_READ,
                               NULL,
                               CREATE_ALWAYS,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);

                    DWORD dwWritedBytes = 0;

                    BOOL bRet = WriteFile(hFile,
                        lpAddr,
                        nResSize,
                        &dwWritedBytes,
                        NULL);

                    CloseHandle(hFile);


                    int n = nResSize;
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
                //����һ���Ի���

                //1. ģ̬�Ի���
                //g_nResult = DialogBox(g_hInst,
                //    MAKEINTRESOURCE(IDD_MYDLG),
                //    hwnd,
                //    DialogProc);

                //MessageBox(NULL, NULL, NULL, NULL);


                //2. ��ģ̬�Ի���
                HWND hDlg = CreateDialog(g_hInst,
                    MAKEINTRESOURCE(IDD_MYDLG),
                    hwnd,
                    DialogProc);

                if (hDlg == nullptr){
                    int n = 0;
                }

                ShowWindow(hDlg, SW_SHOWNORMAL);
                //SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)_T("xxxx"));

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

                    if (IsDialogMessage(hDlg, &msg)) {
                        DispatchMessage(&msg);
                    }
                }







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
            _T("�����Ի���"), WS_CHILD | WS_VISIBLE, 0, 0, 50, 50,
            hwnd, (HMENU)0x123, lpCs->hInstance, NULL);


        //

        //SendMessage(g_hBtnWnd, WM_SETTEXT, 0, (LPARAM)_T("ȡ��"));

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

    g_hInst = hInstance;

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