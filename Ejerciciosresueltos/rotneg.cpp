#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <queue>

using namespace aed;
using namespace std;

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dada una cola #Q,# escribir una funcion 
   #void rotneg(queue<int> &Q);# 
   que rota los elementos (es decir extraer del frente e
   insertar en la cola) de tal forma que el elemento que quede
   en el frente debe ser negativo. Por ejemplo si
   #Q=(1,2,3,-2,7,8,9)# entonces debe quedar #Q=(-2,7,8,9,1,2,3).#

   *Nota:* Esta garantizado que al menos hay un numero negativo en la cola

   [Tomado en el Trabajo Practico de Laboratorio 1
   (TPL1) de 2020-09-24]
   keywords: cola

FIN DE DESCRIPCION */

void rotneg(queue <int> & Q) {
  while (Q.front()>=0) {
    int x = Q.front();
    Q.pop();
    Q.push(x);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  ev.eval<1>(rotneg,vrbs);
  return 0;
}
