// TestInherit.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <iostream>

//������󣺼̳�
//

//ѧ�� ��ʦ ְ��
//���ࣺ���ӣ��޸ģ�ɾ���鷳

class CPerson {
public:
    CPerson(int nGender){
        m_nGender = nGender;
        m_nPublic =   0xAAAAAAAA;
        m_protected = 0xBBBBBBBB;
        m_private =   0xDDDDDDDD;
    }

    int Gender() {
        return m_nGender;
    }

    void SetGender(int nGender) {
        m_nGender = nGender;
        //this->m_nTeaId = 2;
    }

public:
    //std::string m_strName; //����
    int m_nGender; //�Ա�
    int m_nPublic;
    int n;

protected:
    int m_protected;

private:
    int m_private;
};

//������Ĺ�ϵ:
//��Ϲ�ϵ��ѧ�����˵�����   (has-a) 
class CStudent {
public:
    CStudent(int StuId, int nGender) 
        :m_nStuId(StuId), m_per(nGender)
    {
    
    }

    void SetGender(int nGender) {
        m_per.SetGender(nGender);
    }



private:
    CPerson m_per;
    int m_nStuId;  //ѧ��
};

//�̳й�ϵ����ʦ��һ����    ��is-a��
//�������м̳У�
//  1.��Ա���ݣ��Ա�
//  2.��Ա������get ,set��
//�ƺ���
// CPerson ---> ����    /   ����
// CTeacher ---> ������ /   ����


// ����--�ˡ������� ����
// ��ͨ����--�ɻ���������
// ��--�������𳵣�Ħ�г������г�
// ����--���ǵϣ�ѩ�������µ�
// �µ�--A4,A8,A9
// Object  ����
// MFC --> CObject
// Qt  --> QObject

class CTeacher: public CPerson {
public:
    CTeacher(int TeaId, int nGender)
        :m_nTeaId(TeaId), CPerson(nGender)
    {
        m_nGender = 3;

        //m_nPublic = 1;
        //m_protected = 2;
        //m_private = 3;
    }

    void teach() {
        std::cout << "teach" << m_nTeaId << std::endl;
        CPerson::n = 3;
    }

private:
    int n;
    int m_nTeaId;  //����
};

//����Ȩ��
/*
������Ա��protected����������Ա��������������������⣬��������������ʹ�á�
�������Ȩ�����ڱ���ʱ�����ļ�飬ʵ������Ķ�����ڴ��а����������г�Ա��
        ���ࣨCPerson��   <--   ���м̳�public     --     ����(CTeacher)                        
���г�Ա��public��                                      ���г�Ա��public��
������Ա��protected��                                   ������Ա��protected��
˽�г�Ա��private��                                     ���ɼ�

                     ����   <--   �����̳�protected   --    ����                         
���г�Ա��public��                                       ������Ա��protected��
������Ա��protected��                                    ������Ա��protected��
˽�г�Ա��private��                                      ���ɼ�

                     ����   <--   ˽�м̳�private     --    ����                         
���г�Ա��public��                                       ���ɼ�
������Ա��protected��                                    ���ɼ�
˽�г�Ա��private��                                      ���ɼ�

*/

/*
    ���죬����˳��
    ���죺�ȸ��࣬������
    �����������࣬�ٸ���

    ���࣬���࣬������

*/

/*
    �������أ�
         

*/

int n = 1;
int main()
{
    int n = 2;
    //CStudent stu(1, 2);

    //stu.SetGender(1);
    //int nSize = sizeof(stu);

    CPerson* aryObj[2];

    CPerson per(1);
    //per.m_protected = 2;

    CTeacher tea(1, 2);
    //tea.m_nPublic = 1;
    //tea.m_protected = 2;

    aryObj[0] = &per;
    aryObj[1] = &tea;

    CTeacher* pTea = &tea;
    
    //����ת��������ת��������ָ�루���ã�ת��Ϊ����ָ�루���ã��� ��ȫ��
    CPerson* pPer = pTea;
    pPer->SetGender(1);

    //����ת��������ת��������ָ�루���ã�ת��Ϊ����ָ�루���ã��� ����ȫ��,���·���Խ��
    CTeacher* pTea2 = (CTeacher*)&per;

    pTea2->teach();

    //Ψһ�İ�ȫ�������
    CTeacher* pTea3 = (CTeacher*)pPer;
    pTea3->teach();


    tea.SetGender(1);
    int nSize = sizeof(tea);

    return 0;
}

