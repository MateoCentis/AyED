#include <iostream>
#include <list>
using namespace std;

//A) Usando insert
list<int> concatenar(list<int> &L1, list<int> &L2)
{
    list<int> L = L1;
    L.insert(L.end(), L2.begin(), L2.end());
    return L;
}

//B)Una lista LL de n sublistas usando insert
void concatenarN(list<list<int>> &LL, list<int> &L)
{
    L.clear();
    auto itB = LL.begin();
    while (itB != LL.end())
    {
        L.insert(L.end(), itB->begin(), itB->end());
        ++itB;
    }
}
//C)Una lista LL de n sublistas usando insert
void concatenarN_splice(list<list<int>> &LL, list<int> &L)
{
    L.clear();
    auto itB = LL.begin();
    auto it2 = itB;
    while (itB != LL.end())
    { //????
        L.splice(it2, itB)
    }
}

void printList(const list<int> &L)
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
    list<list<int>> LL = {{1, 3, 4, 5, 2, 3}, {5, 4, 2, 1, 5, 6}, {7, 8, 4, 2, 4, 5, 8}};
    list<int> L;
    concatenarN(LL, L);
    printList(L);
}