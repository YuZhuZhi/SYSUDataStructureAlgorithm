#pragma once
#include <string>
#include <stack>

//�����ʹ��ջʵ����׺���ʽ��ֵ��
//ExpressEval(const std::string& infix)��������ͨ��ֵ���ʽ���ã�����"1+2+3"��
//ExpressEval(const std::string & infix, const int x)�����ڰ�������x�ı��ʽ������"x*x+x/x"��

class InfixCompute
{
public:
    static double ExpressEval(const std::string& infix)
    {
        std::stack<char> OPTR; //��Ų�������ջ
        std::stack<int> OPND; //��Ų�������ջ
        for (int i = 0; i <= infix.size() - 1; i++) {
            if (infix[i] >= '1' && infix[i] <= '9') { //�����������
                int j = i + 1;
                while (infix[j] >= '0' && infix[j] <= '9') j++; //�ҵ����ֽ����ĺ�һλ
                OPND.push(ToInt(infix, i, j - 1)); //ѹ������
            }
            else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(' || infix[i] == ')') {
                //������������
                ISOPTR:
                if (!OPTR.empty()) { //��������ջ�ǿ�
                    if (Priority[Map(OPTR.top())][Map(infix[i])] == 1) { //��ջ�����ȼ���
                        int opnd1 = OPND.top();
                        OPND.pop(); //������һ������
                        int opnd2 = OPND.top();
                        OPND.pop(); //�����ڶ�������
                        OPND.push(Operate(opnd1, opnd2, OPTR.top())); //ѹ�������
                        OPTR.pop(); //�����Ѽ��������
                        goto ISOPTR;
                        OPTR.push(infix[i]); //ѹ�뵱ǰ�����
                    }
                    else if (Priority[Map(OPTR.top())][Map(infix[i])] == 2) { //�����ȼ���ͬ
                        OPTR.pop();
                    }
                    else if (Priority[Map(OPTR.top())][Map(infix[i])] == -1) return -1; //���������������
                    else OPTR.push(infix[i]); //ѹ�뵱ǰ�����
                }
                else OPTR.push(infix[i]); //ѹ�뵱ǰ�����
            }
        }
        while (!OPTR.empty()) { //���ϲ���������OPTR���ɷǿ�
            int opnd1 = OPND.top();
            OPND.pop(); //������һ������
            int opnd2 = OPND.top();
            OPND.pop(); //�����ڶ�������
            OPND.push(Operate(opnd1, opnd2, OPTR.top())); //ѹ�������
            OPTR.pop(); //�����Ѽ��������
        }
        return OPND.top(); //��󷵻ز�����ջ��(��)
    }
    static double ExpressEval(const std::string& infix, const int x)
    {
        std::stack<char> OPTR; //��Ų�������ջ
        std::stack<int> OPND; //��Ų�������ջ
        for (int i = 0; i <= infix.size() - 1; i++) {
            if (infix[i] == 'x') { //�������x,ֱ�ӽ����Ӧֵѹ��OPND
                OPND.push(x);
                continue;
            }
            else if (infix[i] >= '1' && infix[i] <= '9') { //�����������
                int j = i + 1;
                while (infix[j] >= '0' && infix[j] <= '9') j++; //�ҵ����ֽ����ĺ�һλ
                OPND.push(ToInt(infix, i, j - 1)); //ѹ������
            }
            else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(' || infix[i] == ')') {
                //������������
            ISOPTR:
                if (!OPTR.empty()) { //��������ջ�ǿ�
                    if (Priority[Map(OPTR.top())][Map(infix[i])] == 1) { //��ջ�����ȼ���
                        int opnd1 = OPND.top();
                        OPND.pop(); //������һ������
                        int opnd2 = OPND.top();
                        OPND.pop(); //�����ڶ�������
                        OPND.push(Operate(opnd1, opnd2, OPTR.top())); //ѹ�������
                        OPTR.pop(); //�����Ѽ��������
                        goto ISOPTR;
                        OPTR.push(infix[i]); //ѹ�뵱ǰ�����
                    }
                    else if (Priority[Map(OPTR.top())][Map(infix[i])] == 2) { //�����ȼ���ͬ
                        OPTR.pop();
                    }
                    else if (Priority[Map(OPTR.top())][Map(infix[i])] == -1) return -1; //���������������
                    else OPTR.push(infix[i]); //ѹ�뵱ǰ�����
                }
                else OPTR.push(infix[i]); //ѹ�뵱ǰ�����
            }
        }
        while (!OPTR.empty()) { //���ϲ���������OPTR���ɷǿ�
            int opnd1 = OPND.top();
            OPND.pop(); //������һ������
            int opnd2 = OPND.top();
            OPND.pop(); //�����ڶ�������
            OPND.push(Operate(opnd1, opnd2, OPTR.top())); //ѹ�������
            OPTR.pop(); //�����Ѽ��������
        }
        return OPND.top(); //��󷵻ز�����ջ��(��)
    }

private:
    static constexpr int Priority[6][6] = { { 1, 1, 0, 0, 0, 1 }, { 1, 1, 0, 0, 0, 1 },
{ 1, 1, 1, 1, 0, 1 }, { 1, 1, 1, 1, 0, 1 }, { 0, 0, 0, 0, 0, 2 }, { 1, 1, 1, 1, -1, 1 } };//+-*/()��������ȼ���
    static int Map(const char optr)
    { //Ϊ��ʹ�����ȼ�������һ���������Ӧ�����ӳ��
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
    { //�ڵ�������������֮�󣬶�Ӧ��Ҫ��������
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
    { //�������׺���ʽ�а�����λ�����ϵ������˺�������ת��Ϊint��
        int result = 0;
        for (int i = end - start; i >= 0; i--) {
            result = result + (int)(str[end - i] - '0') * pow(10, i);
        }
        return result;
    }

};