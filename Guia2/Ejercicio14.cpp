#include <iostream>
#include <list>
using namespace std;

/*14) Merge. Escribir una funci´on void merge(list<int> &L1, list<int> &L2, list<int>& L) la
cual recibe dos listas ordenadas (que pueden ser de distinto tamaño) de forma ascendente L1 y L2
y retorna una lista L, pasada como parámetro, con los elementos de ambas ordenados también en
forma ascendente. Por ejemplo si L1=[1, 3, 6, 11] y L2=[2, 4, 6, 10], la lista L debe quedar
como L=[1, 2, 3, 4, 6, 6, 10, 11].*/

void merge(list<int> &L1, list<int> &L2, list<int> &L)
{
    list<int>::iterator it1 = L1.begin();
    list<int>::iterator it2 = L2.begin();
    while (it1 != L1.end() or it2 != L2.end()) //Nos guardamos las listas
    {
        if (it1 != L1.end())
            L.push_back(*it1);
        if (it2 != L2.end())
            L.push_back(*it2);
        ++it1;
        ++it2;
    }
    //Sólo hay que hacer un sort ahora
    list<int>::iterator it = L.begin();
    list<int>::iterator itt;
    while (it != L.end())
    {
        itt = it;
        ++itt;
        for (; itt != L.end(); ++itt)
        {
            if (*it > *itt)
            {
                swap(*it, *itt);
            }
        }
        ++it;
    }
}

void PrintL(list<int> &L)
{
    cout << "[ ";
    for (auto it = L.begin(); it != L.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << "]";
}

int main()
{
    list<int> L1 = {1, 3, 6, 11};
    list<int> L2 = {2, 4, 6, 10};
    list<int> L;
    cout << "test" << endl;
    merge(L1, L2, L);
    PrintL(L);
}