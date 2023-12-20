#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <list>


/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   Dada una lista de enteros #L1# y dos iteradores #p, q# de la
   misma, escriba una funcion 
   #void extraer_rango(list<int> &L1, list<int>::iterator p,# 
   #list<int>::iterator q, list<int> &L2);# que extraiga el rango de #L1# 
   y lo deja en la lista #L2.# 
   Nota: ambos iteradores #p# y #q# pueden ser #end()# y
   no necesariamente #p# esta antes de #q.#

   [Tomado en el Trabajo Practico de Laboratorio 1
   (TPL1) de 2020-09-24]
   keywords: lista

   FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

int distancia(list<int> &L,list<int>::iterator p) {
  int j=0;
  auto z=L.begin();
  while (z!=p) {
    j++;
    z++;
  }
  return j;
}

void extraer_rango(list<int> &L1, list<int>::iterator p, list<int>::iterator q, list<int> &L2)  {
  int dp = distancia(L1,p);
  int dq = distancia(L1,q);
  if (dp<dq) {
    L2.insert(L2.begin(),p,q);
    L1.erase(p,q);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  ev.eval<1>(extraer_rango,vrbs);
  return 0;
}
