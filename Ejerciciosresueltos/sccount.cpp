/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Cuenta la cantidad de "hijos unicos" de un arbol binario. 
   [Tomado en el TPL3 2013-11-09].
   keywords: arbol binario

   FIN DE DESCRIPCION */

// -----------------------------------------------------------------
#include <cstdio>
#include <iostream>
#include "./util.h"
#include "./btree.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

typedef btree<int> tree_t;
typedef btree<int>::iterator node_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int sccount(tree_t &T, node_t n) {
  if (n==T.end()) return 0;
  node_t l=n.left(), r=n.right();
  int nchild = (l==T.end()) + (r==T.end());
  return (nchild==1) + sccount(T,l) + sccount(T,r);
}
             
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
int sccount(tree_t &T) {
  return sccount(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  btree<int> T;

  for (int j=0; j<20; j++) {
    // Genera un arbol binario aleatorio
    make_random_btree (T, 10, 0.8);
    printf("----------------\n");
    T.lisp_print();
    printf("\nNro de hijos unicos %d\n",sccount(T));
  }
  
  return 0;
}
