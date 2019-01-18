#include <windows.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include "resource.h"
#include <Commctrl.h>
#include <functional>
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



#ifdef _UNICODE 
    #define tstring wstring
    #define tstringstream wstringstream  
#else
    #define tstring string
    #define tstringstream stringstream  
#endif

typedef std::function<void(HWND, HWND, std::tstring, WIN32_FIND_DATA)> FOO;

tstring g_CurPath;
FOO g_f;

bool EnumFile(LPCTSTR strFilePath, FOO fn, HWND hListView, HWND hTreeView) {

    tstring strFind = strFilePath;
    g_CurPath = strFind;
    strFind += _T("*.*");

    WIN32_FIND_DATA FileData;
    HANDLE hSearch;

    BOOL fFinished = FALSE;

    hSearch = FindFirstFile(strFind.c_str(), &FileData);
    if (hSearch == INVALID_HANDLE_VALUE){
        return false;
    }

    while (!fFinished)
    {
        //���

        //�����ݣ����������
        tstring str = strFilePath;
        str += FileData.cFileName;

        fn(hListView, hTreeView,str, FileData);
      
        if (!FindNextFile(hSearch, &FileData))
        {
            if (GetLastError() == ERROR_NO_MORE_FILES)
            {
                fFinished = TRUE;
                continue;
            }
            else
            {
                return FALSE;
            }
        }

    }

    return true;
}

WNDPROC g_OldProc;

LRESULT CALLBACK MyEditWndProc(HWND hwnd,      // handle to window
    UINT uMsg,      // message identifier
    WPARAM wParam,  // first message parameter
    LPARAM lParam)   // second message parameter);
{
    if (uMsg == WM_CHAR)
    {
        OutputDebugStringA("123");
        TCHAR ch = (TCHAR)wParam;
        if (ch >= '0' && ch <= '9'){
            return TRUE;
        }

    }


    return CallWindowProc(g_OldProc, hwnd, uMsg, wParam, lParam);
}




