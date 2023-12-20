#define USECHRONO
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>
#include <numeric>
#include "eval.hpp"

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dada una lista de enteros 
   implemente una funcion 
   #void nearest_neighbor_1d(list<int> &L, int v);# 
   que ordene la lista de acuerdo a la distancia en valoe absoluto
   al valor de referencia #v# pasado como argumento.

   [Tomado en el Trabajo Practico de Laboratorio 1
   (TPL1) de 2020-09-24]
   keywords: lista

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> discrete_moving_mean (tpl 1)
void nearest_neighbor_1d(list<int> &L, int v){
  list<int> L2;
    
  while(!L.empty()){
    list<int>::iterator it = L.begin();
    list<int>::iterator itMin = it;
    while(it!=L.end()){
      if(abs(*it-v)<abs(*itMin-v)){
        itMin = it;
      }
      it++;
    }
    L2.push_back(*itMin);
    L.erase(itMin);
  }
  L = L2;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  
  Eval ev;
  int vrbs = 0;
  ev.eval<1>(nearest_neighbor_1d,vrbs);
  return 0;
}
