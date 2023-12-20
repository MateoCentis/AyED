#include <iostream>
#include <list>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------------------------------------
//DESCRIPCIÓN
// ReemplazaSecuencia. Dada una lista de enteros L y dos listas SEQ y REEMP, posiblemente de
//distintas longitudes, escribir una funci´on void reemplaza(list<int> &L, list<int>& SEQ,
//list<int> &REEMP), que busca todas las secuencias de SEQ en L y las reemplaza por REEMP. Por
//ejemplo, si L=(1,2,3,4,5,1,2,3,4,5,1,2,3,4,5), SEQ=(4,5,1) y REEMP=(9,7,3), entonces
//despu´es de llamar a reemplaza(L,SEQ,REEMP), debe quedar L=(1,2,3,9,7,3,2,3,9,7,3,2,3,4,5).
//Para implementar este algoritmo primero buscar desde el
//principio la secuencia SEQ, al encontrarla, reemplazar por REEMP, luego seguir buscando a partir
//del siguiente elemento al ´ultimo de REEMP.
//---------------------------------------------------------------------------------------------------------

void reemplaza(list<int> &L, list<int> &SEQ, list<int> &REEMP)
{
    auto itB = L.begin();
    list<int> Lpasar;
    auto itL = Lpasar.begin();
    list<int> aux;
    while (itB != L.end())
    {
        auto itaux = itB;
        for (auto it2 = SEQ.begin(); it2 != SEQ.end(); ++it2)
        {
            aux.push_back(*itB);
            ++itB;
            if (itB == L.end())
            {
                aux.push_back(*itB);
                break;
            }
        }
        if (aux == SEQ)
        {
            Lpasar.insert(itL, aux.begin(), aux.end());
            advance(itL, aux.size());
            aux.clear();
        }
    }
    swap(Lpasar, L);
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
    list<int> L = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    list<int> SEQ = {4, 5, 1};
    list<int> REEMP = {9, 7, 3};
    reemplaza(L, SEQ, REEMP);
    PrintL(L);
}