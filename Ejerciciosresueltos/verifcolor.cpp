/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dado un grafo #map<int, set<int> >G# y una coloracion
   #map<int,string> C# determinar si #C# es una coloracion valida, es
   decir si dados dos vertices adyacentes #x#, #y# de #G# sus colores
   son diferentes. 
   [Tomado en tercer parcial 2011-11-24].
   keywords: conjunto, grafo

  FIN DE DESCRIPCION */
#include <cstdio>
#include <cassert>

#include <map>
#include <set>
#include <string>

using namespace std;

typedef map<int, set<int> > graph_t;
bool verif_color(graph_t &G,map<int,string> &C) {
  // q itera sobre los vertices del grafo
  graph_t::iterator q = G.begin();
  while (q!=G.end()) {
    int vrtx = q->first;
    assert(C.find(vrtx)!=C.end());
    // qcolor es el color de q
    string &qcolor = C[vrtx];
    // Vecinos de q
    set<int> &ngbrs = q->second;
    // r itera sobre los vecinos de q
    set<int>::iterator r = ngbrs.begin();
    while (r!=ngbrs.end()) {
      assert(C.find(*r)!=C.end());
      // rcolor es el color de r
      string &rcolor = C[*r];
      // Chequea que no tengan el mismo color
      if (qcolor==rcolor) return false;
      r++;
    }
    q++;
  }
  return true;
}

int modulo(int n,int m) {
  int r = n%m;
  if (r<0) r+= m;
  return r;
}

int main() {
  for (int N=10; N<=15; N++) {
    // Crea un simplisimo grafo 1D con N vertices
    // en forma de circulo
    graph_t G;
    for (int j=0; j<N; j++) {
      set<int> &ngbrs = G[j];
      ngbrs.insert(modulo(j+1,N));
      ngbrs.insert(modulo(j-1,N));
    }

    // Asigna rojo a los impares y negro a los pares
    map<int,string> C;
    for (int j=0; j<N; j++) 
      C[j] = (modulo(j,2) ? "red" : "black");
  
    // Chequea la coloracion, deberia dar
    // que es valida para N par
    printf("N %d, valid coloring? %d\n",N,verif_color(G,C));
  }
  return 0;
}
