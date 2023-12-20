// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
  A partir de un numero entero #m#
  escribir una funcion #void decomp_int(int m, btree<int> &T);#
  que construye el arbol binario #T# de la siguiente forma:
  1) Si #m=0# da el arbol vacio
  2) Si #m=1# contiene un solo nodo con el valor 1. 
  3) Si #m>1#
  3.a) En la raiz contiene #m#
  3.b) En los hijos izquierdo y derecho contiene los valores
    #mr=m/2# y #ml=m-mr#. 
  3.c)  Propaga recursivamente la decomposicion a los nodos. 
  Por ejemplo si #m=5# entonces el arbol generado es 
  #(5 (3 (2 1 1) 1) (2 1 1))#. 
   [Tomado en el segundo parcial 2011-10-27].
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
void decomp_int(btree<int> &T,node_t p) {
  if (p==T.end()) return;
  if (*p==1) return;
  int mr=*p/2, ml=*p-mr;
  T.insert(p.left(),ml); 
  decomp_int(T,p.left());
  T.insert(p.right(),mr); 
  decomp_int(T,p.right());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void decomp_int(btree<int> &T,int m) {
  T.clear();
  T.insert(T.begin(),m);
  decomp_int(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  btree<int> T;

  decomp_int(T,5);
  T.lisp_print();
  printf("\n");

  return 0;
}
