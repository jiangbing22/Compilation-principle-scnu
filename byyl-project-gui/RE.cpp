#include "RE.h"
void RE::rBracket() {
    int leftBracket = -1;
    string result = "";
    for (size_t i = 0; i < re.length(); i++) 
    {
        if (re[i] == '\\')
        {

            result += re[i]; 
            result += re[i + 1];
            i++; 
            continue;
        }
        else if (re[i] == '[') 
        {
            leftBracket = i;
        } 
        else if (re[i] == ']') 
        {
            if (leftBracket != -1) 
            {
                string subStr = re.substr(leftBracket + 1, i - leftBracket - 1); // 不包括'['和']'
                string newStr = "(";
                for (size_t j = 0; j < subStr.size(); j += 3) 
                {
                    for (char ch = subStr[j]; j + 2 < subStr.size() && ch <= subStr[j + 2]; ch++) 
                    {
                        newStr += ch;
                        newStr += '|';
                    }
                }
                if (!newStr.empty()) 
                {
                    // 去除最后一个多余的'|'
                    newStr.pop_back();
                    newStr += ')';
                    result += newStr;
                }
            }
            leftBracket = -1; // 重置，为下一次可能的'['做准备
        } 
        else
        {
            if (leftBracket==-1)
            {
                result += re[i];
            }
        }
    }
    if (!result.empty() && result.back() == '|')
    {
        result.pop_back();
    }
    re = result;
}

void RE::addConcat()
{
    string result = "";
    for (size_t i = 0; i < re.length()-1; i++) {
        result += re[i];
        if (re[i]=='\\')//如果re[i]是转义字符
        {
            i++;
            if (i < re.length() - 1)
            {
                result += re[i];
                if (calculator.find(re[i + 1]) == calculator.end() || re[i + 1] == '(' || re[i + 1] == '\\')
                {
                    result += '&';
                    
                }

            }
        }
        else if(calculator.find(re[i])!=calculator.end())//如果re[i]是运算符
        {
            if(re[i]==')'||re[i]=='*'||re[i]=='+')
            {
                if(calculator.find(re[i+1])==calculator.end()||re[i+1]=='('||re[i+1]=='\\')
                {
                    result += "&";
                }

            }
         
        }
        else//如果re[i]不是运算符
        {
            if(calculator.find(re[i+1])==calculator.end()||re[i+1]=='(' || re[i + 1] == '\\')
            {
                result += "&";
            }
        }

    }
    result += re.back();
    re = result;
}

void RE::toPost() {
    if (re.empty()) {
        re_post = "";
        return;
    }
    stack<char> operators;
    string postfix = "";
    string infix = re;
    for (auto p = infix.begin(); p != infix.end(); p++) {
        auto c = *p;

        if (c == '\\')
        {
            postfix += c;
            if (c != infix.back())
            {
                p++;
                postfix += *p;
            }
        }
        else if (calculator.find(c) == calculator.end())
        {
            postfix += c;
        }
        else if (c == '(') 
        {
            operators.push(c);
        }
        else if (c == ')') 
        {
            while (!operators.empty() && operators.top() != '(') 
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else 
        {
            while (!operators.empty() && prior[operators.top()] >= prior[c]) 
            {
                postfix += operators.top();
                operators.pop();
                
            }
            operators.push(c);
        }
    }
    while (!operators.empty()) 
    {
        postfix += operators.top();
        operators.pop();
    }
    re_post = postfix;
}

