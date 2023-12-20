/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dados un Grafo Dirigido Aciclico (DAG) #G=(V,E)# y un
   subconjunto de vertices #W\subseteq V#, determinar el conjunto
   $D\subseteq V$ de *descendientes* de #W#, es decir #d\in D# si
   y solo si existe un camino que va de algun nodo #w\in W# a #d#. 

   [Tomado en el 3er parcial de 2012-11-22].  
   keywords: conjunto, correspondencia

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------

#include <cstdio>
#include <cassert>
#include <cmath>

#include <map>
#include <set>

#include "./util.h"

using namespace std;

typedef map<int, set<int> > graph_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void dag_desc(graph_t &G,set<int> &W, set<int> &D) {
  // El frente que avanza es guardado en el conjunto `front'
  set<int> front = W;
  // Inicializa el conjunto de descendientes como el
  // la fuente W
  D = W;
  while (!front.empty()) {
    // Toma un vertice `v' del frente
    int v = *front.begin();
    front.erase(v);
    // Lo pone en el conjunto de descendientes
    D.insert(v);
    // Recorre los vecinos `r' de `v'
    set<int> &ngbrs = G[v];
    set<int>::iterator r = ngbrs.begin();
    while (r!=ngbrs.end()) {
      // Si `r' no fue visitado agregarlo al frente
      if (D.find(*r)==D.end())
        front.insert(*r);
      r++;
    }
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Imprime el grafo
void print_graph(const graph_t &G) {
  graph_t::const_iterator q = G.begin();
  while (q!=G.end()) {
    printf("%d -> {",q->first);
    const set<int> &ngbrs = q->second;
    set<int>::const_iterator r = ngbrs.begin();
    while (r!=ngbrs.end()) 
      printf("%d ",*r++);
    printf("}\n");
    q++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Lee un grafo de un int[]. Se insertan las aristas como
// pares de enteros y termina con un -1. Asume que no hay
// nodos desconexos (sin ninguna arista) y que los vertices
// son >=0
void read_graph_directed(graph_t &G, const int *g) {
  const int *p = g;
  while (*p>=0) {
    int 
      v1 = *p++,
      v2 = *p++;
    G[v1].insert(v2);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  graph_t G4,G5;

  // Crea el grafo del ejemplo en el parcial
  int g4[] = {0,1, 0,2, 2,1, 2,3, 1,3, 1,5, 
              1,4, 5,6, 6,7, 3,4, 4,7, 3,7, -1};
  read_graph_directed(G4,g4);
  printf("G4: -------- \n");
  print_graph(G4);

  set<int> W,D;
  W.insert(5);
  W.insert(3);

  dag_desc(G4,W,D);
  printf("D: {");
  set<int>::iterator q = D.begin();
  while (q!=D.end()) {
    printf("%d ",*q);
    q++;
  }
  printf("}\n");
  
  return 0;
}
