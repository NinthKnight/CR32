// TankWar.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include "glut\glut.h"
#include "MyView.h"

#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "opengl32.lib")

const unsigned int SCR_WIDTH = 650;
const unsigned int SCR_HEIGHT = 650;

CMyView g_View;


//绘制一个矩形
void testDrawRect() {
    //绘制矩形
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(0.0f, 620.0f, 30.0f, 650.0f);
    //glRectf(0.5f, 0.5f, 0.6f, 0.6f);
}

//通知重绘
void update() {
    glutPostRedisplay(); //调用这个函数可以重新绘图,每次相应消息之后，所有全部重绘
}

//显示回调函数
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);/* clear all pixels   */

    g_View.drawMap();
 
    //testDrawRect();
    glFlush();
}

//键盘回调函数
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 033: // ESC键 和 'q' 键退出游戏
            exit(EXIT_SUCCESS);
            break;
        case 'q':
            exit(EXIT_SUCCESS);
            break;
        case 'w': {
            std::cout << "w" << std::endl;
            g_View.OnUp();
        }
             break;
        case 's': {
            std::cout << "s" << std::endl;

        }
            break;
        case 'a': {
            std::cout << "a" << std::endl;

        }
        break;
        case 'd': {
            std::cout << "d" << std::endl;

        }
        break;
    }
    update();
}

//定时器回调函数
void idle(int value)
{
    std::cout << "123" << std::endl;

    update();
    glutTimerFunc(1000, idle, 1);
}


int main()
{

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //设置显示模式
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT); //设置窗口大小 
    glutInitWindowPosition(200, 200); //设置窗口在屏幕上的位置 
    glutCreateWindow("坦克大战"); //创建窗口并给出标题 
   
    //键盘回调函数
    glutKeyboardFunc(keyboard);

    //定时器
    glutTimerFunc(1000, idle, 1); 

    //添加显示的回调函数
    glutDisplayFunc(display); //注册显示窗口时回调函数
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//清屏
    glOrtho(0.0f, SCR_WIDTH, 0.0f, SCR_HEIGHT, 1.0, -1.0);
    //消息循环（处理操作系统等的消息，例如键盘、鼠标事件等）
    glutMainLoop(); 

    return 0;
}

