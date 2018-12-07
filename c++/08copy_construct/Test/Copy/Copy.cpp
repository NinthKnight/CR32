// Copy.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

//��������
// 1. ���ܣ���һ����������ݿ�������һ�����󣬱���Ҳ�ǹ��캯����
// 2. ϵͳ���ṩһ��Ĭ�ϵĿ������캯����Ĭ�Ϲ�����һ��ǳ������ֻ����ֵ��
//    ����ʹ��=delete����.
// 3. ǳ������CStuent stu2 = stu1�ȼ���memcpy��&stu2, &stu1, sizeof(stu1)����
// 4. ������Լ�ʵ�֣������Դ�������룬�Ӷ��������������ظ��ͷ���Դ�����⡣

// =������ĸ�ֵ
// 1. ϵͳ���ṩһ��Ĭ�ϵ�=������ĸ�ֵ�ĺ����� ��=�����������,Ҳ��ǳ������

//Ϊ�˱���ǳ������������Դ�ظ��ͷŵ����⣬��д���������=���������������أ����߽��á�

class CStudent {
public:
    CStudent(char* pName,int nGender = 1)
        :m_nGender(nGender)
    {     
        m_nName  = new char[strlen(pName) + 1];
        strcpy_s(m_nName, strlen(pName) + 1, pName);

        std::cout << "CStudent(int nGender)" << std::endl;
    }

    //��������
    //CStudent(CStudent& obj) = delete;
    CStudent(CStudent& obj) {

        std::cout << "CStudent(CStudent& obj)" << std::endl;

        m_nGender = obj.m_nGender;
        
        m_nName = new char[strlen(obj.m_nName) + 1];
        strcpy_s(m_nName, strlen(obj.m_nName) + 1, obj.m_nName);
    }

    //=���������
    CStudent& operator=(CStudent& obj) {
        std::cout << "CStudent& operator=(CStudent& obj)" << std::endl;

        if (m_nName == obj.m_nName) {
            return *this;
        }

        if (m_nName != NULL) {
            delete [] m_nName;
            m_nName = NULL;
        }

        m_nGender = obj.m_nGender;

        m_nName = new char[strlen(obj.m_nName) + 1];
        strcpy_s(m_nName, strlen(obj.m_nName) + 1, obj.m_nName);

        return *this;
    }


    ~CStudent()
    {
        std::cout << "~CStudent()" << std::endl;
        if (m_nName != NULL) {
            delete[] m_nName;
            m_nName = NULL;
        }
        
    }

private:
    int m_nGender;
    char* m_nName;
};



int main()
{
    char szName[] = "zhangsan";
    CStudent stu1(szName, 1);

    //CStudent stu1 = 1;
    CStudent stu2("1");
    stu2 = stu1;

   
    CStudent stu3 = stu2;
    CStudent stu4 = stu2;
    CStudent stu5 = stu2;
    CStudent stu6 = stu2;


    //int n = 1;
    //printf("n=%d\r\n",n = 2);


    return 0;
}

