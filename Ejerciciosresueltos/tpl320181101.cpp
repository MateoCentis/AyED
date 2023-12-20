#define USECHRONO
#undef HAVE_MPI
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

   #make-full:# Implementar una funcion 
   #void make_full(btree<int> &T);# que elimina (in-place) los nodos interiores
   de un arbol binario que tienen un solo hijo, de manera que el arbol
   resultante es un arbol binario lleno (Full Binary Tree). En el arbol
   resultante solo deben quedar hojas o arboles interiores con dos
   hijos.

   #max-subtree:# Escribir una funcion,
   #int max_subbtree(btree<int>&T);#
   que retorna la suma de etiquetas maxima de entre todos los posibles
   subarboles del arbol binario #T.#

   #most-connected:# Implementar una funcion 
   #int most_connected(vector< set<int> > &VS);#
   que retorna el indice #j# tal que el conjunto #VS[j]# es el que
   esta \emph{conectado} con un mayor numero de otros conjuntos de
   #VS.# Decimos que dos conjuntos estan conectados si no son disjuntos,
   es decir, si tienen interseccion comun no vacia.

   [Tomado en el Trabajo Practico de Laboratorio Nro 3
   (TPL3) de 2018-11-01].
   keywords: arbol binario, conjunto

FIN DE DESCRIPCION */

typedef btree<int>::iterator bnode_t;
// Funcion recursiva. Cmo cambia la estructura del arbol
// tiene que retornar el nodo refrescado
bnode_t make_full(btree<int> &T,bnode_t n) {
  // Arbol vacio, no hay que hacer nada
  if (n==T.end()) return n;
  // Nodos derecho e izquierdo
  bnode_t cl = n.left(), cr=n.right();
  // Aplica recursivamente a los hijos (OJO refrescar!!)
  cl = make_full(T,cl);
  cr = make_full(T,cr);
  // Booleanos que indica si tiene cada uno de los hijos
  bool hasL=(cl!=T.end()), hasR=(cr!=T.end());
  // Si NO tiene los dos es una hoja -> no hay que hacer nada
  // Si SI tiene los dos entonces es lleno -> no hay que hacer nada
  if (hasL==hasR) return n;
  // Si llega aca es porque tiene uno y solo uno de los hijos. 
  // CHILD: es el hijo que es dereferenciable
  bnode_t child = (hasL? cl : cr);
  // Arbol temporario
  btree<int> tmp;
  // Splicea el subarbol de CHILD al temporario
  T.splice(tmp.begin(),child);
  // Borra el nodo (es una hoja a esta altura)
  n = T.erase(n);
  // Splicea de vuelta el temporario al nodo
  bnode_t from = tmp.begin();
  n = T.splice(n,from);
  // Retorna el nodo refrescado
  return n;
}

// Wrapper
void make_full(btree<int> &T) {
  make_full(T,T.begin());
}

// Otra solucion, no necesita refrescar los iteradores
void make_full2(btree<int> &T, btree<int>::iterator it) {
  if ( (it.left()==T.end()) != (it.right()==T.end()) ) {
    // Tiene uno solo de los hijos, elimina el nodo y
    // splicea ese hijo
    // T2 es un temporario para splicear
    btree<int> T2;
    // ITC es el nodo que no es Lamdba
    auto itc = it.left()==T.end() ? it.right() : it.left();
    // Mueve el subarbol del hijo al temporario
    T2.splice(T2.begin(),itc);
    // Elimina el nodo (a esta altura es una hoja)
    it = T.erase(it);
    // Splicea de vuelta el temporario al nodo eliminado
    auto it2 = T2.begin();
    it = T.splice(it,it2);
    // Aplica recursivamente
    make_full2(T,it);
  } else {
    // Los dos nodos son Lambda o NO. Le aplica la funcion
    // recursivamente a cada uno de ellos (si no son Lambda)
    if (it.left()!=T.end()) make_full2(T,it.left());
    if (it.right()!=T.end()) make_full2(T,it.right());
  }
}

