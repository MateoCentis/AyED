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

   #prom-nivel:# Dado un arbol #T,# calcular una lista de
   reales #P,# donde el elemento #l# de la lista sea el
   promedio de los nodos del arbol de nivel #l.#

   #es-circuito:# Dado un grafo #G# representado por un map
   de nodos a lista de vecinos, y una lista de nodos #L,#
   escriba una funcion que determine si la secuencia de
   nodos #L# es un camino dentro del grafo #G.#

   #map-graph:# Dado un grafo #Gin# y una permutacion #P,#
   encontrar el grafo #Gout# que resulta de permutar los
   vertices de #Gin# por la pertmutacion #P,# es decir si la
   arista #(j,k)# esta en #Gin,# entonces la arista
   #(P[j],P[k])# debe estar en #Gout.#

   [Tomado en el TPL2 de 2017-10-12].  
   keywords: correspondencia, arbol orientado

FIN DE DESCRIPCION */

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Funcion recursiva, acumula en N y S por nivel la cantidad
// de nodos y suma de sus elementos
void prom_nivel(tree<int> &T, tree<int>::iterator it, 
                int level, map<int,int> &N, map<int,int> &S) {
  if (it==T.end()) return;
  S[level]+=*it; N[level]++; level++;
  for(auto it2=it.lchild();it2!=T.end();++it2)
    prom_nivel(T,it2,level,N,S);
}

void prom_nivel(tree<int> &T, list<float> &P) {
  if (T.begin()==T.end()) return;
  // Llama a la funcion auxiliar y calcula las sumas y
  // numero de nodos
  map<int,int> N;
  map<int,int> S;
  prom_nivel(T,T.begin(),0,N,S);
  // Va calculando el promedio
  for(auto p:N) {
    P.push_back(float(S[p.first])/p.second);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Retorna `true' si x esta en `L'
bool contiene(list<int>&L,int x){
  for(auto y : L)
    if(y == x) return true;
  return false;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool es_circuito(map<int,list<int>>&G,list<int>&L){
  // Recorre los elementos de L
  list<int>::iterator it = L.begin();
  while(it!=L.end()){
    // En cada iteracion it y ++it son dos vertices
    // consecutivos en L
    map<int,list<int>>::iterator itg = G.find(*it);
    ++it;
    // Es el siguiente (o begin()) si
    // llegamos al final
    auto z = (it==L.end()?*L.begin():*it);
    if(!contiene(itg->second,z)) return false;
  }
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void unique(vector<int> &v) {
  // Using a map (could be a set)
  map<int,int> M;
  for (auto &x : v) M[x] = 1; // 1 or whatever
  v.clear();
  for (const auto &q : M) v.push_back(q.first);
  sort(v.begin(),v.end()); // No hace falta...
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void map_graph(map<int,vector<int> > &Gin,map<int,int> &P,
               map<int,vector<int> > &Gout) {
  Gout.clear();
  for (auto const &q : Gin) {
    int j = q.first;
    const vector<int> &ngbrs = q.second;
    for (auto const &k : ngbrs) {
      // (j,k) es la arista en Gin
      int Pj=P[j], Pk=P[k];
      Gout[Pj].push_back(Pk);
    }
  }
  // Ordena los ngbrs de Gout y elimina repetidos
  for (auto & q : Gout) unique(q.second); 
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  // User typical call
  ev.eval<1>(prom_nivel,vrbs);
  h1 = ev.evalr<1>(prom_nivel,seed,vrbs);

  ev.eval<2>(es_circuito,vrbs);
  h2 = ev.evalr<2>(es_circuito,seed,vrbs);

  ev.eval<3>(map_graph,vrbs);
  h3 = ev.evalr<3>(map_graph,seed,vrbs);

  printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
         seed,h1,h2,h3);
  
  return 0;
}
