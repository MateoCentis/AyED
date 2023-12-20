#include <iostream>
#include <list>
using namespace std;

//9) Camaleon. Implemente los predicados bool menor(int x, int y), bool mayor(int x, int y)
//y bool dist(int x, int y) que retornen verdadero si x es menor, mayor o menor en valor
//absoluto que y respectivamente. Luego implemente una funci´on
//ordena(list<int> &L, bool (*f)(int,int)) que ordene la lista L dependiendo de la funci´on
//f pasada c´omo par´ametro

bool menor(int x, int y)
{
    return x < y;
}

bool mayor(int x, int y)
{
    return x > y;
}

bool dist(int x, int y)
{
    return abs(x) < abs(y);
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

void ordena2(list<int> &L, bool (*f)(int, int))
{
    list<int>::iterator itB = L.begin();
    list<int>::iterator itE = L.end();
    --itE; //Se decrece ya que L.end() retorna un null
    for (; itB != itE; ++itB)
    {
        auto itt = itB;
        ++itt; //Un iterador que esté por delante de itB
        for (; itt != L.end(); ++itt)
        {
            if (f(*itt, *itB))
            {
                swap(*itt, *itB);
            }
        }
    }
}

int main()
{
    list<int> L = {4, 2, 3, 10, -1, -300, 3, 4};
    ordena2(L, menor);
    PrintL(L);
}