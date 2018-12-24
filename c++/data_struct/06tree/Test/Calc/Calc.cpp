// Calc.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stack>
#include <string>


//���������ȼ���ϵ

const char SymbolAry[] = {
    '+','-','*','/','(',')','#'
};


const char aryPriority[][7] =     
{
    { '>','>','<','<','<','>','>' },
    { '>','>','<','<','<','>','>' },
    { '>','>','>','>','<','>','>' },
    { '>','>','>','>','<','>','>' },
    { '<','<','<','<','<','=','0' },
    { '>','>','>','>','0','>','>' },
    { '<','<','<','<','<','0','=' },
};

int GetIndex(char ch) {
    for (int i = 0; i < sizeof(SymbolAry) / sizeof(char); i++) {
        if (ch == SymbolAry[i]) {
            return i;
        }
    }

    return -1;
}

bool IsNumber(char ch) {
    return (ch >= '0' && ch <= '9');
}



char GetPriority(char lOper, char rOper) {
    int nIndex1 = GetIndex(lOper);
    int nIndex2 = GetIndex(rOper);

    if (nIndex1 != -1 && nIndex2 != -1) {
        return aryPriority[nIndex1][nIndex2];
    }

    return '?';
}

int GetResult(int lNum, int rNum, char chSymbol) {

    switch (chSymbol)
    {
    case '+': {
        return lNum + rNum;
    }
              break;
    case '-': {
        return lNum - rNum;
    }
              break;
    case '*': {
        return lNum * rNum;
    }
              break;
    case '/': {
        return lNum / rNum;
    }
              break;

    default:
        break;
    }

    return 0;
}

bool CalcOnce(std::stack<int>&  numStk, std::stack<char>& chStk) {
    if (numStk.size() < 2 || chStk.size() < 1) {
        return false;
    }
    
    //��ʾ����ջ��Ҫ����һ��ջ�����ţ�
    //����ջ���������֣�Ȼ��ʼ������
    char curSymbol = chStk.top();
    chStk.pop();

    //�Ҳ�����
    int rNum = numStk.top();
    numStk.pop();

    //�������
    int lNum = numStk.top();
    numStk.pop();

    //��ʼ����
    int nResult = GetResult(lNum, rNum, curSymbol);
    numStk.push(nResult);

    return true;
}

//4+((7-5))*2
int calc(std::string calcStr) {

   
    std::stack<int>  numStk; //����ջ
    std::stack<char> chStk;  //����ջ

    std::string strNum = "";

    for (size_t i = 0; i < calcStr.length(); i++){
        char ch = calcStr[i];
        if (IsNumber(ch)) {
            strNum += ch;
            continue;
        }

        if (!strNum.empty()) {
            //˵������������
            int n = atoi(strNum.c_str());
            strNum = "";
            //��ʱ�ð�����ѹ�뵽����ջ��
            numStk.push(n);
        }

        //ch ��ʾ�Ƿ���
        if (chStk.empty()) {
            chStk.push(ch);
            continue;
        }
        else {
            //��ʾ����ջ���Ѿ������˷���
            //��ʼ�ȽϷ��ŵ����ȼ�
            while (!chStk.empty() ) {
                switch (GetPriority(chStk.top(), ch))
                {
                case '>':
                {
                    CalcOnce(numStk, chStk);
                }
                break;

                case '<':
                {
                    chStk.push(ch);    
                    goto Exit;
                }
                break;

                case '=':
                {
                    chStk.pop();
                    goto Exit;
                }
                break;

                default:
                {
                    //�����ʾ������
                    printf("input error\r\n");
                    return 0;
                }
                break;
                }

               
            }
           
            chStk.push(ch);
        Exit:
            ;
        }

    }

    //������˵�����ʽ�Ѿ�����ջ�ˣ�
    //���ܷ���ջ���Դ��ڷ���
    //˵������������
    if (!strNum.empty()) {
        int n = atoi(strNum.c_str());
        strNum = "";
        //��ʱ�ð�����ѹ�뵽����ջ��
        numStk.push(n);
    }

    while (!chStk.empty()) {
        CalcOnce(numStk, chStk);
    }

    //������
    if (numStk.size() == 1) {
        return numStk.top();
    }

    //�������ʾ���յ�����ջ�ж��ˣ�����
    printf("input error");
    return 0;
}

int main()
{
    int n = calc("4+(999*3-(7-5))*2");


    printf("4+(999*3-(7-5))*2 = %d\r\n %d\r\n", n, 4+(999*3-(7-5))*2);

    return 0;
}

