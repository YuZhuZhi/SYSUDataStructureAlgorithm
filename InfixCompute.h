#pragma once
#include <string>
#include <stack>

//这个类使用栈实现中缀表达式求值。
//ExpressEval(const std::string& infix)函数对普通数值表达式适用，例如"1+2+3"；
//ExpressEval(const std::string & infix, const int x)适用于包含代数x的表达式，例如"x*x+x/x"。

class InfixCompute
{
public:
    static double ExpressEval(const std::string& infix)
    {
        std::stack<char> OPTR; //存放操作符的栈
        std::stack<int> OPND; //存放操作数的栈
        for (int i = 0; i <= infix.size() - 1; i++) {
            if (infix[i] >= '1' && infix[i] <= '9') { //如果碰到数字
                int j = i + 1;
                while (infix[j] >= '0' && infix[j] <= '9') j++; //找到数字结束的后一位
                OPND.push(ToInt(infix, i, j - 1)); //压入数字
            }
            else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(' || infix[i] == ')') {
                //如果碰到运算符
                ISOPTR:
                if (!OPTR.empty()) { //如果运算符栈非空
                    if (Priority[Map(OPTR.top())][Map(infix[i])] == 1) { //且栈顶优先级高
                        int opnd1 = OPND.top();
                        OPND.pop(); //弹出第一操作数
                        int opnd2 = OPND.top();
                        OPND.pop(); //弹出第二操作数
                        OPND.push(Operate(opnd1, opnd2, OPTR.top())); //压入计算结果
                        OPTR.pop(); //弹出已计算运算符
                        goto ISOPTR;
                        OPTR.push(infix[i]); //压入当前运算符
                    }
                    else if (Priority[Map(OPTR.top())][Map(infix[i])] == 2) { //且优先级相同
                        OPTR.pop();
                    }
                    else if (Priority[Map(OPTR.top())][Map(infix[i])] == -1) return -1; //但不存在这种情况
                    else OPTR.push(infix[i]); //压入当前运算符
                }
                else OPTR.push(infix[i]); //压入当前运算符
            }
        }
        while (!OPTR.empty()) { //以上操作结束后OPTR依旧非空
            int opnd1 = OPND.top();
            OPND.pop(); //弹出第一操作数
            int opnd2 = OPND.top();
            OPND.pop(); //弹出第二操作数
            OPND.push(Operate(opnd1, opnd2, OPTR.top())); //压入计算结果
            OPTR.pop(); //弹出已计算运算符
        }
        return OPND.top(); //最后返回操作数栈顶(底)
    }
    static double ExpressEval(const std::string& infix, const int x)
    {
        std::stack<char> OPTR; //存放操作符的栈
        std::stack<int> OPND; //存放操作数的栈
        for (int i = 0; i <= infix.size() - 1; i++) {
            if (infix[i] == 'x') { //如果碰到x,直接将其对应值压入OPND
                OPND.push(x);
                continue;
            }
            else if (infix[i] >= '1' && infix[i] <= '9') { //如果碰到数字
                int j = i + 1;
                while (infix[j] >= '0' && infix[j] <= '9') j++; //找到数字结束的后一位
                OPND.push(ToInt(infix, i, j - 1)); //压入数字
            }
            else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(' || infix[i] == ')') {
                //如果碰到运算符
            ISOPTR:
                if (!OPTR.empty()) { //如果运算符栈非空
                    if (Priority[Map(OPTR.top())][Map(infix[i])] == 1) { //且栈顶优先级高
                        int opnd1 = OPND.top();
                        OPND.pop(); //弹出第一操作数
                        int opnd2 = OPND.top();
                        OPND.pop(); //弹出第二操作数
                        OPND.push(Operate(opnd1, opnd2, OPTR.top())); //压入计算结果
                        OPTR.pop(); //弹出已计算运算符
                        goto ISOPTR;
                        OPTR.push(infix[i]); //压入当前运算符
                    }
                    else if (Priority[Map(OPTR.top())][Map(infix[i])] == 2) { //且优先级相同
                        OPTR.pop();
                    }
                    else if (Priority[Map(OPTR.top())][Map(infix[i])] == -1) return -1; //但不存在这种情况
                    else OPTR.push(infix[i]); //压入当前运算符
                }
                else OPTR.push(infix[i]); //压入当前运算符
            }
        }
        while (!OPTR.empty()) { //以上操作结束后OPTR依旧非空
            int opnd1 = OPND.top();
            OPND.pop(); //弹出第一操作数
            int opnd2 = OPND.top();
            OPND.pop(); //弹出第二操作数
            OPND.push(Operate(opnd1, opnd2, OPTR.top())); //压入计算结果
            OPTR.pop(); //弹出已计算运算符
        }
        return OPND.top(); //最后返回操作数栈顶(底)
    }

private:
    static constexpr int Priority[6][6] = { { 1, 1, 0, 0, 0, 1 }, { 1, 1, 0, 0, 0, 1 },
{ 1, 1, 1, 1, 0, 1 }, { 1, 1, 1, 1, 0, 1 }, { 0, 0, 0, 0, 0, 2 }, { 1, 1, 1, 1, -1, 1 } };//+-*/()运算符优先级表
    static int Map(const char optr)
    { //为了使用优先级表，创建一个运算符对应坐标的映射
        switch (optr)
        {
        case '+':
            return 0;
            break;
        case '-':
            return 1;
            break;
        case '*':
            return 2;
            break;
        case '/':
            return 3;
            break;
        case '(':
            return 4;
            break;
        case ')':
            return 5;
            break;
        default:
            break;
        }
    }
    static double Operate(const int opnd1, const int opnd2, const char optr)
    { //在弹出两个操作数之后，对应需要做的运算
        switch (optr)
        {
        case '+':
            return (opnd2 + opnd1);
            break;
        case '-':
            return (opnd2 - opnd1);
            break;
        case '*':
            return (opnd2 * opnd1);
            break;
        case '/':
            return (opnd2 / (double)opnd1);
            break;
        default:
            break;
        }
    }
    static int ToInt(const std::string str, const int start, const int end)
    { //如果在中缀表达式中包含二位数以上的数，此函数将其转换为int型
        int result = 0;
        for (int i = end - start; i >= 0; i--) {
            result = result + (int)(str[end - i] - '0') * pow(10, i);
        }
        return result;
    }

};