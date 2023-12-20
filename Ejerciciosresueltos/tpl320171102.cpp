#define USECHRONO
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

using namespace aed;
using namespace std;

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   #isBST:# Dado un arbol binario #T,# determinar si es un
    arbol binario de busqueda.

    #fillBST:# Dada una lista de enteros #L# y un arbol
    binario #T,# generar #fillBST# que inserta los elementos
    de #L# en #T# formando un arbol binario de busqueda
    siguiendo el orden original de #L.#

    #eqsumplit.# Escribir un predicado que retorna #true#
    sii el conjunto #S# se puede descomponer en dos conjuntos
    disjuntos #S1# y #S2# tales que la suma de los elementos
    de #S1# es igual a la suma de #S2.#

    [Tomado en el TPL3 de 2017-11-02].  
    keywords: arbol binario, conjunto

FIN DE DESCRIPCION */

void inorden(btree<int>&T,btree<int>::iterator it,list<int>&L){
  // Genera el listado en orden simetrico
  if(it == T.end())
    return;
  inorden(T,it.left(),L);
  L.push_back(*it);
  inorden(T,it.right(),L);
}

// Un arbol binario AB es de busqueda sii el listado en
// orden simetrico esta ordenado.
bool isBST(btree<int>&T){
  list<int> orden;
  inorden(T,T.begin(),orden);
  list<int>::iterator it, it2;
  it = orden.begin();
  it2 = it;it2++;
  while(it2!=orden.end()){
    // Chequea que los elementos esten ordenados y sean
    // estrictamente diferentes.
    if(*it2<=*it)
      return false;
    it++;it2++;
  }
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Otra solucion. La funcion recursiva retorna si
// ademas el minimo y el maximo del subarbol
bool isBST2(btree<int>&T, btree<int>::iterator it,
            int &min,int &max){
  if (it==T.end()) {
    // INT_MAX, INT_MIN estan definidos en `climits.h'
    min = INT_MAX;
    max = INT_MIN;
    return true;
  }
  int minr,maxr,minl,maxl;
  auto ql=it.left(), qr=it.right();
  if (!isBST2(T,ql,minl,maxl)) return false;
  if (!isBST2(T,qr,minr,maxr)) return false;
  int n = *it;
  if (maxl>=n || minr<=n) return false;
  min = (ql==T.end()? n : minl);
  max = (qr==T.end()? n : maxr);
  return true;
}

bool isBST2(btree<int>&T){
  int min,max;
  return isBST2(T,T.begin(),min,max);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Otra solucion. Usa funciones auxiliares para el minimo
// y maximo de un BT.

// Busca el minimo avanzando por hijo izquierdo
int min(btree<int>&T, btree<int>::iterator n) {
  if (n==T.end()) return INT_MAX;
  auto c=n;
  while (1) {
    c = n.left();
    if (c==T.end()) return *n;
    n=c;
  }
}

// Busca el maximo avanzando por hijo derecho
int max(btree<int>&T, btree<int>::iterator n) {
  // INT_MAX, INT_MIN estan definidos en `climits.h'
  if (n==T.end()) return INT_MIN;
  auto c=n;
  while (1) {
    c = n.right();
    if (c==T.end()) return *n;
    n=c;
  }
}

bool isBST3(btree<int>&T, btree<int>::iterator n){
  // Un arbol vacio es BST
  if (n==T.end()) return true;
  auto ql=n.left(), qr=n.right();
  // Chequea que los subarboles der e izq sean BST
  if (!isBST3(T,ql)) return false;
  if (!isBST3(T,qr)) return false;
  // Chequea la condicion en el nodo
  return max(T,ql)<*n && *n<min(T,qr);
}

bool isBST3(btree<int>&T){ return isBST3(T,T.begin()); }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void fillBST(btree<int>&T,list<int>&L){
  btree<int>::iterator n = T.begin();
  if(L.empty()) return;
  n = T.insert(n,*L.begin());
  L.erase(L.begin());
  while(!L.empty()){
    while(n != T.end()){
      if(*n>*L.begin())
        n = n.left();
      else if(*n<*L.begin())
        n = n.right();
      else {
        if(L.size() != 1)
          n = T.begin();
        else n = T.end();
        L.erase(L.begin());
      }
    }
    if(L.size()>=1 && n !=T.begin()){
      n = T.insert(n,*L.begin());
      L.erase(L.begin());
      n = T.begin();
    }
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Basicamente es un algoritmo tipo
// powerset es decir prueba con S1 todos los subconjuntos de
// S. Para cada S1 

// Funcion auxiliar calcula la suma de los elementos de un conjunto
int sum(set<int> &S) {
  int s=0;
  for (auto q:S) s+=q;
  return s;
}

// Funcion recursiva auxiliar. Chequea con todos los S1
// subconjuntos de W.
bool eqsumsplit(set<int> &S,set<int> &W) {
  // Prueba con S1=W
  set<int> S2,S1=W;
  set_difference(S,S1,S2);
  if (sum(S1)==sum(S2)) return true;
  // Prueba recursivamente con todos los subconjuntos
  // que se obtienen tomando cualquier elemento `x' de
  // W y formando W-{x}
  for (auto x:W) {
    set<int> W1=W;
    W1.erase(x);
    if (eqsumsplit(S,W1)) return true;
  }
  // No encontro ninguna solucion
  return false;
}

// Wrapper que llama a la recursiva
bool eqsumsplit(set<int> &S) {
  return eqsumsplit(S,S);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Otra solucion.
bool eqssplit2(set<int> &SS, int s1=0, int s2=0) {
  set<int> S=SS;
  if (S.empty()) return s1==s2;
  int x = *S.begin(); S.erase(S.begin());
  if (eqssplit2(S,s1+x,s2)) return true;
  if (eqssplit2(S,s1,s2+x)) return true;
  return false;
}

// Wrapper
bool eqsumsplit2(set<int> &SS) { return eqssplit2(SS); }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 386;
  int h1=0,h2=0,h3=0;

  do {
    ev.eval<1>(isBST,vrbs);
    h1 = ev.evalr<1>(isBST,seed,vrbs);
    
    ev.eval<2>(fillBST,vrbs);
    h2 = ev.evalr<2>(fillBST,seed,vrbs);
    
    ev.eval<3>(eqsumsplit,vrbs);
    h3 = ev.evalr<3>(eqsumsplit,seed,vrbs);
    
    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    printf("\n\nIngrese un valor para la semilla:");
  } while (cin>>seed);
  
  return 0;
}
