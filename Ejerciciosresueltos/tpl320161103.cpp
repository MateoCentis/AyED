#define USECHRONO
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   #puede-simplificar:# Se utiliza un arbol binario para representar una
   expresion matematica, donde los nodos interiores representan
   operadores binarios, y los nodos hoja operandos (variables o
   constantes).  Escriba una funcion para determinar si la
   expresion que representa el arbol puede simplificarse extrayendo 
   un factor comun.

   #prune-and-return:# Implemente la funcion #prune(T,v,L)#
   que dado un arbol binario #T# busque el nodo cuya
   etiqueta sea #v# y retorne en #L# la lista en preorden de
   todos los nodos del subarbol
   correspondiente. Adicionalmente el nodo y su subarbol debe ser eliminado de #T#. 

   #gather-sets:# Dado un vector de conjuntos  y un predicado
   retornar la union de todos los conjuntos que
   contienen al menos un elemento que satisface el predicado.

   [Tomado en el Trabajo Practico de Laboratorio Nro 3
   (TPL3) de 2016-11-03].  
   keywords: arbol binario, conjunto, programacion funcional

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool puede_simplificar(btree<string> &T,
                       btree<string>::iterator it, string fc) {
  // hoja -> si es fc verdadero, sino falso
  if (it.left()==T.end()) 
    return *it==fc;
  
  bool puede_left = puede_simplificar(T,it.left(),fc),
       puede_right = puede_simplificar(T,it.right(),fc);
  // si es una mult, con que uno de los factores tenga el
  // fc como factor comun alcanza
  if (*it=="*" && (puede_left || puede_right))
    return true;
  // si es suma o resta, ambos operandos deben tener al fc como factor comun
  if ( (*it=="+" || *it =="-") && (puede_left && puede_right) ) 
    return true;
  // sino -> no se puede
  return false;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool puede_simplificar(btree<string> &T, string fc) {
  if (T.begin()==T.end()) return false;
  return puede_simplificar(T,T.begin(),fc);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void gather_sets(vector<set<int>> &VS,
                 bool (*pred)(int),set<int> &S) {
  S.clear();
  for(auto &R:VS) {  // por cada conjunto R de VS
    for(int x:R)     // por cada elemento x de R
      if (pred(x)) { // si alguno cumple el predicado
        for(int y:R) // agregar todos los elementos de R a S
          S.insert(y); 
        break;                  // y pasar al siguiente R
      } 
  } 
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void preorden(btree<int>&T, btree<int>::iterator it,
              list<int>& L){
  if(it==T.end()) return;
  L.push_back(*it);
  preorden(T,it.left(),L);
  preorden(T,it.right(),L);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool prune_and_return(btree<int>&T, btree<int>::iterator it,
                      int v, list<int>& L){
  if(it==T.end()) return false;
  if(*it==v){
    preorden(T,it,L);
    T.erase(it);
    return true;
  }else{
    if (prune_and_return(T, it.left(),v,L)) return true;
    else return prune_and_return(T, it.right(),v,L);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void prune_and_return(btree<int>&T, int v, list<int>& L) {
  prune_and_return(T,T.begin(),v,L);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  cout << "seed: 123" << endl;
  do {
    ev.eval<1>(puede_simplificar,vrbs);
    h1 = ev.evalr<1>(puede_simplificar,seed,vrbs);
    
    ev.eval<2>(prune_and_return,vrbs);
    h2 = ev.evalr<2>(prune_and_return,seed,vrbs);
    
    ev.eval<3>(gather_sets,vrbs);
    h3 = ev.evalr<3>(gather_sets,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    cout << endl << "Siguiente seed (ctrl+d para terminar): ";
  } while (cin>>seed);

  return 0;
  
}
