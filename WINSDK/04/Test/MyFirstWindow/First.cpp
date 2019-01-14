#include <windows.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include "resource.h"
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

//DC
//BeginPaint/EndPaint, ��WM_PAINT��Ϣ��ʹ��
//GetDC GetDesktopDC GetWindowDC... / ReleaseDC
//CreateCompatibleDC CreateDC / DeleteDC

int OnPaint(HWND hwnd,      // handle to window
    UINT uMsg,      // message identifier
    WPARAM wParam,  // first message parameter
    LPARAM lParam) {

    //����
    //��ȡ��Ļ�����ݣ������뵽�ڴ�DC��

    //������Ĵ���DC�е����ݷ��뵽�ڴ�DC��

    //1. ���Ȼ�ȡ����Ĵ���HWND
    HWND hDskWnd = GetDesktopWindow();

    //2. ��ȡ����Ĵ���DC
    HDC hDskDC = GetDC(hDskWnd);

    //3. ����һ���ڴ�DC������DC������ʼ��bitmap��1*1
    //HDC hMemDC = CreateCompatibleDC(hDskDC);

    //// λͼ bitmap, jpg, png, gif, bmp
    ////4. ����һ�����ڴ�DC����ݵ�bitmap����

    ////��ȡϵͳ����Ļ���
    int nWidth = GetSystemMetrics(SM_CXSCREEN);
    int nHeight = GetSystemMetrics(SM_CYSCREEN);

    //HBITMAP hBitmap = CreateCompatibleBitmap(hDskDC,
    //                                        nWidth,
    //                                        nHeight);

    ////5. �����ڴ�DC��bitmap
    //SelectObject(hMemDC, hBitmap);


    ////6. ������DC��Bitmap�е����ݿ������ڴ�DC��
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

    //���ڴ�DC���ó����ݣ����뵽������
    //�ÿͻ�����DC
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
    ////����һ����ˢ
    //HBRUSH hbrush, hbrushOld;
    //hbrush = CreateSolidBrush(RGB(255, 0, 0));
    //hbrushOld = (HBRUSH)SelectObject(hDC, hbrush);
    //Rectangle(hDC, 100, 100, 200, 200);


    //SelectObject(hDC, hbrushOld);
    //DeleteObject(hbrush);

    ////����һ������
    ////CreatePen();
    ////��ֱ��
    ////LineTo


    //DrawIcon(hDC, 0, 0, g_AppleIcon);

    //EndPaint(hwnd, &ps);

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


        SetTimer(hwnd, 1, 1000, nullptr);

        int n = 0;
    }
    break;

    //��ʱ��
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

    case WM_DESTROY:{
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

    //��ȡ���ⴰ�ڵĴ��ھ��

    HWND hCalcWnd =  FindWindow(_T("Notepad"), NULL);




    //�������ϻ���
    HWND hDskWnd = GetDesktopWindow();

    HDC hDC = GetWindowDC(hCalcWnd);

    RECT rc;
    rc.top = 200;
    rc.left = 0;
    rc.right = 100;
    rc.bottom = 400;

    DrawText(hDC, _T("Hello WOrld!"), -1, &rc, DT_LEFT);


    ReleaseDC(hCalcWnd, hDC);


    //������Ľṹ��
    WNDCLASSEX wcs = {0};

    wcs.cbSize = sizeof(WNDCLASSEX);
    wcs.lpszClassName = _T("CR32_WinCls"); // ָ������������Ϊ����Ĵ�����ע��ʹ���������׼��
    wcs.lpfnWndProc = MyWindowProc; //ָ�����ڻص�������Ϊ�������Ϣѭ����׼��
    wcs.hbrBackground =  (HBRUSH)GetStockObject(WHITE_BRUSH);
    //(HBRUSH)(COLOR_WINDOW + 1);

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


    //3. ��ʾ
    //
    ShowWindow(hWnd, SW_SHOWNORMAL);

    // ����
    UpdateWindow(hWnd);


    //4. ��Ϣѭ��
    //
    MSG msg = {0};

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

        //������Ϣ WM_KEYDOWN--> WM_CHAR
        TranslateMessage(&msg);

        //�ɷ���Ϣ
        DispatchMessage(&msg);
    }
    

    return 0;
}