//�Ի���Ļص�����
INT_PTR CALLBACK DialogProc(HWND hwndDlg,  // handle to dialog box
    UINT uMsg,     // message 
    WPARAM wParam, // first message parameter
    LPARAM lParam) // second message parameter;
{
    switch (uMsg)
    {
    case WM_INITDIALOG: {
        
        //���໯
        //��ȡedit�ؼ����

        HWND hEdit = GetDlgItem(hwndDlg, IDC_EDIT1);

        //���ô��ڹ��̺���
        g_OldProc = (WNDPROC)SetWindowLong(hEdit, GWL_WNDPROC, (LONG)MyEditWndProc);

        


        
        
        //��������

        TCHAR szBuf[256] = { 0 };

        GetLogicalDriveStrings(256, szBuf);

        //��ȡcombo�Ĵ��ھ��
        HWND hComBo = GetDlgItem(hwndDlg, IDC_COMBO1);

        TCHAR szText1[] = _T("x86");
        TCHAR szText2[] = _T("x64");

        BOOL bRet = SendMessage(hComBo, CB_ADDSTRING, 0, (LPARAM)szText1);
        bRet =  SendMessage(hComBo, CB_ADDSTRING, 0, (LPARAM)szText2);
        bRet = SendMessage(hComBo, CB_ADDSTRING, 0, (LPARAM)_T("1"));
        bRet = SendMessage(hComBo, CB_ADDSTRING, 0, (LPARAM)_T("2"));
        bRet = SendMessage(hComBo, CB_ADDSTRING, 0, (LPARAM)_T("3"));
        bRet = SendMessage(hComBo, CB_ADDSTRING, 0, (LPARAM)_T("4"));

        //ֱ����ؼ�����Ϣ
        SendDlgItemMessage(hwndDlg,
            IDC_LIST1,
            LB_ADDSTRING,
            0,
            (LPARAM)_T("����"));

        SendDlgItemMessage(hwndDlg,
            IDC_LIST1,
            LB_ADDSTRING,
            0,
            (LPARAM)_T("����"));

        
        //listview
        //��ȡListView�Ĵ��ھ��
        HWND hListView = GetDlgItem(hwndDlg, IDC_LISTVIEW);
        
        //����ͼ��
        //��ϵͳ��ͼ��List
        SHFILEINFOA si = {0};
        HIMAGELIST hSmallImgLst = (HIMAGELIST)SHGetFileInfoA(NULL,
            FILE_ATTRIBUTE_NORMAL,
            &si,
            sizeof(SHFILEINFOA),
            SHGFI_SMALLICON | SHGFI_SYSICONINDEX);


        //����ͼ��List���õ�ListView��
        ListView_SetImageList(hListView, hSmallImgLst, LVSIL_SMALL);


        //����ListView�ķ��
        DWORD dwOldStyle = SendMessage(hListView, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);
        SendMessage(hListView,
                    LVM_SETEXTENDEDLISTVIEWSTYLE,
                    0, 
                    (LPARAM)dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

        //���뱨��ͷ
        LVCOLUMN lvCol1 = {0};
        lvCol1.pszText = _T("�ļ���");
        lvCol1.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvCol1.iSubItem = 0;
        lvCol1.cx = 100;

        int nRet = ListView_InsertColumn(hListView, 0, &lvCol1);

        LVCOLUMN lvCol2 = { 0 };
        lvCol2.pszText = _T("�ļ���С");
        lvCol2.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvCol2.iSubItem = 1;
        lvCol2.cx = 100;

        ListView_InsertColumn(hListView, 1, &lvCol2);

        g_f = [](HWND hListView, HWND hTreeView, std::tstring str, WIN32_FIND_DATA FileData)->void {

            OutputDebugString(str.c_str());
            SHFILEINFO si = { 0 };

            LVITEM lvI = { 0 };

            //��ȡָ���ļ���ͼ��
            memset(&si, 0, sizeof(si));
            SHGetFileInfo(str.c_str(),
                FILE_ATTRIBUTE_NORMAL,
                &si,
                sizeof(SHFILEINFO),
                SHGFI_SMALLICON | SHGFI_SYSICONINDEX | SHGFI_USEFILEATTRIBUTES);


            int iImage = 0;
            __int64 nFileSize = 0;
            if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                //��ʾ���ļ���
                iImage = 4;
                nFileSize = 0;
            }
            else {
                iImage = si.iIcon;
                nFileSize = FileData.nFileSizeHigh;
                nFileSize = (nFileSize << 32) & 0xFFFFFFFF00000000;
                nFileSize += FileData.nFileSizeLow;

            }

            // Initialize LVITEM members that are common to all items.
            lvI.pszText = FileData.cFileName; // Sends an LVN_GETDISPINFO message.
            lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
            lvI.stateMask = 0;
            lvI.iSubItem = 0;
            lvI.state = 0;
            lvI.iImage = iImage;

            ListView_InsertItem(hListView, &lvI);

            tstringstream ss;

            //ss << nFileSize;
            //ss << _T("\0");
            //TCHAR* p = (TCHAR*)ss.str().c_str();

            TCHAR szBuf[256] = { 0 };

            //_itot_s(nFileSize, szBuf, 10);

            wsprintf(szBuf, _T("%I64d"), nFileSize);

            ListView_SetItemText(hListView, 0, 1, szBuf);


            TVINSERTSTRUCT tvsChild1 = { 0 };
            tvsChild1.hParent = NULL;
            tvsChild1.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE;
            tvsChild1.item.pszText = FileData.cFileName;
            tvsChild1.item.iImage = iImage;
            tvsChild1.item.iSelectedImage = iImage;

            TreeView_InsertItem(hTreeView, &tvsChild1);
        };



        //��treeview�в�������
        //��ȡListView�Ĵ��ھ��
        HWND hTreeView = GetDlgItem(hwndDlg, IDC_TREEVIEW);

        SetWindowLong(hTreeView,
            GWL_STYLE,
            GetWindowLong(hTreeView, GWL_STYLE) | TVS_HASBUTTONS  | TVS_SINGLEEXPAND | TVS_FULLROWSELECT | TVS_HASLINES);

        TreeView_SetImageList(hTreeView, hSmallImgLst, TVSIL_NORMAL);

        TVINSERTSTRUCT tvs = {0};
        tvs.hParent = NULL;
        tvs.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE;
        tvs.item.iImage = 4;
        tvs.item.iSelectedImage = 4;
        tvs.item.pszText = _T("C:");


        HTREEITEM hParent  = TreeView_InsertItem(hTreeView, &tvs);

  
        //ö�ٲ��������
        EnumFile(_T("c:\\"), g_f, hListView, hTreeView);


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
                //NMITEMACTIVATE* hdr2 = (NMITEMACTIVATE*)lParam;

                //TCHAR szBuf[256] = { 0 };
                //ListView_GetItemText(hdr->hwndFrom,
                //    hdr2->iItem,
                //    0,
                //    szBuf,
                //    256);

                //OutputDebugString(szBuf);   
            }
            else if (hdr->code == NM_DBLCLK) {   
                NMITEMACTIVATE* hdr2 = (NMITEMACTIVATE*)lParam;

                TCHAR szBuf[256] = { 0 };
                ListView_GetItemText(hdr->hwndFrom,
                    hdr2->iItem,
                    0,
                    szBuf,
                    256);

                tstring str = g_CurPath + szBuf;
                OutputDebugString(str.c_str());
                
                //�����ж�˫�����Ƿ����ļ���
                WIN32_FIND_DATA FileData;
                HANDLE hSearch = FindFirstFile(str.c_str(), &FileData);
                if (hSearch == INVALID_HANDLE_VALUE) {
                    return TRUE;
                }

                if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

                    //����Ϣ����listview���
                    HWND hListView = hdr->hwndFrom;
                    ListView_DeleteAllItems(hListView);
                    
                    str += _T("\\");
                    //EnumFile(str.c_str(), g_f, hListView);
                }

                CloseHandle(hSearch);

            }

        }


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
                g_nResult = DialogBox(g_hInst,
                    MAKEINTRESOURCE(IDD_MYDLG),
                    hwnd,
                    DialogProc);

                //MessageBox(NULL, NULL, NULL, NULL);


                //2. ��ģ̬�Ի���
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

                //    //����Ϣ
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