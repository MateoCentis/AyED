#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <queue>

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dada una cola #Q# de enteros de longitud par, escribir una
   funcion #void intercalarCola(queue<int>& Q),# que intercale
   los elementos de la primera mitad de la cola con los
   elementos de la segunda mitad.

   [Tomado en el Trabajo Practico de Laboratorio 1
   (TPL1) de 2020-09-24]
   keywords: cola

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

void intercalarCola(queue<int>& Q) {
  stack<int> Saux;
    
  int N = Q.size() / 2;
  for(int i=0; i<N; i++) {
    Saux.push(Q.front());
    Q.pop();
  }
    
  while(!Saux.empty()) {
    Q.push(Saux.top());
    Saux.pop();
  }
    
  for(int i=0; i<N; i++) {
    Q.push(Q.front());
    Q.pop();
  }
    
  for(int i=0; i<N; i++) {
    Saux.push(Q.front());
    Q.pop();
  }
    
  while(!Saux.empty()) {
    Q.push(Saux.top());
    Saux.pop();
    Q.push(Q.front());
    Q.pop();
  }
}
  
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  ev.eval<1>(intercalar_cola,vrbs);
  return 0;
}
