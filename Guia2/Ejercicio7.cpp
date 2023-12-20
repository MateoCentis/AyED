#include <iostream>
#include <list>
using namespace std;

//E7) Ascendente1. Escribir una funci´on void  ascendente1(list<int> &L, list<list<int>> &LL)
//que, dada una lista L, genera una lista de listas LL de tal forma de que cada sublista es ascendente.

void ascendente1(list<int> &L, list<list<int>> &LL)
{
    LL.clear();
    auto itB = L.begin();
    auto itB2 = itB;
    advance(itB2, 1);
    list<int> aux;
    aux.push_back(*itB);
    for (; itB2 != L.end(); ++itB2)
    {
        if (*itB2 > *itB)
        {
            aux.push_back(*itB2);
        }
        else
        {
            LL.push_back(aux);
            aux.clear();
            aux.push_back(*itB2);
        }
        ++itB;
    }
    LL.push_back(aux);
}
//L = {3, 5, 3, 2, 1, 5, 6, 4, 2, 3, 4, 5, 6, 1, 3, 4, 5, -2, -4, -3, -10};
void PrintLL(list<list<int>> &LL)
{
    int cont = 1;
    for (auto it = LL.begin(); it != LL.end(); ++it)
    {
        cout << "Sublista " << cont << ": ";
        auto itB = it->begin();
        cout << "[ ";
        for (; itB != it->end(); ++itB)
        {
            cout << *itB << " ";
        }
        cout << "]" << endl;
        ++cont;
    }
}

int main()
{
    list<int> L = {3, 5, 3, 2, 1, 5, 6, 4, 2, 3, 4, 5, 6, 1, 3, 4, 5, -2, -4, -3, -10, 2, -3};
    list<list<int>> LL = {{3, 4, 5, 6}, {-1, 2, -3, -4}, {-5, -3, 2, 2}};
    ascendente1(L, LL);
    PrintLL(LL);
}
