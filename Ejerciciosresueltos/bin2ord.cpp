//$Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   bin2ord: Escribir una funcion #void bin2ord(btree<int> &B, tree<int>#
   #&T);# que dado un AB B de enteros POSITIVOS lo convierte a un AOO con
   la siguiente convencion. En caso de que uno de los nodos del AB tenga
   uno solo de los hijos reemplazamos el valor por un valor LAMBDA (en
   este caso puede ser LAMBDA=-1).
   ord2bin: Escribir la funcion inversa #void ord2bin(tree<int> &T,#
   #btree<int> &B);# que dado un AOO (que supuestamente fue generado por
   bin2ord) lo convierte de nuevo a AB. (Deberia ser siempre
   #B=ord2bin(bin2ord(B))# )
   [Tomado 2do parcial de 2012, 2012-10-25]
   keywords: arbol orientado, arbol binario

   FIN DE DESCRIPCION */

// -----------------------------------------------------------------
#include <cstdio>
#include <iostream>
#include "./util.h"
#include "./tree.h"
#include "./btree.h"
#include "./util_tree.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

typedef btree<int>::iterator bnode_t;
typedef tree<int>::iterator node_t;

// Este es el valor especial que deben tomar los nodos LAMBDA
const int LAMBDA = -1;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void bin2ord(btree<int> &B, bnode_t b, 
             tree<int> &T, node_t t) {
  // Construye el AOO en el nodo `t' a partir del AB en el nodo `b'
  // Presupone que b y t no son end() 
  if (b==B.end()) return;
  // Asigna la raiz
  *t = *b;
  node_t l,r;
  if (b.right()!=B.end() || b.left()!=B.end()) {
    // Inserta preventicamente dos valores LAMBDA en los hijos de `t'
    l = t.lchild();
    l = T.insert(l,LAMBDA);
    r = l; r++;
    r = T.insert(r,LAMBDA);
    
    // Recursivamente la funcion se encarga de setear el valor si el
    // correspondiente nodode de B no es end()
    bin2ord(B,b.left(),T,l);
    bin2ord(B,b.right(),T,r);
  }
}
             
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void bin2ord(btree<int> &B, tree<int> &T) {
  T.clear();
  // Si B esta vacio no hay que hacer nada
  if (B.begin()==B.end()) return;
  // Agrega un LAMBDA en el AOO para empezar
  T.insert(T.begin(),LAMBDA);
  // Aplica recursivamente
  bin2ord(B,B.begin(),T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void ord2bin(tree<int> &T, node_t t,
             btree<int> &B,bnode_t b) {
  // Si el nodo en el AOO es end() o LAMBDA el
  // correspondiente AB es vacio
  if (t==T.end() || *t==LAMBDA) return;
  // Copia el valor de la raiz
  b = B.insert(b,*t);
  // Obtiene los nodos left y right del AOO.
  // Puede ser que no tenga ninguno o los dos
  node_t l = t.lchild(), r;
  if (l==T.end()) return;
  r=l; r++;
  assert(r!=T.end());
  // Aplica recursivamente
  ord2bin(T,l,B,b.left());
  ord2bin(T,r,B,b.right());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void ord2bin(tree<int> &T, btree<int> &B) {
  B.clear();
  ord2bin(T,T.begin(),B,B.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Incluimos el predicado de igualdad. Lo que vamos
// a verificar es que ord2bin(bin2ord) = identidad
bool iguales (btree<int> & A, btree<int>:: iterator p,
              btree<int> & B, btree<int>:: iterator q) { 
  bool b1, b2 ;
  if      ( p == A.end () xor q == B.end () ) { 
    return (false) ; }
  else if ( p == A.end () ) { 
    return (true)  ; }
  else if ( *p != *q ) { 
    return (false) ; }
  else {
    b1 = iguales (A, p.right (), B, q.right ()); 
    b2 = iguales (A, p.left  (), B, q.left  ());
    return (b1 && b2) ;
  } // end if
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool iguales (btree<int> & A, btree<int> & B){
  return iguales (A, A.begin(), B, B.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  tree<int> T;
  btree<int> B,B2;

  for (int j=0; j<20; j++) {
    // Genera un arbol binario aleatorio
    make_random_btree (B, 10, 0.8);
    printf("----------------------------------------------\n");
    printf("btree T: ");
    B.lisp_print();
    printf("\n");
  
    // Lo convierte a AOO
    printf("tree T = bin2ord(B): ");
    bin2ord(B,T);
    T.lisp_print();
    printf("\n");
    
    // Lo vuelve a AB
    printf("btree B2 = ord2bin(T): ");
    ord2bin(T,B2);
    B2.lisp_print();
    printf("\n");

    // Chequea que sean iguales
    printf("B==B2? %d\n",iguales(B,B2));
  }
  
  return 0;
}
