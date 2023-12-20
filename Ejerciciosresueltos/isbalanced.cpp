// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
  Un arbol binario (AB) es balanceado si
  1) Es el arbol vacio o,
  2) Sus subarboles derecho e izquierdo son balanceados, y sus
    alturas difieren a lo sumo en 1
  Consigna: Escribir una funcion #bool is_balanced(btree<int> &T);#
  que determina si el arbol esta balanceado. 
   [Tomado en el segundo parcial 2011-10-27].
   keywords: arbol binario

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------
#include <cstdarg>
#include <cstdio>
#include <climits>

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "./util.h"
#include "./btree.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
typedef btree<int>::iterator node_t;
bool is_balanced(btree<int> &T,node_t n,int &height) {
  height = -1;
  if (n==T.end()) return true;
  node_t 
    ql = n.left(),
    qr = n.right();
  int hl,hr;
  height = INT_MAX;
  if (!is_balanced(T,ql,hl)) return false;
  if (!is_balanced(T,qr,hr)) return false;
  height = (hl>hr ? hl : hr)+1;
  return abs(hl-hr)<=1;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool is_balanced(btree<int> &T) {
  int height;
  return is_balanced(T,T.begin(),height);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Uses `decomp_int' for generating balanced trees
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
// Wrapper for decomp_int
void decomp_int(btree<int> &T,int m) {
  T.clear();
  T.insert(T.begin(),m);
  decomp_int(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  btree<int> T;

  // These are most probably unbalanced
  for (int j=1; j<10; j++) {
    T.clear();
    make_random_btree(T, 10, 1.);
    T.lisp_print();
    printf("\n");
    printf("is balanced ? %d\n-----------\n",is_balanced(T));
  }

  // Balanced trees
  for (int j=1; j<10; j++) {
    T.clear();
    decomp_int(T,j);
    T.lisp_print();
    printf("\n");
    printf("is balanced ? %d\n-----------\n",is_balanced(T));
  }

  return 0;
}
