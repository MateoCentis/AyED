#define USECHRONO
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>
#include <numeric>
#include "eval.hpp"

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   #max_sublist_m# Programar una funcion 
   #max_sublist_m(list<int> &L, int m);# que reciba una lista de
   enteros #L# y un entero #m# tal que #0<m<=L.size(),# y encuentre y
   retorne el valor de la mayor suma de entre todas las posibles
   sumas de sublistas de longitud #m.#

   #remove_max_sibling:# Escribir un funcion 
   #void remove_max_sibling(tree<int>&T);# que borra el mayor hijo
   de cada lista de hijos. 

   #max_siblings_sum:# Escriba una funcion 
   #void max_siblings_sum(tree<int>&T,list<int>&L);#
   que reciba un AOO y retorne la lista de nodos
   hermanos (ordenados desde el mas izquierdo) que obtenga
   la mayor suma entre todas sus etiquetas.

   #max_valid_path:# Implementar la funcion
   #int max_valid_path(map<int,set<int>>& G, bool (*pred)(int));# 
   que recibe un grafo no dirigido #G#
   y retorna la longitud del camino mas largo (sin repetir vertices) 
   tal que cada uno de los nodos que lo
   compone satisface el predicado #pred.# 

   [Tomado en el Recup TPLs (TPLR) de 2016-11-10].  
   keywords: lista, arbol orientado, arbol binario, correspondencia, conjunto, programacion funcional

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

int max_sublist_m(list<int> &L, int m){
  int mx = numeric_limits<int>::min(); // para guardar la maxima suma
  int I = L.size()-m+1; // si las sublistas son de largo m, no
                        // pueden empezar mas alla de I
  auto it = L.begin();
  for(int i=0;i<I;i++) { 
    auto it2 = it++; // lista que empieza en it (y de paso
                     // lo incremento para la proxima)
    int aux = 0; // para acumular
    for(int j=0;j<m;j++) aux+=*(it2++);
    mx = max(mx,aux); // me quedo con la max entre lo que tenia
                      // y la que acabo de probar
  }
  return mx;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

void remove_max_sibling(tree<int>&T, tree<int>::iterator it){
  auto itm = T.end(); // aca va el maximo hijo-hoja, empiezo con
                      // end para decir que todavia no hay
  for(auto c = it.lchild();c!=T.end();++c)
    if (c.lchild()==T.end()) { // si es hoja, ver si es el maximo
      if (itm==T.end()||*itm<*c) itm=c; // queda como maximo si
                                        // no habia otro, o si es mejor
                                        // que el que habia
  } else {
    remove_max_sibling(T,c); // si no es hoja, aplicar recursivamente
  }
  if (itm!=T.end()) T.erase(itm); // si habia algun hijo-hoja,
                                  // aca quedo el maximo; borrarlo
}

void remove_max_sibling(tree<int>&T){
  remove_max_sibling(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
const list<int> &maxL(const list<int> &L1, const list<int> &L2) {
  // funcion auxiliar para elegir la mejor entre
  // dos posibles listas de hermanos
  return accumulate(L1.begin(),L1.end(),0) >=
    accumulate(L2.begin(),L2.end(),0) ? L1: L2;
}

list<int> max_siblings_sum(tree<int>&T, tree<int>::iterator it) {
  list<int> Lc, Lm; // Lc es la lista de hijos de este nodo, 
                    // Lm es la mejor entre las que retornan
                    // las llamadas recursivas
  for(auto c=it.lchild();c!=T.end();++c) {
    Lc.push_back(*c);
    // si hay empate entre hijos, en preorden gana el primer hijo
    Lm = maxL(Lm,max_siblings_sum(T,c)); 
  }
  return maxL(Lm,Lc); // si hay empate entre la del nodo
                      // actual y la de los hijos, en preorden
                      // termina antes la de un hijo
}

list<int> max_siblings_sum(tree<int>&T) {
  list<int> Lbeg = { *T.begin() }; // habia que considerar a la raiz
                                   // como una lista con un unico "hermano"
  return maxL(Lbeg,max_siblings_sum(T,T.begin()));
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

int max_valid_path(map<int,set<int>>& G, bool (*pred)(int),
                   int node, int len, set<int> visited) {
  int mx = len; // cantidad de nodos en el camino hasta llegar a este punto
  visited.insert(node); // marcar el actual como visitado
  for(int v:G[node]) // buscar otros nodos que cumplan
                     // el pred y no visitados para seguir
    if (pred(v) && visited.count(v)==0)
      // quedarse siempre con el mayor
      mx = max (mx, max_valid_path(G,pred,v,len+1,visited)); 
  return mx;
}

int max_valid_path(map<int,set<int>>& G, bool (*pred)(int)){
  set<int> visited; // si esta en el set esta visitado, sino no
  int mx = 0; // maximo numero de nodos en el camino
              // (la long del camino es mx-1)
  for(auto p:G) 
    if (pred(p.first)) // por cada nodo que cumple con el
                       // pred, probar iniciar ahi un camino
      // quedarse siempre con el mayor
      mx = max(mx,max_valid_path(G,pred,p.first,1,visited)); 
  return mx-1;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

int main() {
  
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0,h4=0;
  
  cout << "seed: 123" << endl;
  do {
    ev.eval<1>(max_sublist_m,vrbs);
    h1 = ev.evalr<1>(max_sublist_m,seed,vrbs);
    
    ev.eval<2>(remove_max_sibling,vrbs);
    h2 = ev.evalr<2>(remove_max_sibling,seed,vrbs);
    
    ev.eval<3>(max_siblings_sum,vrbs);
    h3 = ev.evalr<3>(max_siblings_sum,seed,vrbs);
    
    ev.eval<4>(max_valid_path,vrbs);
    h4 = ev.evalr<4>(max_valid_path,seed,vrbs);
    
    printf("S=%03d -> H1=%03d H2=%03d H3=%03d H4=%03d\n",
           seed,h1,h2,h3,h4);
    
    cout << endl << "Siguiente seed: ";
  } while (cin>>seed);
  return 0;
  
}
