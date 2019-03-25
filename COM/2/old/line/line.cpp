#include <stdio.h>
#include "../CAD/CAD/plugin.h"
#include <windows.h>


Plugin g_plugin = { 
    CADGetMenuName, 
    CADOnLButtonDown,
    CADOnMouseMove,
    CADOnLButtonUp,
    CADOnDraw,
    CADSetID,
    CADGetID, 
    };


const char* CADGetMenuName() {
    return "Line(&L)";
}

int CADOnLButtonDown(HWND hWnd, int x, int y) {
    return PLUGIN_OK;
}


int CADOnMouseMove(HWND hWnd, int x, int y) {
    return PLUGIN_OK;
}

int CADOnLButtonUp(HWND hWnd, int x, int y) {
    return PLUGIN_OK;
}

int CADOnDraw(HWND hWnd, HDC hdc) {
    MessageBox(NULL, "ªÊ÷∆÷±œﬂ", NULL, MB_OK);
    return PLUGIN_OK;
}

int CADOnMouseDown(HWND hWnd, int x, int y) {
    return PLUGIN_OK;
}

static int ID = 0;

int CADSetID(int id) {
    ID = id;
    return PLUGIN_OK;
}

int CADGetID() {
    return ID;
}


Plugin* GetPlugin() {
    return &g_plugin;
}