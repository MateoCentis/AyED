#include <iostream>
#include <list>
using namespace std;

void show_list(list<int> L)
{
    cout << "(";
    for (auto i : L)
    {
        cout << i << " ";
    }
    cout << ")" << endl;
}

void merge(list<int> &L1, list<int> &L2, list<int> &L)
{
    list<int>::iterator itL1 = L1.begin();
    list<int>::iterator itL2 = L2.begin();

    L.clear();

    while (itL1 != L1.end() && itL2 != L2.end())
    {
        if (*itL1 < *itL2)
        {
            L.push_back(*itL1);
            itL1++;
        }
        else
        {
            L.push_back(*itL2);
            itL2++;
        }
    }

    L.insert(L.end(), itL1, L1.end());
    L.insert(L.end(), itL2, L2.end());
}

/// Implementacion poco eficiente
void merge2(list<int> &L1, list<int> &L2, list<int> &L)
{
    list<int>::iterator it2 = L2.begin();
    L = L1;
    while (it2 != L2.end())
    {
        L.push_back(*it2);
        it2++;
    }
    L.sort();
}

/// -------------------------------------------------------------------------------

void mergesort(list<int> &L)
{
    if (L.size() <= 1)
    {
        return;
    }
    else
    {
        list<int> L1, L2;

        L1.swap(L);

        list<int>::iterator itL1 = L1.begin();
        for (int i = 0; i < L1.size() / 2; i++)
        {
            itL1++;
        }

        L2.splice(L2.begin(), L1, itL1, L1.end());

        mergesort(L1);
        mergesort(L2);
        merge(L1, L2, L);
    }
}

/// Implementacion eficiente (una sola recursion)
void mergesort2(list<int> &L)
{
    if (L.empty() || L.size() == 1)
        return;

    list<int> L1;
    L1.splice(L1.begin(), L, L.begin());
    list<int> L2;
    L2.splice(L2.begin(), L);
    mergesort2(L2);
    merge(L1, L2, L);
}

int main(int argc, char *argv[])
{
    list<int> L1 = {1, 3, 6, 11, 15};
    list<int> L2 = {2, 4, 6, 10};
    list<int> L;

    //merge(L1, L2, L);

    //show_list(L);

    cout << "mergesort" << endl;

    list<int> LL = {2, 4, 67, 3, 21, 7, 9, 0, 4, 2, 1, 4, 5, 8, 0, 3, 4};

    mergesort(LL);

    show_list(LL);

    cout << endl;

    list<int> LL2 = {2, 4, 67, 3, 21, 7, 9, 0, 4, 2, 1, 4, 5, 8, 0, 3, 4};

    cout << "mergesort2" << endl;

    mergesort2(LL2);

    show_list(LL2);

    return 0;
}