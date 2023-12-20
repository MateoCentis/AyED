#include <iostream>
#include <list>
#include <map>
using namespace std;
typedef map<int, list<int>> Graph;
/*8) CompConexa. Dado un grafo G encontrar los subconjuntos del mismo
list<list<int>> D que est´an desconectados, es decir, los conjuntos de v´ertices de cada una de las
componentes conexas. Por ejemplo, si G={1->{2},2->{1},3->{4},4->{3}}, entonces debe
retornar D=({1,2},{3,4})*/

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

void comp_conexas(Graph &G, list<list<int>> &D)
{
    Graph::iterator it = G.begin();
    auto itD = D.begin();
    
    while (it != G.end())
    {
        it->second.swap(*itD);
        itD->push_front(it->first);
        ++itD;
        ++it;
    }
    //Ahora hacemos sort
    itD = D.begin();
    while (itD != D.end())
    {
        itD->sort();
        ++itD;
    }
    D.unique();
}
//Por ejemplo, si G={1->{2},2->{1},3->{4},4->{3}}, entonces debe retornar D=({1,2},{3,4})
int main()
{
    list<list<int>> D;
    Graph G;
    G[1] = {2};
    G[2] = {1};
    G[3] = {4};
    G[4] = {3};
    comp_conexas(G, D);
    auto it = D.begin();
    while (it != D.end())
    {
        PrintList(*it);
        cout << endl;
        ++it;
    }
}