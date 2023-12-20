// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Escribir una funcion
   #void count_level(tree<int> &T, int l),# que
   cuenta cuantos nodos hay en el nivel #l# del arbol #T#. 
   [Tomado en el TPL2 2013-10-12].
   keywords: arbol orientado

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------
#include <cstdarg>
#include <cstdio>

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "./util.h"
#include "./tree.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

typedef tree<int> tree_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int count_level(tree_t &T,tree_t::iterator n,int l) {
  if (n==T.end()) return 0;
  if (l==0) return 1;
  tree_t::iterator c = n.lchild();
  int m=0;
  while (c!=T.end()) m += count_level(T,c++,l-1);
  return m;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int count_level(tree_t &T,int l) {
  return count_level(T,T.begin(),l);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  tree_t T;
  make_random_tree2(T,5,10,2.0);
  T.lisp_print();
  printf("\n");
  int l=0;
  while (1) {
    int m = count_level(T,l);
    if (!m) break;
    printf("Level %d, nodes %d\n",l++,m);
  }
  return 0;
}
