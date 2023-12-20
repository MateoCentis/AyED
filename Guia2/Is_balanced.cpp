#include <iostream>
#include <stack>
using namespace std;

bool is_balanced(string &expr)
{
    stack<char> S;
    for (size_t i = 0; i < expr.size(); ++i)
    {
        char ch = expr[i];
        if (ch == '{' or ch == '[' or ch == '(')
        {
            S.push(ch);
        }
        else if (ch == '}' or ch == ']' or ch == ')')
        {
            if (S.empty())
                return false;
            char ch1 = S.top();
            switch (ch)
            {
            case '}':
                if (ch1 == '{')
                    S.pop();
                else
                    return false;
                break;
            case ']':
                if (ch1 == '[')
                    S.pop();
                else
                    return false;
                break;
            case ')':
                if (ch1 == '(')
                    S.pop();
                else
                    return false;
                break;
            }
        }
    }
    return S.empty();
}
int main()
{
    string s = "{[( )]}";
    if (is_balanced(s))
        cout << "Esta balanceado";
    else
        cout << "No lo está ";
}