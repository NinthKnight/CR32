// TankWar.cpp : �������̨Ӧ�ó������ڵ㡣
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


//����һ������
void testDrawRect() {
    //���ƾ���
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(0.0f, 620.0f, 30.0f, 650.0f);
    //glRectf(0.5f, 0.5f, 0.6f, 0.6f);
}

//֪ͨ�ػ�
void update() {
    glutPostRedisplay(); //������������������»�ͼ,ÿ����Ӧ��Ϣ֮������ȫ���ػ�
}

//��ʾ�ص�����
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);/* clear all pixels   */

    g_View.drawMap();
 
    //testDrawRect();
    glFlush();
}

//���̻ص�����
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 033: // ESC�� �� 'q' ���˳���Ϸ
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

//��ʱ���ص�����
void idle(int value)
{
    std::cout << "123" << std::endl;

    update();
    glutTimerFunc(1000, idle, 1);
}


int main()
{

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //������ʾģʽ
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT); //���ô��ڴ�С 
    glutInitWindowPosition(200, 200); //���ô�������Ļ�ϵ�λ�� 
    glutCreateWindow("̹�˴�ս"); //�������ڲ��������� 
   
    //���̻ص�����
    glutKeyboardFunc(keyboard);

    //��ʱ��
    glutTimerFunc(1000, idle, 1); 

    //�����ʾ�Ļص�����
    glutDisplayFunc(display); //ע����ʾ����ʱ�ص�����
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//����
    glOrtho(0.0f, SCR_WIDTH, 0.0f, SCR_HEIGHT, 1.0, -1.0);
    //��Ϣѭ�����������ϵͳ�ȵ���Ϣ��������̡�����¼��ȣ�
    glutMainLoop(); 

    return 0;
}

