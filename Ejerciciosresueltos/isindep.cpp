/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   escribir un predicado 
   #bool is_indep(map<int, set<int> >&G,set<int>&S);#
   que determina si #S# es un conjunto
   _independiente_ de #G#. Se dice que #S# es un conjunto
   independiente de #G#, si para cada par de vertices de #S#, NO existe una
   arista que los une en #G#.
   [Tomado en tercer parcial 2011-11-24].
   keywords: conjunto, grafo

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------

#include <cstdio>
#include <cassert>

#include <list>
#include <map>
#include <set>
#include <string>

using namespace std;

typedef map<int, set<int> > graph_t;
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool is_indep(graph_t &G,set<int> &S) {
  set<int>::iterator q = S.begin(),r;
  // chequea que todos los indices en S
  // sean relamente nodos del grafo (o sea claves del map)
  while (q!=S.end()) 
    if (G.find(*q++)==G.end()) 
      return false;

  q = S.begin();
  // q itera sobre los vertices incluidos en S
  while (q!=S.end()) {
    // `qngbrs' es el conjunto de vertices adyacentes a q
    set<int> &qngbrs = G[*q];
    // r itera sobre los restantes vertices de S (a partir
    // del siguiente a q).
    // Chequea que r no este entre los vecinos de q
    r=q; r++;
    while (r!=S.end()) 
      if (qngbrs.find(*r++)!=qngbrs.end()) return false;
    q++;
  }
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int modulo(int n,int m) {
  int r = n%m;
  if (r<0) r+= m;
  return r;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  // simple 1D graph
  // Crea un simplisimo grafo 1D con N vertices
  // en forma de circulo
  for (int N=5; N<10; N++) {
    graph_t G;
    for (int j=0; j<N; j++) {
      set<int> &ngbrs = G[j];
      ngbrs.insert(modulo(j+1,N));
      ngbrs.insert(modulo(j-1,N));
    }
    
    // Cuando N es par los pares y los impares
    // son independientes. Cuando N es impar los
    // pares NO son independientes y los impares si
    for (int start=0; start<2; start++) {
      // start=0 -> mira el conjunto de los PARES
      // start=1 -> mira el conjunto de los IMPARES
      set<int> S;
      for (int j=start; j<N; j+=2) S.insert(j);
      
      int calc = is_indep(G,S);
      int correct = N%2==0 || start==1;
      printf("N par %d, S=%s, es independiente? "
             "calculado %d, correcto %d, OK? %d\n",
             N,(start? "impares" : "pares  "),calc,correct,calc==correct);
    }
  }
  return 0;
}
