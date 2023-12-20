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
   Dada una lista de enteros #L,# se pide que implemente un
   filtro de suavizado de ventana fija de tamano #w,# con las
   siguientes caracteristicas: El primer elemento sera el
   promedio (en division entera) de los primeros #w# elementos
   de #L,# El segundo sera el promedio desde el 2 elemento al
   #w+1# en general, el elemento en la posicion #N# de la lista
   resultado, sera el promedio entre los elementos #[N,w+N)#
   de #L.#

   [Tomado en el Trabajo Practico de Laboratorio 1
   (TPL1) de 2020-09-24]
   keywords: lista

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

list<int> smoothing (list<int>& L, int w){
  list<int> R;
  list<int>::iterator it = L.begin();
  list<int> Laux;
  for(;it!=L.end();it++){
    Laux.push_back(*it);
    if(Laux.size()==w){
      R.push_back(accumulate(Laux.begin(),Laux.end(),0)/w);
      Laux.pop_front();
    }
  }
  return R;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  ev.eval<1>(smoothing,vrbs);
  return 0;
}
