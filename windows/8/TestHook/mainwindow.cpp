#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <sstream>
#include <string>
#include <stdlib.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

HHOOK g_hHook;

LRESULT __stdcall KeyboardProc(int code,       // hook code
    WPARAM wParam,  // virtual-key code
    LPARAM lParam   // keystroke-message information
    ) {

    int nKey = (int)wParam;
    stringstream ss;
    ss << nKey << "pressed" << endl;
    OutputDebugStringA(ss.str().c_str());

    return CallNextHookEx(g_hHook, code, wParam, lParam);
}

void MainWindow::on_btn_Local_clicked()
{
    //本地钩子
//    g_hHook = SetWindowsHookEx(WH_KEYBOARD,
//        KeyboardProc,
//        NULL,
//        GetCurrentThreadId());

    //全局钩子

    HMODULE hDll = LoadLibraryA("Hook.dll");

    HOOKPROC pfn = (HOOKPROC)GetProcAddress(hDll, "KeyboardProc");

    g_hHook = SetWindowsHookEx(WH_KEYBOARD,
        (HOOKPROC)pfn,
        hDll,
        0);

}

void MainWindow::on_btn_free_clicked()
{
    UnhookWindowsHookEx(g_hHook);
}
