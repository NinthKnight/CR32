// TestCureVirtual.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


//�������ṩ�ӿڣ����ʣ���������Ӧ������λ��
//������ͨ����д���ݳ�Ա��ֻ�ṩ�ӿڡ�

//���麯������дʵ��
//һ��������д��麯�������ǳ����࣬����ʵ������
//����̳и���Ĵ��麯����ֻҪ��һ�����麯����ʵ�֣�����Ȼ�ǳ����࣬����ʵ������

//interface
class IPerson {
public:
    virtual void Speak() = NULL; //���麯��

    //int m_n;
};

//void CPerson::Speak() {
//    printf("CPerson::Speak(�˻�)\r\n");
//}

class CChinese : public IPerson {
public:
    virtual void Speak() {
        printf("CChinese::Speak(����)\r\n");
    }

};

int main()
{
    CChinese chs;
    chs.Speak();

    //CPerson per;
    //per.Speak();


    return 0;
}

