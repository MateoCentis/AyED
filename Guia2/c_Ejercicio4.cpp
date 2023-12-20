#include <iostream>
#include <map>
#include <list>
using namespace std;

//x = {x1,x2,x3,...,xn} claves de A
//y = {y1,y2,y3,...,yk} claves de B
//w = {x1,x2,x3,...,xn} U {y1,y2,y3,...,yk} claves de C
// si x2 == y3 merge(A[x2],B[x2]);
void merge(list<int> &L1, list<int> &L2, list<int> &L3); //Sacar de list

void merge_map(map<int, list<int>> &A, map<int, list<int>> &B, map<int, list<int>> &C)
{
    map<int, list<int>>::iterator itA = A.begin();
    map<int, list<int>>::iterator itB = B.begin();
    map<int, list<int>>::iterator it;
    list<int> L;
    while (itA != A.end() and itB != B.end())
    {
        if (itA != A.end())
        {
            it = B.find(itA->first);
            //Si las claves están en los dos
            if (it != B.end())
            {
                merge(itA->second, it->second, L);
                C[itA->first] = L;
            }
            else
            { //Sino están meto las de A
                C[itA->first] = itA->second;
            }
            ++itA;
        }
        //Acá meto las de B que no están en A
        if (itB != B.end())
        {
            it = A.find(itB->first);
            if (it == A.end())
            {
                C[itB->first] = itB->second;
            }
            ++itB;
        }
    }
}
int main()
{
}