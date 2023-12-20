#include <iostream>
#include <set>
#include <vector>
using namespace std;
/*Disjuntos. Escribir una funci´on predicado bool disjuntos(vector<set<T>>&v) que verifica si
todos los conjuntos Ai dentro del vector de conjuntos v son disjuntos de a pares, esto es: si
Ai != Aj entonces Ai Intersección Aj = φ vacío.
*/
void set_intersection(set<int> &A, set<int> &B, set<int> &C)
{
    set<int>::iterator itA = A.begin();
    set<int>::iterator itB = B.begin();
    while (itA != A.end() and itB != B.end())
    {
        if (*itA == *itB)
        {
            C.insert(*itA);
        }
        ++itA;
        ++itB;
    }
}
template <typename T>
bool disjuntos(vector<set<T>> &v)
{
    set<T> C;
    for (int i = 0; i < v.size(); ++i)
    {
        for (int j = 0; j < v.size(); ++j)
        {
            if (v[i] != v[j])
            {
                set_intersection(v[i], v[j], C);
            }
            else
                continue;
            if (!C.empty())
                return false;
        }
    }
    return true;
}
int main()
{
}