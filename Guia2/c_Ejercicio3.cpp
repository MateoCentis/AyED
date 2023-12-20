#include <iostream>
#include <map>
using namespace std;

bool areinverse(map<int, int> &M1, map<int, int> &M2)
{
    if (M1.size() != M2.size())
        return false;
    map<int, int>::iterator it1 = M1.begin();

    while (it1 != M1.end())
    {
        map<int, int>::iterator it = M2.find(it1->second);
        if (it == M2.end())
            return false;
        if (it->second != it1->first)
            return false;
        ++it1;
    }
    return true;
}
int main()
{
    map<int, int> M1 = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
    map<int, int> M2 = {{5, 4}, {4, 3}, {3, 2}, {2, 1}};
    cout << (areinverse(M1, M2) ? "true" : "false") << endl;
}