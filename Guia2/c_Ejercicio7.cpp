#include <iostream>
#include <map>
#include <list>
using namespace std;
typedef map<int, list<int>> Graph;
/*Camino. Implemente la funci´on bool es_camino(map<int,list<int>> G, list<int> &L) que
recibe una lista L y determina si es o no camino en el grafo G. El grafo se representa como un
mapa que relaciona cada v´ertice (clave) con la lista de sus v´ertices adyacentes (valor).*/
/*
bool es_camino(Graph &G, list<int> &L)
{
    if (L.empty())
        return false;

    list<int>::iterator itL1 = L.begin();
    list<int>::iterator itL2;
    ++itL2;
    if (L.size() == 1)
    {
        Graph::iterator it = G.find(*itL1);
        return (it != G.end());
    }
    while (itL2 != L.end())
    {
        Graph::iterator it = G.find(*itL1);
        if (it == G.end())
            return false;
        list<int>::iterator itTmp = it->second.begin();
        while (itTmp != it->second.end())
        {
            if (*itTmp == *itL2)
                break;
            ++itTmp;
        }
        if (itTmp == it->second.end())
            return false;
        ++itL1;
        ++itL2;
    }
    return true;
}


typedef map<int,list<int>> Graph;
*/
bool es_camino(Graph &G, list<int> &L)
{
    if (L.empty())
        return false;
    list<int>::iterator itL1 = L.begin();
    list<int>::iterator itL2;
    if (L.size() == 1)
    {
        Graph::iterator it = G.find(*itL1);
        return (it != G.end());
    }
    while (itL2 != L.end())
    {
        Graph::iterator itG = G.find(*itL1);
        list<int>::iterator itTmp = itG->second.begin();
        while (itTmp != itG->second.end())
        {
            if (*itTmp == *itL2)
                break;
            ++itTmp;
        }
        if (itTmp == itG->second.end())
            return false;
        ++itL1;
        ++itL2;
    }
    return true;
}

int main()
{
    Graph G;
}