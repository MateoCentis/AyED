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

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dada una pila #S,# escribir una funcion 
   #void acumula(stack<int> &S);# tal que deja en la posicion #j# de
   la pila la suma de los elementos desde #0# hasta #j#
   (inclusive) por ejemplo si #S = (1,3,2,4,2)# entonces debe
   quedar #S = (1,4,6,10,12)#.

   [Tomado en el Trabajo Practico de Laboratorio 1
   (TPL1) de 2020-09-24]
   keywords: pila

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

void acumula(stack<int>& S){
  int suma = 0;
  stack<int> Saux;
  while (!S.empty()) {
    int actual = S.top();
    suma = suma + actual;
    Saux.push(suma);
    S.pop();
		
  }
  for (int i = 0; i = Saux.size(); i++) {
    S.push(Saux.top());
    Saux.pop();
  }
	
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  ev.eval<1>(acumula,vrbs);
  return 0;
}
