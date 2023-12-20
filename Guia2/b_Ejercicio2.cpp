#include <iostream>
#include <list>
#include <queue>
#include <stack>
using namespace std;

/*Inverso. Escribir un procedimiento bool inverso(list<char>&z) para determinar si una cadena
de caracteres de entrada es de la forma z=xy donde y es la cadena inversa (o espejo) de la cadena
x, ignorando los espacios en blanco. Emplear una cola y una pila auxiliares. */

bool inverso(list<char> &z)
{
    list<char>::iterator it = z.begin();
    stack<char> s;
    queue<char> q;
    while (it != z.end())
    {
        if (*it != ' ')
        {
            s.push(*it);
            q.push(*it);
        }
        ++it;
    }
    while (!s.empty())
    {
        if (s.top() != q.front())
        {
            return false;
        }
        s.pop();
        q.pop();
    }
    return true;
}

void show_list(list<int> L)
{
    cout << "(";
    for (auto i : L)
    {
        cout << i << " ";
    }
    cout << ")" << endl;
}

int main()
{
    list<char> L = {'t', 'a', 'n', ' ', 'a', 'n', ' ', 'a', 't'};
    if (inverso(L) == true)
    {
        cout << "Es";
    }
    else
    {
        cout << "No es";
    }
}