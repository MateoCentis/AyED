#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   #fill-oprev:# Dado un AOO #T# y una lista #L# reemplaza
   los nodos de #T# con los valores de #L#. Si hay mas
   nodos en #T# que valores en #L# entonces los nodos
   restantes de #T# quedan en su valor
   original. Reciprocamente, si hay mas valores en #L# que
   en #T# los valores restantes de #L# son descartados. 

   #a-lo-ancho:# Implemente una funcion que reciba un grafo
   no dirigido #G# y genere un arbol de expansion #T# de
   la componente conexa a la que pertenece el primer
   vertice del grafo (que sera la raiz del arbol), a
   partir del algoritmo de busqueda a lo ancho.

   #intersect-map:# Implemente una funcion que, a partir de
   las correspondencias A# y #B# construye una
   correspondencia #C# de manera que las claves de #C# son
   la interseccion de las claves de #A# y B# y para cada
   clave #k# en #C# la imagen #C[k]# es la interseccion
   ordenada de las listas ordenadas #A[k]# y B[k]#. Si
   esta interseccion de listas es nula, no debe incluirse
   la entrada de clave #k# en #C#.

   [Tomado en el Trabajo Practico de Laboratorio Nro 2
   (TPL2) de 2019-10-10].
   keywords: arbol orientado, correspondencia

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

void fill_ordprev(tree<int> &T,tree<int>::iterator n,
                  list<int> &L) {
  // Si el arbol esta vacio o la lista esta vacia no hay que
  // hacer nada
  if (n==T.end()) return;
  if (L.empty()) return;
  // Extrae el primer elemento de la lista y pisa el valor
  // del nodo
  *n = L.front();
  // Hay que extraer el elemento de la lista (en este caso
  // es destructivo sobre la lista). Si no la otra
  // posibilidad seria tener un iterador en la lista. 
  L.pop_front();
  // Aplica recursivamente a los hijos
  auto c = n.lchild();
  while (c!=T.end()) fill_ordprev(T,c++,L);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void fill_ordprev(tree<int> &T,list<int> &L) {
  fill_ordprev(T,T.begin(),L);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Lo mismo que fill_ordprev, pero llenando en orden posterior. 
void fill_ordpost(tree<int> &T,tree<int>::iterator n,
                  list<int> &L) {
  if (n==T.end()) return;
  auto c = n.lchild();
  while (c!=T.end()) fill_ordpost(T,c++,L);
  if (L.empty()) return;
  *n = L.front();
  L.pop_front();
}

void fill_ordpost(tree<int> &T,list<int> &L) {
  fill_ordpost(T,T.begin(),L);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void a_lo_ancho(graph& G, tree<char>& T){
  typedef tree<char>::iterator node;
  // Conjunto de nodos que ya fueron visitados
  map<char,bool> visitados;
  // En cada iteracion toma los nodos de la capa actual
  // "current layer", recorre sus adyacencias y las inserta
  // en los hijos. Va llenando listas que son la siguiente
  // capa (next layer). Por cada capa mantenemos una lista
  // de valores y una lista de nodos en el arbol. 
  list<char> nextLayer;
  list<char> currLayer;
  list<node> nextLayerTree;
  list<node> currLayerTree;

  // inicializa poniendo la primera clave del grafo como
  // raiz del arbol
  currLayer.push_back(G.begin()->first);
  currLayerTree.push_back(T.insert(T.begin(),G.begin()->first));
  visitados[G.begin()->first];

  // En cada iteracion de este lazo se agrega una capa.  El
  // algoritmo se termina cuando no hay mas nodos en una
  // capa. OJO que si el grafo es disconexo entonces solo
  // inserta en el arbol la componente conexa conectada a la
  // primera clave del grafo.
  while(currLayer.size()){
    // Limpiar los contenedores para la siguiente capa
    nextLayer.clear();
    nextLayerTree.clear();

    // Itera sobre los nodos de la capa actual
    auto itLayer = currLayerTree.begin();
    for(int n:currLayer) {
      // n es el char, it es el nodo correspondiente en la
      // capa
      auto it = *itLayer;
      it = it.lchild();
      // Vecinos del nodo
      auto &vecinos = G[n];
      for(auto &v : vecinos){
        if(visitados.find(v)==visitados.end()){
          // Los nodos no visitados los agrega a las listas
          // (ambas cosas, el char y el iterador)
          nextLayer.push_back(v);
          it = T.insert(it,v);
          nextLayerTree.push_back(it);
          visitados[v];
          it++;
        }
      }
      // incrementa el iterador en la lista de iterators
      itLayer++;
    }
    // Swapea los contenedores de los niveles
    currLayer = nextLayer;
    currLayerTree = nextLayerTree;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void intersect_map(map<int,list<int>> &A,
                   map<int,list<int>> &B,
                   map<int,list<int>> &C){
  // Recorre las claves de A
  for(auto &p :A){
    auto itB = B.find(p.first);
    if(itB!=B.end()){
      // la clave esta en A y en B
      // LB es una referencia a la lista en B
      auto &LB = itB->second;
      // eA es un elemento de la lista en A 
      for(auto &eA: p.second){
        // Si el elemento esta en LB lo inserta en C
        if(find(LB.begin(),LB.end(),eA)!=LB.end()){
          C[p.first].push_back(eA);
        }
      }
    }
  }    
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {

  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  cout << "seed: 123" << endl;
  do {

    ev.eval<1>(fill_ordprev,vrbs);
    h1 = ev.evalr<1>(fill_ordprev,seed,vrbs);

    ev.eval<2>(a_lo_ancho,vrbs);
    h2 = ev.evalr<2>(a_lo_ancho,seed,vrbs);

    ev.eval<3>(intersect_map,vrbs);
    h3 = ev.evalr<3>(intersect_map,seed,vrbs);
    
    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    cout << endl << "Siguiente seed: ";
  } while (cin>>seed);

  return 0;
  
}

