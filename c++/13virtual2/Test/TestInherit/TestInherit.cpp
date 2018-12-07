// TestInherit.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <ctime>

//������󣺶�̬-�麯��
//��������
// 1. ͬ������
// 2. ͬ��
// 3. �����б�ͬ������ֵ�͵���Լ��������

//��������
// 1. ������ͬ
// 2. ͬ��
// 3. �����б�����ֵ�͵���Լ��������

//�������� --- ָ�ľ��������
// ���ʣ� ������д������麯���������е�����Ӧ��λ�ûᱻ����Ķ�Ӧ���麯������
// ��д���壺
//     ����������ȫ��ͬ���������������б�����ֵ������Լ����
//     virtual�ؼ��ֿ�д�ɲ�д��������ϣ����Ӵ���ɶ���
// λ�ú��壺
//     1. �������麯��������˳��������������麯����˳��
//     2. �����������麯���Ḹ�ඨ����麯���ĺ���
// ���ǣ�
//     �����麯���������Ӧλ�õ��麯���滻�ˡ�

// 1. ������ͬ
// 2. ����������ȫ��ͬ
// 3. ���ٸ�������virtual�ؼ��֡�

//����ã�
// 1. �����������麯����virtual��
// �����ⲿ����������ָ��������ã�����Ǽ�ӵ���
// �����ڲ�����ĳ�Ա������)��������ֱ�ӷ�����ֱ�ӵ��ã���thisָ���Ǽ�ӵ���
// ����Ĺ���������е����麯�������̬��
//  ��1�������麯������ֱ�ӵ���
//   (2) ���õ��ǳ�Ա������ͨ����Ա�������麯����Ȼû�ж�̬��
//         ����&����ʱ��������ָ���Ϊ�Լ�������ָ�롣

//��������ԭ��
// delete �����ָ��ʱ�������ж�̬���ܹ����õ�����������������

class CPerson {
public:
    CPerson() {
        m_nType = 0;
        Test();
    }

    virtual ~CPerson() {
        printf("~CPerson()");
        Test();
    }

    //�麯��
    virtual void Speak() {
        printf("CPerson::Speak(�˻�)\r\n");
    }

    virtual void Eat() {
        printf("CPerson::Eat(����)\r\n");
    }

    virtual void Test() {
        this->Speak();
    }
    
    int m_nType;
};

class CChinese : public CPerson{
public:
    //R"("123")" ԭʼ�ַ���

    CChinese() {
        m_nType = 1;
        Test();
    }

    virtual ~CChinese() {
        printf("~CChinese()");
        Test();
    }


    virtual void Eat() {
        printf("CChinese::Eat(�в�)\r\n");
    }

    virtual void Speak() {
        printf("CChinese::Speak(\"����\")\r\n");
    }

};


int main()
{
    CPerson* pPer = new CChinese();

    pPer->Test();

    delete pPer;

    //chs.Test();


   
   

    return 0;
}

