// $Id$

/* COMIENZO DE DESCRIPCION 

   __USE_WIKI__
   Dado una serie de conjuntos de enteros #S_j#, con #j# en #[0,N_S)#
   y otro conjunto #W# encontrar aquel #S_k# cuya interseccion con
   #W# tiene el maximo tamano.
   [Tomado en el TPL3 2013-11-09].
   keywords: conjunto

   FIN DE DESCRIPCION */
#include <cstdio>

#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <algorithm>
#include "./util.h"

using namespace std ;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#define STERM -1
#define TERM -2
int velem[]={1,3,5,STERM,
             0,2,4,8, STERM,
             0,1,4,9,STERM,
             5,10,STERM,
             1,3,6,STERM,TERM};
             
typedef list< set<int> > ls_t;
typedef vector< set<int> > vs_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void printvs(vs_t &ls) {
  vs_t::iterator q = ls.begin();
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
set<int> maxshare(vs_t &S,set<int> &W) {
  set<int> Smax;
  int nmax = 0;
  int NS = S.size();
  for (int j=0; j<NS; j++) {
    set<int> tmp;
    set_intersection(S[j],W,tmp);
    if (tmp.size()>nmax) {
      Smax = S[j];
      nmax = tmp.size();
    }
  }
  return Smax;
}

//--------------------------------------------------------------------
int main() {
  vs_t S;
  set<int> W;
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
  W = S[0];
  S.erase(S.begin());
  printvs(S);
  prints(W);
  set<int> Smax = maxshare(S,W);
  prints(Smax);
  return 0;
}
