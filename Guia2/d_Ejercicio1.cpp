#include <iostream>
#include <set>
using namespace std;

template <typename T>
void show_set(const set<T> &S)
{
    cout << "[";
    for_each(S.begin(), S.end(), [](t v)){cout << v << " "};
    cout << "]" << endl;
}
//a) void set_union(set<T>&A,set<T>&B,set<T>&C);
void set_union(set<int> &A, set<int> &B, set<int> &C)
{
    C.insert(A.begin(), A.end());
    C.insert(B.begin(), B.end());
}
//b) void set_intersection(set<T>&A...)

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

//c) void set_difference(...), A - B = elementos que pertenecen a A y no a B
void set_difference(set<int> &A, set<int> &B, set<int> &C)
{
    set<int>::iterator itA = A.begin();
    while (itA != A.end())
    {
        if (B.find(*itA) == B.end())
        {
            C.insert(*itA);
        }
        ++itA;
    }
}

int main()
{
}