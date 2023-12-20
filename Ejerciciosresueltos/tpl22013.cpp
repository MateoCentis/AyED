/* COMIENZO DE DESCRIPCION 

   __USE_WIKI__
   Contiene count-level, odd2even, y is_shift. 
   [Tomado en el TPL2 2013-10-12].
   keywords: correspondencia, lista, arbol orientado

   FIN DE DESCRIPCION */

#include <cstdio>

#include "Evaluar.hpp"
#include "./tree.h"
#include "./util_tree.h"
#include "./util.h"

//--------------------------------------------------------------------
void odd2even(list<int> &L,map<int,list<int> > &M) {
  M.clear();
  // Avanza hasta el primer impar
  list<int>::iterator q = L.begin();
  while (q!=L.end() && *q%2==0) q++;
  while (q!=L.end()) {
    list<int> &L2 = M[*q++];
    while (q!=L.end() && *q%2==0) L2.push_back(*q++);
  }
}

//--------------------------------------------------------------------
typedef map<int, list<int> > graph_t;
bool is_shift(graph_t &G1,graph_t &G2,int m) {
  if (G1.size() != G2.size()) return false;
  graph_t::iterator q1 = G1.begin(), q2;
  while (q1!=G1.end()) {
    q2 = G2.find(q1->first+m);
    if (q2==G2.end()) return false;
    list<int>
      &L1 = q1->second,
      &L2 = q2->second;
    list<int>::iterator 
      p1 = L1.begin(),
      p2 = L2.begin();
    while (p1!=L1.end() && p2!=L2.end()) {
      if (*p2!=*p1+m) return false;
      p1++; p2++; 
    }
    q1++; 
  }
  return true;
}

typedef tree<int> tree_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int count_level(tree_t &T,tree_t::iterator n,int l) {
  if (n==T.end()) return 0;
  if (l==0) return 1;
  tree_t::iterator c = n.lchild();
  int m=0;
  while (c!=T.end()) m += count_level(T,c++,l-1);
  return m;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int count_level(tree_t &T,int l) {
  return count_level(T,T.begin(),l);
}

using namespace aed;
int main() {
  Evaluar ev;
  ev.evaluar1(count_level);
  ev.evaluar2(is_shift);
  ev.evaluar3(odd2even);
  return 0;
}
