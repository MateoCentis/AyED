#include <iostream>
#include <list>
using namespace std;

/*13) maxSubList. Programar una funci´on list<int> max_sublist(list<int> &L) la cual reciba una
lista de enteros y encuentre y retorne la sublista Lmax que obtenga la mayor suma entre todos sus
elementos. Notar que debido a que algunos elementos pueden ser negativos el problema no se
resuelve simplemente tomando todos los elementos. Tambi´en es posible que la sublista resultado
no contenga ning´un elemento, en el caso de que todos los elementos de L sean negativos. Si hay
varias sublistas que den la misma suma, debe retornar la que comience primero y sea m´as corta.
Por ejemplo: [1,2,-5,4,-3,2]->[4], [5,-3,-5,1,7,-2]->[1,7], [4,-3,11,-2]->[4,-3,11]. */

int SumaLista(list<int> &L)
{
    if (L.empty())
        return 0;
    list<int>::iterator it = L.begin();
    int suma = 0;
    while (it != L.end())
    {
        suma += *it;
        ++it;
    }
    return suma;
}

list<int> max_sublist(list<int> &L)
{
    list<int> Lmax;
    list<int>::iterator it = L.begin();
    list<int>::iterator it2;
    list<int> aux;
    while (it != L.end())
    {
        aux.push_back(*it);
        it2 = it;
        ++it2;
        if (SumaLista(aux) > SumaLista(Lmax))
        {
            Lmax = aux;
        }
        for (; it2 != L.end(); ++it2)
        {
            aux.push_back(*it2);
            if (SumaLista(aux) > SumaLista(Lmax))
            {
                Lmax = aux;
            }
        }
        aux.clear();
        ++it;
    }
    return Lmax;
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
    list<int> L = {4, -3, 11, -2};
    cout << "test" << endl;
    list<int> max = max_sublist(L);
    PrintL(max);
}