// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Se define una relaci\'on de orden entre AOO de enteros de
   la siguiente forma: #A<B# si
   #(na,c0a,c1a,c2a...)<(nb,c0b,c1b,c2b...)#, donde #na# es
   la raiz de #A#, #h0a# el subarbol del primer hijo de #A#
   y asi siguiendo. En la expresion anterior se toma el orden 
   lexicografico para listas y se asume que en caso de tener 
   longitudes diferentes se completa con -infinito. 
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
// Comparacion por < de arboles
bool lesser_aux(tree<int> &A,tree<int>::iterator na,
          tree<int> &B,tree<int>::iterator nb) {
  // Primero vemos si algunas de las raices es Lambda.
  // Si A=Lambda y B!=Lambda entonces A<B
  // Si A=B=Lambda A==B
  // Si A!=Lambda y B=Lambda A>B
  if (nb==B.end()) return false;
  if (na==A.end()) return true;
  // Ninguno es Lambda, comparamos los valores
  if (*na!=*nb) return *na<*nb;
  // Ahora vamos comparando uno a unos los hijos.
  // No tenemos comparacion por diferencia, asi que hacemos
  // !a<b y !b<a
  node_t 
    ca = na.lchild(),
    cb = nb.lchild();
  while (ca!=A.end() && cb!=B.end()) {
    if (lesser_aux(A,ca,B,cb)) return true;
    if (lesser_aux(B,cb,A,ca)) return false;
    ca++; cb++;
  }
  // Si llegamos aca alguna de las listas de hijos es end.
  // Solo es A<B si el que es end() es ca y cb no. 
  return ca==A.end() && cb!=B.end();
}


//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Makes a random tree with `s' siblings and `m' nodes
void make_random_tree2(tree<int> &T,tree<int>::iterator n,
                       int M, int m,int s) {
  if (!m) return;
  // Toma los m nodos y los divide en `ss' siblings donde s es aleatorio
  // en [1,s]
  int ss = rand()%s+1;
  // Inserta un nodo en la raiz
  n = T.insert(n,rand()%M);
  m--; // toma en cuenta que ya inserto 1
  // Reparte los nodos que quedan aleatoriamente en los ss hijos
  vector<int> v(ss,0);
  for (int j=0; j<m; j++) v[rand()%ss]++;
  // A esta altura tenemos un vectos v[] con s enteros
  // cuya suma es `m'.  Algunos pueden ser nulos, pero no importa
  // porque en ese caso la llamada recursiva no va a hacer nada. 
  for (int j=0; j<v.size(); j++) 
    make_random_tree2(T,n.lchild(),M,v[j],s);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void make_random_tree2(tree<int> &T,int M, int m,int s) {
  make_random_tree2(T,T.begin(),M,m,s);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper para la funcion de comparacion.
// (No se porque el compilador patalea si tiene el mismo nombre
// que la auxiliar, por eso le pongo comp2). 
bool lesser(tree<int> A,tree<int> B) {
  return lesser_aux(A,A.begin(),B,B.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Predicado de igualdad para arboles
bool equal(tree<int> &T1,tree<int>::iterator n1,
           tree<int> &T2,tree<int>::iterator n2) {
  // Si uno es Lambda y el otro no: false
  if ((n1==T1.end()) != (n2==T2.end())) return false;
  // Si n1==end entonces n2 tambien y por lo tanto: true
  if (n1==T1.end()) return true;
  // Si los valores son distintos: false
  if (*n1 != *n2) return false;
  // Compara recursivamente los hijos
  tree<int>::iterator c1 = n1.lchild(), c2 = n2.lchild();
  while (c1!=T1.end() && c2!= T2.end()) {
    // Si no son iguales los subarboles: false
    if (!equal(T1,c1,T2,c2)) return false;
    c1++; c2++;
  }
  // Si en alguno de los dos quedo algo: falso, si no: true
  return (c1!=T1.end()) == (c2!=T2.end());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
bool equal(tree<int> &T1,tree<int> &T2) {
  return equal(T1,T1.begin(),T2,T2.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  typedef tree<int> tree_t;
  // TEST 2
  int N=50;
  vector<tree_t> treev(N);
  // Genera N arboles aleatorios y los ordena
  // (ahi usa la funcion de comparacion)  
  printf("----------------\nNO ORDENADOS:\n");
  for (int j=0; j<N; j++) {
    // make_random_tree(treev[j],10,1.0);
    make_random_tree2(treev[j],3,5,2.0);
    printf("treev[%d]: ",j);
    treev[j].lisp_print();
    printf("\n");
  }
  sort(treev.begin(),treev.end(),lesser);

  printf("----------------\nORDENADOS:\n");
  for (int j=0; j<N; j++) {
    printf("treev[%d]: ",j);
    treev[j].lisp_print();
    printf("\n");
  }

  // TEST 2, genera M pares de arboles y los compara
  // Uno solo de los siguientes puede ser verda:
  // T1<T2, T1==T2 o T1>T2. Chequea esto para los M pares. 
  int bad=0,ok=0,M=10000;
  for (int j=0; j<M; j++) {
    tree_t T1,T2;
    make_random_tree2(T1,3,5,2.0);
    make_random_tree2(T2,3,5,2.0);
    int l=lesser(T1,T2),
      e=equal(T1,T2),
      g=lesser(T2,T1),
      f = (l+g+e==1);
    ok += f;
    bad += !f;
    // printf("T1<T2 %d, T1==T2 %d, T1>T2 %d, ok? %d\n",
    //        l,g,e,f);
    if (!ok) {
      // No se cumplio la condicion, error
      printf("T1: ");
      T1.lisp_print();
      printf("\n");

      printf("T2: ");
      T2.lisp_print();
      printf("\n--------------\n");
      
      int b = lesser(T1,T2);
      printf("lesser(T1,T2) %d\n",b);
      b = lesser(T2,T1);
      printf("lesser(T2,T1) %d\n",b);
      exit(0);
    }
  }
  printf("Tested %d, ok %d, bad %d\n",M,ok,bad);
  return 0;
}
