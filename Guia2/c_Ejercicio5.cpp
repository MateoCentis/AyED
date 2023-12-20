#include <iostream>
#include <map>
#include <list>
using namespace std;

//Elimina todas las claves que no están en el rango [p,q)
/*En las asignaciones que quedan también debe eliminar los elementos de la lista que no estÁn en el rango. Si la lista queda 
vacía, entonces la asignación debe ser eliminada. Por ejemplo: si M = {1->(2,3,4), 5->(6,7,8), 8->(4,5), 3->(1,3,7)},
entonces cutoffmap(M,1,6) debe dejar M={1->(2,3,4), 3->(1,3)}.
Notar que la clave 5 ha sido eliminada si bien está dentro del rango porque su lista quedaría vacía.
Restricciones: No usar contenedores auxiliares.*/
bool SatisfaceRango(int p, int q, int x)
{
    if (x >= p and x < q)
        return true;
    else
        return false;
}

void cutoffmap(map<int, list<int>> &M, int p, int q)
{
    map<int, list<int>>::iterator it = M.begin();
    list<int>::iterator itL;
    while (it != M.end())
    {
        if (!SatisfaceRango(p, q, it->first))
        {
            it = M.erase(it);
        }
        else
        {
            itL = it->second.begin();
            while (itL != it->second.end())
            {
                if (!SatisfaceRango(p, q, *itL))
                {
                    itL = it->second.erase(itL);
                }
                ++itL;
            }
        }
        if (it->second.empty())
        {
            it = M.erase(it);
        }
        else
            ++it;
    }
}
//M = {1->(2,3,4), 5->(6,7,8), 8->(4,5), 3->(1,3,7)}
//cutoffmap(M,1,6) debe dejar M={1->(2,3,4), 3->(1,3)}
void ShowMap(map<int, list<int>> &M)
{
    auto it = M.begin();
    while (it != M.end())
    {
        cout << it->first << "-> (";
        auto itL = it->second.begin();
        while (itL != it->second.end())
        {
            cout << *itL << " ";
            ++itL;
        }
        cout << ")" << endl;
        ++it;
    }
}
int main()
{
    map<int, list<int>> M;
    M[1] = {2, 3, 4};
    M[5] = {6, 7, 8};
    M[8] = {4, 5};
    M[3] = {1, 3, 7};
    ShowMap(M);
    cutoffmap(M, 1, 6);
    cout << endl;
    ShowMap(M);
}