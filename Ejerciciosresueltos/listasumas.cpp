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
   Dada una lista #L,# encuentre y retorne la sublista cuya
   suma sea #S.# Si no existe ninguna sublista con dicha suma,
   retorne la lista vacia. En caso de haber varias listas
   que cumplan retorne la primera y la mas corta. 

   [Tomado en el Trabajo Practico de Laboratorio 1
   (TPL1) de 2020-09-24]
   keywords: lista

   FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

list<int> listaSumaS(list<int>& L, int S){
  list<int> R;
  if(S==0) return R;
  list<int>::iterator it = L.begin();
  while(it!=L.end()){
    int acum = 0;
    auto it2 = it;
    while(it2!=L.end()){
      acum += *it2;
      if(acum==S){
        R.insert(R.begin(),it,++it2);
        return R;
      }
      it2++;
    }
    it++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  
  Eval ev;
  int vrbs = 0;
  ev.eval<1>(listaSumaS,vrbs);
  return 0;
}
