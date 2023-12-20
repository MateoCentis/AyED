#include <iostream>
#include "include/tree.hpp"
#include "include/lisp.hpp"
#include "include/make_random.hpp"
#include "include/graphviz.hpp"
#include "include/str_convs.hpp"

using namespace std;
using namespace aed;

typedef map<int,list<int>> Graph;

template<typename T>
void show_list(const list<T> &L){
    cout << "[ ";
    for_each(L.begin(),L.end(),[](T v){cout << v << " ";});
    cout << "] \n";
}





int main()
{

    Graph GL = {{1,{2,3,4,5}},
                             {2,{1,25}},
                             {3,{1,6,7}},
                             {4,{1,8}},
                             {5,{1,9,13}},
                             {6,{3}},
                             {7,{3,21,25}},
                             {8,{4,30}},
                             {9,{5,21}},
                             {13,{5,30}},
                             {21,{7,9}},
                             {25,{2,7}},
                             {30,{8,13}}};
    aed::graph2dot(GL,"Grafo");

    return 0;
}
