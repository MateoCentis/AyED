// $Id$

/* COMIENZO DE DESCRIPCION 

   __USE_WIKI__
   Dado una serie de conjuntos de enteros #S_j#, con #j# en #[0,N_S)#
   juntarlos entre si aquellos que tienen al menos un elemento en
   comun. 
   [Tomado en el TPL3 2013-11-09].
   keywords: conjunto

   FIN DE DESCRIPCION */
#include <cstdio>

#include <iostream>
#include <set>
#include <list>
#include <algorithm>
#include "./util.h"

using namespace std ;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#define STERM -1
#define TERM -2
int velem[]={5,7,11,STERM,0,1,3,STERM,1,2,10,STERM,7,13,22,STERM,TERM};

typedef list< set<int> > ls_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void printls(ls_t &ls) {
  ls_t::iterator q = ls.begin();
  int j=0;
  while (q!=ls.end()) {
    set<int> &S= *q++;
    printf("S[%d]= {",j++);
    set<int>::iterator s = S.begin();
    while (s!=S.end()) printf("%d ",*s++);
    printf("}\n");
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void prints(const set<int> &S,const char*label=NULL) {
  if (label) printf("%s={",label);
  printf("{");
  set<int>::iterator s = S.begin();
  while (s!=S.end()) printf("%d ",*s++);
  printf("}\n");
}

//--------------------------------------------------------------------
void gatherset(ls_t &S,ls_t &W) {
  W.clear();
  while (!S.empty()) {
    set<int> tmp = *S.begin();
    S.erase(S.begin());
    ls_t::iterator q = W.begin();
    while (q!=W.end()) {
      set<int> &w = *q, aux;
      set_intersection(tmp.begin(),tmp.end(),w.begin(),w.end(),
                       inserter(aux,aux.begin()));
      if (!aux.empty()) {
        tmp.insert(w.begin(),w.end());
        q = W.erase(q);
      } else q++;
    }
    W.push_back(tmp);
  }
}

//--------------------------------------------------------------------
int main() {
  ls_t S,W;
  int j=0,x;
  while (1) {
    set<int> tmp;
    while (1) {
      x = velem[j++];
      if (x==TERM) break;
      if (x==STERM) {
        S.push_back(tmp);
        break;
      }
      tmp.insert(x);
    }
    if (x==TERM) break;
  }
  printls(S);
  gatherset(S,W);
  printls(W);
  return 0;
}
