//$Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Escribir una funcion #list2tree(tree<int> &T,list<int> &L);# 
   que dada una lista #L# con el orden previo de #T# y el tamano
   de sus subarboles reconstruye #T#. La forma de almacenar el
   arbol en #T# es la siguiente: se almacena en orden previo 2 
   valores enteros por cada nodo, a saber el contenido del nodo y 
   el numero de hijos. Por ejemplo para el arbol 
   #(6 4 8 (5 4 4) 7 9)# se tenemos
   #L=(6 5 4 0 8 0 5 2 4 0 4 0 7 0 9 0)#. 
   Escribir tambien la funcion inversa #tree2list(tree<int> &T,list<int> &L);# 
   [Tomado en el 2do parcial de 2010, 2010-10-28]
   Keywords: arbol orientado

   FIN DE DESCRIPCION */

// -----------------------------------------------------------------
#include <cstdio>
#include <iostream>
#include "./util.h"
#include "./tree.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

typedef list<int> list_t;
typedef list<int>::iterator pos_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void tree2list(tree_t &T,node_t n,list_t &L) {
  pos_t p = L.end();
  p = L.insert(p,*n); p++;
  p = L.insert(p,0); 
  int nchild = 0;
  node_t c = n.lchild();
  while (c!=T.end())  {
    tree2list(T,c++,L);
    nchild++;
  }
  *p = nchild;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void tree2list(tree_t &T,list_t &L) {
  tree2list(T,T.begin(),L);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
node_t 
list2tree(tree_t &T, node_t n,
          list_t &L,pos_t &p) {
  // Inserta el nodo
  n = T.insert(n,*p++);
  int nchild = *p++;
  
  // Reconstruye los hijos
  node_t c = n.lchild();
  for (int j=0; j<nchild; j++) {
    c = list2tree(T,c,L,p);
    c++;
  }
  return n;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void list2tree(tree_t &T,list_t &L) {
  pos_t p = L.begin();
  list2tree(T,T.begin(),L,p);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  // Prueba con 20 arboles generados aleatoriamente
  for (int j=0; j<20; j++) {
    printf("-----------------\n");
    tree_t T;
    // Genera el arbol
    make_random_tree(T,10,2);
    printf("tree T: ");
    T.lisp_print();
    printf("\n");

    // Lo convierte a lista
    list_t L;
    tree2list(T,L);
    printl(L);

    // Lo reconstruye en T2
    tree_t T2;
    list2tree(T2,L);
    printf("Arbol reconstruido: ");
    T2.lisp_print();
    printf("\n");
 
  }

  // Este ejemplo es el que figuraba en el parcial
  tree_t T;
  list_t L;

  // Debe dar T = (6 4 8 (5 4 4) 7 9)
  add_to_list(L,-1,6,5,4,0,8,0,5,2,4,0,4,0,7,0,9,0,-1);
  list2tree(T,L);
  T.lisp_print();
  printf("\n");
  return 0;
}
