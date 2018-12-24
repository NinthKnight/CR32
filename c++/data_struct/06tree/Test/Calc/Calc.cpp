// Calc.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stack>
#include <string>


//算符间的优先级关系

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
    
    //表示符号栈需要弹处一个栈顶符号，
    //数字栈弹两个数字，然后开始运算了
    char curSymbol = chStk.top();
    chStk.pop();

    //右操作数
    int rNum = numStk.top();
    numStk.pop();

    //左操作数
    int lNum = numStk.top();
    numStk.pop();

    //开始运算
    int nResult = GetResult(lNum, rNum, curSymbol);
    numStk.push(nResult);

    return true;
}

//4+((7-5))*2
int calc(std::string calcStr) {

   
    std::stack<int>  numStk; //数字栈
    std::stack<char> chStk;  //符号栈

    std::string strNum = "";

    for (size_t i = 0; i < calcStr.length(); i++){
        char ch = calcStr[i];
        if (IsNumber(ch)) {
            strNum += ch;
            continue;
        }

        if (!strNum.empty()) {
            //说明遇到符号了
            int n = atoi(strNum.c_str());
            strNum = "";
            //此时该把数字压入到数字栈中
            numStk.push(n);
        }

        //ch 表示是符号
        if (chStk.empty()) {
            chStk.push(ch);
            continue;
        }
        else {
            //表示符号栈中已经存在了符号
            //开始比较符号的优先级
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
                    //这里表示出错了
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

    //到这里说明表达式已经都入栈了，
    //可能符号栈中仍存在符号
    //说明遇到符号了
    if (!strNum.empty()) {
        int n = atoi(strNum.c_str());
        strNum = "";
        //此时该把数字压入到数字栈中
        numStk.push(n);
    }

    while (!chStk.empty()) {
        CalcOnce(numStk, chStk);
    }

    //到这里
    if (numStk.size() == 1) {
        return numStk.top();
    }

    //到这里，表示最终的数字栈中多了，出错
    printf("input error");
    return 0;
}

int main()
{
    int n = calc("4+(999*3-(7-5))*2");


    printf("4+(999*3-(7-5))*2 = %d\r\n %d\r\n", n, 4+(999*3-(7-5))*2);

    return 0;
}

