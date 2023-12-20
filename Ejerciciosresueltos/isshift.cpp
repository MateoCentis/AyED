// $Id$

/* COMIENZO DE DESCRIPCION 

   __USE_WIKI__
   Dados dos grafos escribir una funcion
   #bool is_shift(graph_t &G1,graph_t &G2,int m);#
   que determina si #G2# es un `shift' de #G1#, es
   decir la arista #(x,y)# esta en #G1# si y solo si #(x+m,y+m)#
   esta en #G2#.
   [Tomado en el TPL2 2013-10-12].
   keywords: correspondencia

   FIN DE DESCRIPCION */
#include <cstdio>

#include <iostream>
#include <map>
#include <list>
#include "./util.h"

using namespace std ;


//--------------------------------------------------------------------
typedef map<int, list<int> > graph_t;
bool is_shift(graph_t &G1,graph_t &G2,int m) {
  if (G1.size()!=G2.size()) return false;
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

#if 0
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool is_shift(graph_t &G1,graph_t &G2,int m) {
  return is_shift1(G1,G2,m) && is_shift1(G2,G1,-m);
}
#endif

//--------------------------------------------------------------------
int main() {
  graph_t G1,G2;
  int m=3;
  for (int j=0; j<10; j++) {
    int v = 2*j;
    list<int> &L1 = G1[v];
    L1.push_back(j);
    L1.push_back(j+1);
    L1.push_back(j+2);

    list<int> &L2 = G2[v+m];
    L2.push_back(j+m);
    L2.push_back(j+1+m);
    L2.push_back(j+2+m);
  }
  printf("is_shift(G1,G2,%d) -> %d\n",m,is_shift(G1,G2,m));
  int m2=4;
  printf("is_shift(G1,G2,%d) -> %d\n",m2,is_shift(G1,G2,m2));
  return 0;
}
