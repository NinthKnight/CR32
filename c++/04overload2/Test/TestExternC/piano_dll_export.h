//播放一个音符 
//例如ch = 'F',播放当前目录下"AppPath\Sound_F.wav"文件
#include <windows.h>
void fun_playOneSound(char ch);

//为指定窗口创建音符播放环境
void fun_Create(HWND hwnd);

//释放音符播放环境
void fun_Release();