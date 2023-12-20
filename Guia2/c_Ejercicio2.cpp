#include <iostream>
#include <map>
#include <list>
using namespace std;

void list2map(map<int, int> &M, list<int> &Keys, list<int> &Vals)
{
    list<int>::iterator itK = Keys.begin();
    list<int>::iterator itV = Vals.begin();
    while (itK != Keys.end())
    {
        if (itV != Vals.end())
        {
            M[*itK] = *itV; //Reemplaza el valor de la lave itk
            ++itV;
        }
        else
        {
            M[*itK] = 0; //Pone una llave exista o no, un cero.
            //M.insert({*itK, 0});Pone un 0 sólo si Existe la llave
        }
        ++itK;
    }
}
void print_map(map<int, int> &M)
{
    map<int, int>::iterator it = M.begin();
    while (it != M.end())
    {
        cout << it->first << " -> " << it->second << endl;
        ++it;
    }
}

void PrintList(const list<int> &L)
{
    list<int>::const_iterator itB = L.cbegin();
    cout << "[ ";
    while (itB != L.end())
    {
        cout << *itB << " ";
        ++itB;
    }
    cout << "]" << endl;
}
int main()
{
    list<int> L1 = {1, 23, 3, 5, 6, 7, 34, 3, 3, 5, 7, 3};
    list<int> L2 = {1, 2, 3, 12, -21, 34, 3, 10, -7, 5, 3};
    map<int, int> M;
    list2map(M, L1, L2);
    print_map(M);
}