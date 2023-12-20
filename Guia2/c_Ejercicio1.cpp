#include <iostream>
#include <map>
#include <list>
using namespace std;

void map2list(map<int, int> &M, list<int> &keys, list<int> &vals)
{
    map<int, int>::iterator it = M.begin();
    while (it != M.end())
    {
        keys.push_back(it->first);
        vals.push_back(it->second);
        ++it;
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
    map<int, int> M = {{1, 2}, {3, 5}, {8, 20}};
    list<int> k;
    list<int> v;
    //M={1->2,3->5,8->20}
    //M.insert(1, 2);
    //M.insert(3,5);
    //M.insert(8,20);
    map2list(M, k, v);
    print_map(M);
    PrintList(k);
    PrintList(v);
}