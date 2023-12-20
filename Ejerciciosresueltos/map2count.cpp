// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Escribir una funcion 
   #void map2count(tree<int> &A,tree<int> &B);# que construye un arbol #B#
   a partir de otro dado #A# tal que #B# tiene la misma estructura
   que #A#, y el valor en el nodo #nB# de #B# es la cantidad de
   hojas en el subarbol del nodo correspondiente #nA# en #A#. 

   [Tomado en el final de 2012-12-06].  
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

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
typedef tree<int> tree_t;
typedef tree<int>::iterator node_t;

#if 1
void map2count(tree<int> &A, tree<int> &B, 
               tree<int>::iterator n){
  if (n==B.end()) return;

  if(n.lchild()==B.end()) { *n=1; return;   }

  *n=0;
  tree<int>::iterator c = n.lchild();
  while (c!=B.end()) { 
    map2count(A,B,c);
    *n += *c;
    c++;
  }
}

void map2count(tree<int> &A, tree<int> &B){
  B.clear();
  B=A;
  map2count(A,B,B.begin());
}

#else
node_t map2count(tree_t &A,node_t a,tree_t &B,node_t b) {
  node_t ca = a.lchild();
  // Es una hoja
  if (ca==A.end())  {
    b = B.insert(b,1);
    return b;
  }
  // Crea el nodo `b' en `B', todavia no conoce
  // el valor, le pone 0
  b = B.insert(b,0);
  node_t cb = b.lchild();
  int hojas=0;
  while (ca!=A.end()) {
    cb = map2count(A,ca,B,cb);
    hojas += *cb;
    cb++; ca++;
  }
  *b = hojas;
  return b;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void map2count(tree_t &A,tree_t &B) {
  B.clear();
  if (A.begin() == A.end()) return;
  map2count(A,A.begin(),B,B.begin());
}
#endif

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  // TEST 2
  int N=50;
  // Genera N arboles aleatorios y los ordena
  // (ahi usa la funcion de comparacion)  
  printf("----------------\nNO ORDENADOS:\n");
  tree_t A,B;
  for (int j=0; j<N; j++) {
    make_random_tree2(A,20,10,2.0);
    printf("--------\nA: ",j);
    A.lisp_print();
    printf("\n");
    map2count(A,B);
    printf("map2count(A): ");
    B.lisp_print();
    printf("\n");
  }
  printf("\n");
  return 0;
}
