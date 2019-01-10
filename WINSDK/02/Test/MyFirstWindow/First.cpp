#include <windows.h>
#include <tchar.h>

//���ڻص�����
LRESULT CALLBACK MyWindowProc(HWND hwnd,      // handle to window
    UINT uMsg,      // message identifier
    WPARAM wParam,  // first message parameter
    LPARAM lParam)   // second message parameter);
{
    if (uMsg == WM_DESTROY) {
    
        
        //����WM_QUIT��Ϣ
        //PostQuitMessage(0);


        PostMessage(hwnd, WM_QUIT, 0, 0);
        return 1;
    }


    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPreInstance,
    LPSTR lpCmdLine,
    int nShow) {

    //������Ľṹ��
    WNDCLASSEX wcs = {0};

    wcs.cbSize = sizeof(WNDCLASSEX);
    wcs.lpszClassName = _T("CR32_WinCls"); // ָ������������Ϊ����Ĵ�����ע��ʹ���������׼��
    wcs.lpfnWndProc = MyWindowProc; //ָ�����ڻص�������Ϊ�������Ϣѭ����׼��


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

        //�ɷ���Ϣ
        DispatchMessage(&msg);
    }
    

    return 0;
}