// Wrapper
void make_full2(btree<int> &T) {
  make_full2(T,T.begin());
}

// Funcion auxiliar, hace la suma del subarbol de IT en el
// arbol T
int aux(btree<int>&T,btree<int>::iterator it){
  if(it==T.end()) return 0;
  int l = aux(T,it.left());
  int r = aux(T,it.right());
  return *it+l+r;
}

// Retorna la suma del maximo subarbol de un nodo en el
// subarbol de IT.  Busca el maximo en cada uno de los hijos
// ML,MR y despues considera: Los subarboles encontrados en
// los hijos (ML y MR) y despues la suma correspondiente al
// subarbol de IT mismo
int max_subbtree(btree<int>&T,btree<int>::iterator it){
  if(it==T.end()) return 0;
  int Ml = max_subbtree(T,it.left());
  int Mr = max_subbtree(T,it.right());
  int M = aux(T,it);
  return max(max(M,Ml),Mr);
}
    
int max_subbtree(btree<int>&T){
  return max_subbtree(T,T.begin());
}

// Retorna el indice J de aquel set VS[J] tal que VS[J] esta
// "conectado" a la mayor cantidad de los otros conjuntos
// VS[K].  Dos conjuntos VS[J],VS[K] estan conectados si
// tienen interseccion no-nula.
int most_connected(vector< set<int> > &VS) {
  // Numero de conjuntos en VS
  int nset= VS.size();
  // Inicializar indx (posicion del mas conectado) y su
  // numero de conexiones
  int indx=-1,maxcon=-1;
  // Recorre todos los conjuntos
  for (int j=0; j<nset; j++) {
    // Cuenta cuantos conjuntos tienen interseccion no-nula
    int jcon=0;
    set<int> &VSj = VS[j];
    for (int k=0; k<nset; k++) {
      set<int> &VSk = VS[k];
      set<int> tmp;
      // Usa un temporario para la interseccion
      set_intersection(VSj,VSk,tmp);
      // Sumar 1 si la interseccion no es vacia
      jcon += !tmp.empty();
    }
    // Si el actual J tiene mas conexiones que el mas
    // conectacto hasta ahora => actualizar
    if (jcon>maxcon) {
      maxcon = jcon;
      indx = j;
    }
  }
  return indx;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool connected(set<int> &s1,set<int> &s2) {
  set<int> tmp;
  // Usa un temporario para la interseccion
  set_intersection(s1,s2,tmp);
  return !tmp.empty();
}

// Retorna el indice J de aquel set VS[J] tal que VS[J] esta
// "conectado" a la mayor cantidad de los otros conjuntos
// VS[K].  Dos conjuntos VS[J],VS[K] estan conectados si
// tienen interseccion no-nula.
int most_connected2(vector< set<int> > &VS) {
  // Numero de conjuntos en VS
  int nset= VS.size();
  // Inicializar indx (posicion del mas conectado) y su
  // numero de conexiones
  int indx=-1,maxcon=-1;
  // Recorre todos los conjuntos
  for (int j=0; j<nset; j++) {
    // Cuenta cuantos conjuntos tienen interseccion no-nula
    int jcon=0;
    for (int k=0; k<nset; k++) jcon += connected(VS[j],VS[k]);
    // Si el actual J tiene mas conexiones que el mas
    // conectacto hasta ahora => actualizar
    if (jcon>maxcon) {
      maxcon = jcon;
      indx = j;
    }
  }
  return indx;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  do {

    ev.eval<1>(make_full,vrbs);
    h1 = ev.evalr<1>(make_full,seed,vrbs);

    ev.eval<2>(max_subbtree,vrbs);
    h2 = ev.evalr<2>(max_subbtree,seed,vrbs);

    ev.eval<3>(most_connected,vrbs);
    h3 = ev.evalr<3>(most_connected,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    printf("\n\nIngrese un valor para la semilla:");
  } while (cin>>seed);

  return 0;
}
