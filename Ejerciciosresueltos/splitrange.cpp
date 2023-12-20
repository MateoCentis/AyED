#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <numeric>

using namespace aed;
using namespace std;

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   Dada una lista de enteros #L# y dos enteros #k1,k2# (con
   #k1<=k2)# escribir una funcion 
   #void split_range(list<int>& L,#   
   #int k1,int k2,list<int>& L1,list<int>& L2,list<int>& L3);#
   que divide los elementos de #L# en 3 listas #L1,L2,L3# donde
   respectivamente deben quedar los elementos #x# en los rangos
   #x<k1,# #k1<=x<k2,# #x2<x.#

   [Tomado en el Trabajo Practico de Laboratorio 1
   (TPL1) de 2020-09-24]
   keywords: lista

FIN DE DESCRIPCION */

void split_range(list<int>& L, int k1,int k2,
                 list<int>& L1,list<int>& L2,list<int>& L3){
  L1.clear();
  L2.clear();
  L3.clear();
  auto q = L.begin();
  while (q!=L.end()) {
    int x = *q++;
    if (x < k1) L1.push_back(x);
    else if (x < k2) L2.push_back(x);
    else L3.push_back(x);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void split_range2(list<int>& L, int k1,int k2,
                  list<int>& L1,list<int>& L2,list<int>& L3){
  L1.clear();
  L2.clear();
  L3.clear();
  auto q = L.begin();
  while (q!=L.end()) {
    int x = *q++;
    // Usa solo una linea gracias al "hook" (?) operator
    (x<k1? L1 : x<k2? L2 : L3).push_back(x);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  ev.eval<1>(split_range,vrbs);
  return 0;
}
