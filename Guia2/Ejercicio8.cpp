#include <iostream>
#include <list>
#include <vector>
using namespace std;

//8) Ascendente2. Escribir una funci´on void ascendente2(list<int> &L, vector<list<int>> &VL)
// que, dada una lista L, genera un vector de listas VL de tal forma de que cada sublista es ascendente.

//Forma alternativa
void ascendente2(list<int> &L, vector<list<int>> &VL)
{
    VL.clear();
    auto itl = L.begin();
    list<int> aux;
    while (itl != L.end())
    {
        aux.push_back(*itl);
        auto itt = itl;
        itt++;
        while (itt != L.end() and (*itl < *itt))
        {
            aux.push_back(*itt);
            ++itl;
            ++itt;
        }
        VL.push_back(aux);
        aux.clear();
        ++itl;
    }
}

int main()
{
    list<int> L = {3, 5, 3, 2, 1, 5, 6, 4, 2, 3, 4, 5, 6, 1, 3, 4, 5, -2, -4, -3, -10, 2, -3};
    vector<list<int>> VL;
    ascendente2(L, VL);
}