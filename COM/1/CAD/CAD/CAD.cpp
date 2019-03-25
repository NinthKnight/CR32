// CAD.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <list>
#include <stdlib.h>

using namespace std;

typedef void (*ON_DRAW)();
typedef const char* (*GET_MENU_NAME)();

/*
1.dll数量
*/

struct Plugin {
    int id;
    GET_MENU_NAME pfnGetMenuName;
    ON_DRAW       pfnOnDraw;
};

list<Plugin> g_plugins;


void LoadAllPlugin() {
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
        printf("No .dll files found.\n");
    }

    while (fFinished) {
        szNewPath[0] = '\0';
        strcpy(szNewPath, szDirPath);
        strcat(szNewPath, FileData.cFileName);
       
        HMODULE hDll = LoadLibrary(szNewPath);
        GET_MENU_NAME pfnGetMenuName = (GET_MENU_NAME)GetProcAddress(hDll, "CADGetMenuName");
        if (pfnGetMenuName == NULL) {//不是自己人
            FreeLibrary(hDll);
            fFinished = FindNextFile(hSearch, &FileData);
            continue;
        } 
        ON_DRAW pfnOnDraw = (ON_DRAW)GetProcAddress(hDll, "CADOnDraw");
        if (pfnOnDraw == NULL) {//不是自己人
            FreeLibrary(hDll);
            fFinished = FindNextFile(hSearch, &FileData);
            continue;
        }

        static int g_num = 1;

        //保存信息
        struct Plugin plugin;
        plugin.id = g_num++;
        plugin.pfnGetMenuName = pfnGetMenuName;
        plugin.pfnOnDraw = pfnOnDraw;
        g_plugins.push_back(plugin);

        fFinished = FindNextFile(hSearch, &FileData);
    }

    FindClose(hSearch);
}


void ShowMenu() {
    for (list<Plugin>::iterator it = g_plugins.begin();
    it != g_plugins.end();
        it++) {
       printf("%d.%s\n", (*it).id, (*it).pfnGetMenuName());
    }
}

int main(int argc, char* argv[]) {
    //加载插件
    LoadAllPlugin();

    //显示菜单
    ShowMenu();

    //框架

    int  input;
    scanf("%d", &input);
    for (list<Plugin>::iterator it = g_plugins.begin();
    it != g_plugins.end();
        it++) {
        struct Plugin plugin = *it;
        if (plugin.id == input) {
            plugin.pfnOnDraw();
        }
    }

    system("pause");
    return 0;
}

