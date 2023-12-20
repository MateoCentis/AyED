/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dados un Grafo Dirigido Aciclico (DAG) #G=(V,E)# obtener el
   DAG #G'=(V,E')# tal que si #(v,w)\in E# entonces #(w,v)\in E'#. (Es
   decir, equivale a invertir el sentido de las flechas en el dibujo).

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
void reverse_dag(const graph_t &Gin,graph_t &Gout) {
  // Recorre los vertices `q' de Gin
  graph_t::const_iterator q = Gin.begin();
  while (q!=Gin.end()) {
    int v = q->first;
    // Recorre los vecinos `r' de `q'
    const set<int> &ngbrs = q->second;
    set<int>::const_iterator r = ngbrs.begin();
    while (r!=ngbrs.end()) 
      // La arista de Gin es(*q,*r) por lo tanto
      // insertamos (*r,*q) en `Gout'
      Gout[*r++].insert(v);
    q++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void read_graph_directed(graph_t &G, const int *g) {
  // Lee un grafo de un int[]. Se insertan las aristas como
  // pares de enteros y termina con un -1. Asume que no hay
  // nodos desconexos (sin ninguna arista) y que los vertices
  // son >=0
  const int *p = g;
  while (*p>=0) {
    int 
      v1 = *p++,
      v2 = *p++;
    G[v1].insert(v2);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void print_graph(const graph_t &G) {
  // Imprime el grafo
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
int main() {
  graph_t G4,G5;

  // Genera el grafo del ejemplo
  int g4[] = {0,1, 0,2, 2,1, 2,3, 1,3, 1,5, 1,4, 
              5,6, 6,7, 3,4, 4,7, 3,7, -1};
  read_graph_directed(G4,g4);
  printf("G4: -------- \n");
  print_graph(G4);
  
  reverse_dag(G4,G5);
  printf("G5: -------- \n");
  print_graph(G5);

  return 0;
}
