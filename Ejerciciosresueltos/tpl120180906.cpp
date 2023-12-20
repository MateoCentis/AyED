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

   #sign-split:# Implemente una funcion 
   #void sign_split(list<int> &L,vector< list<int> > &VL);# que dada una
   lista #L#, retornar el un vector de listas #VL# las sublistas
   contiguas del mismo signo (el caso 0 es considerado junto con los
   positivos, es decir separa negativos de no-negativos).


   #sign-join:# Implemente una funcion
   #void sign_join(vector< list<int> > &VL,list<int> &L);#
   que, dado un vector de listas #VL# generar una lista #L# donde estan
   primero concatenados todos la primera subsecuencia de
   no-negativos de #VL[0]#, #VL[1]#, Despues los negativos, 
   despues nuevamente los no-negativos, y asi siguiendo hasta que se acaban todos los #VL#. 

   #reverse-stack:# Escribir un programa que invierta una
   pila #S# utilizando recursion. No esta permitido el uso de constructores
   iterativos (#while#, #for#, etc) ni tampoco el uso estructuras de datos
   adicionales. Solo pueden utilizarse metodos de la pila.

   [Tomado en el Trabajo Practico de Laboratorio Nro 1
   (TPL1) de 2018-09-06].
   keywords: lista

FIN DE DESCRIPCION */

// Funcion `signo' pero modificada. El 0 se considera junto
// con los positivos.
int sign(int x) { return (x>=0? 1: -1); }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void sign_split(list<int> &L,vector< list<int> > &VL) {
  // Limpiar el contenedor de salida por las dudas
  VL.clear();
  // Si L esta vacia VL tambien lo esta
  if (L.empty()) return;
  // Ver el signo del primer elemento
  int s=sign(*L.begin());
  // Iterador sobre L
  auto q = L.begin();
  while (q != L.end()) {
    // Poner elementos en tmp mientras tengan el mismo signo
    // que estamos buscando actualmente
    list<int> tmp;
    while (q!= L.end() && sign(*q)==s)
      tmp.push_back(*q++);
    // Llegamos al final o bien se acabaron los de este signo.
    // Poner la lista temporaria en VL
    VL.push_back(tmp);
    // Invertir el signo
    s = -s;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void sign_join(vector< list<int> > &VL,list<int> &L) {
  // Limpiar el contenedor de salida por las dudas
  L.clear();
  // Empezamos con los no-negativos, despues alternadamente vamos
  // cambiando de signo. 
  int s=1;
  while (1) {
    // Esta bandera detecta cuando todos los contenedores
    // estan vacios para terminar
    bool all_empty = true;
    // Recorre los VL[j], *z es una lista
    auto z = VL.begin();
    while (z!=VL.end()) {
      // Actualiza el `all_empty' si algun VL[j] no esta vacio
      if(!z->empty()) all_empty=false;
      // Mientras haya elementos en *z ponerlos en L y
      // sacarlos de *z
      while (!z->empty() && sign(z->front())==s) {
        L.push_back(z->front());
        z->pop_front();
      }
      // Incrementar el iterador
      z++;
    }
    // Si estan todos vacios terminar
    if (all_empty) break;
    // Invertir el signo
    s = -s;
  }
}

// Inserta un elemento en el fondo de una pila, solo usando
// recursividad. Es una funcion auxiliar para `reverseStack'
void insertAtBottom(stack<int>&S, int x){
  if(S.empty()){
    // Si la pila esta vacia corta la recursion
    S.push(x);
  }else{
    // Extrae el elemento del tope de la pila 
    int temp = S.top();
    S.pop();
    // Inserta en el fono de la pila (que ahora es de un tamano menor)
    insertAtBottom(S,x);
    // Restablece el elemento del tope
    S.push(temp);
  }
}

void reverseStack(stack<int>&S){
  // Si la pila esta vacia no hay que hacer nada y corta la
  // recursion
  if(!S.empty()){
    // Extrae el elemento del tope
    int temp = S.top();
    S.pop();
    // Aplica recursividad sobre la pila (ahora es de tamano menor)
    reverseStack(S);
    // Inserta el elemento que era el tope en el fondo
    // usando la funcion auxiliar
    insertAtBottom(S,temp);
  }
} 

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  do {

    ev.eval<1>(sign_split,vrbs);
    h1 = ev.evalr<1>(sign_split,seed,vrbs);

    ev.eval<2>(sign_join,vrbs);
    h2 = ev.evalr<2>(sign_join,seed,vrbs);

    ev.eval<3>(reverseStack,vrbs);
    h3 = ev.evalr<3>(reverseStack,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    printf("\n\nIngrese un valor para la semilla:");
  } while (cin>>seed);

  return 0;
}
