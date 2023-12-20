// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Igual a #cumsum.cpp# pero ahora para AB. 
   El #cumsum(v)# de un vector #v# es la suma acumulada, es
   decir en la posicion #v[j]# debe quedar la suma de los
   elementos de #v[0..j]#. Para un arbol lo podemos extender
   diciendo que en cada nodo del arbol queda la suma de los
   valores de los nodos de su subarbol ANTES de la
   operacion. 
   keywords: arbol binario

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------
#include <cstdarg>
#include <cstdio>

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "./util.h"
#include "./btree.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

typedef btree<int>::iterator node_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void cumsum_down(btree<int> &T,node_t p, int sum) {
  // sum es la suma acumulada hasta el padre de p
  if (p==T.end()) return;
  // actualiza el valor de p
  *p += sum;
  // propaga a los hijos
  cumsum_down(T,p.left(),*p);
  cumsum_down(T,p.right(),*p);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void cumsum_down(btree<int> &T) {
  cumsum_down(T,T.begin(),0);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void cumsum_up(btree<int> &T,node_t p) {
  if (p==T.end()) return;
  node_t l = p.left(), r = p.right();
  // aplica a los hijos
  cumsum_up(T,l);
  cumsum_up(T,r);
  // actualiza el valor de p
  if (l!=T.end()) *p += *l;
  if (r!=T.end()) *p += *r;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void cumsum_up(btree<int> &T) {
  cumsum_up(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  btree<int> T, Tcpy;

  for (int j=0; j<10; j++) {
    // genera un arbol aleatorio, guarda la copia en Tcpy
    T.clear();
    make_random_btree(T,10,0.5);
    Tcpy = T;
    printf("T: "); T.lisp_print(); 
    printf("\n");

    // aplica cumsum_down e imprime
    cumsum_down(T);
    printf("after cumsum_down(T):"); 
    T.lisp_print(); printf("\n");

    // aplica cumsum_up e imprime
    cumsum_up(Tcpy);
    printf("after cumsum_up(T):"); 
    Tcpy.lisp_print();
    printf("\n--------\n");
  }

  return 0;
}
