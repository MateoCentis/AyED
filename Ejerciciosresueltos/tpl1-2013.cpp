/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Escribir una funcion #void split_mod(list<int> &L, int m,#
   #vector<list<int> > &VL);# que dada una lista #L#, y un entero #m#
   divide a la lista en las sublistas de los elementos que son
   congruentes entre si modulo #m#. Es decir en #VL[j]# deben 
   quedar los elementos tales que #x%m==j#. 

   Escribir una funcion predicado #bool is_sublist(list<int> &L1,#
   #list<int> &L2);# que determina si #L2# es una sublista de #L1#
   es decir si #L2# se puede obtener de #L1# solo borrando elementos
   de L1. 

   Escribir una funcion #void max_sublist(list<int> &L,#
   #list<int> &subl);# que
   dada una lista #L# retorna la maxima sublista contigua de #L# con
   elementos pares #subl#. 

   [Tomado en el TPL1 de 2013-08-31].  
   keywords: lista

  FIN DE DESCRIPCION */
// -----------------------------------------------------------------

#include "Evaluar.hpp"
#include <cstdio>

void split_mod(list<int>&L, int m,
               vector< list<int> >&VL) {
  list<int>::iterator q = L.begin();
  VL.clear();
  VL.resize(m);
  while (q!=L.end()) {
    int r = *q % m;
    VL[r].push_back(*q++);
  }
}

bool is_sublist(list<int>&L1, list<int>&L2) {
  list<int>::iterator 
    q1 = L1.begin(),
    q2 = L2.begin();
  while (q1!=L2.end() && q2!=L2.end()) {
    if (*q1==*q2) q2++;
    else q1++;
  }
  return q2==L2.end();
}

void max_sublist(list<int>&L, list<int>&subl) {
  list<int> tmp;
  list<int>::iterator q = L.begin();
  subl.clear();
  while (q!=L.end()) {
    if (*q%2==0) {
      tmp.clear();
      while (q!=L.end() && *q%2==0) tmp.push_back(*q++);
      if (tmp.size()>subl.size()) subl = tmp;
    } else q++;
  }
}

void max_sublist2(list<int>&L, list<int>&subl) {
  // Esta version es mas eficiente. Solo guarda un
  // iterator al comienzo de la lista mas larga.
  // Despues cuando termina copia esa lista en subl
  list<int> tmp;
  list<int>::iterator 
    q = L.begin(), 
    qmin=q, r;
  int lmax = 0;
  subl.clear();
  while (q!=L.end()) {
    while (q!=L.end() && *q%2) q++;
    int l=0; r=q;
    while (q!=L.end() && *q%2==0) { l++; q++; }
    if (l>lmax) { lmax=l; qmin=r; }
  } 
  subl.clear();
  q=qmin;
  for (int j=0; j<lmax; j++) subl.push_back(*q++);
}

int main() {
  aed::Evaluar ev;
  ev.evaluar1(split_mod);
  ev.evaluar2(is_sublist);
  ev.evaluar3(max_sublist);
  return 0;
}
