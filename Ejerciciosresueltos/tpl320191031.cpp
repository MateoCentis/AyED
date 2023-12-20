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

   #spaceship:# El operador de comparacion de 3 vias
   (three-way comparison operator), tambien llamado
   "operador nave espacial" (spaceship operator) (ya que en
   lenguajes como Perl o C++ (en el estandar C++20) se
   sobrecargan con el operador #<=># se define de la
   siguiente manera: #spaceship(a,b)# retorna 1 si #a>b#, 0
   si #a==b# y -1 si #a<b#. Escribir una funcion
   #spaceship(T1,T2)# para arboles binarios. 

   #mkhuffman:# Implemente una funcion  
   #T=makeHuffmannTree(bosque);# que recibe una lista de 
   arboles y porbabilidades y aplica el algoritmo de Huffmann para 
   retornar el arbol con la codificacion optima resultante.

   #mincostsets:#   Dado un conjunto universal #U# de #n# elementos y una lista
  de subconjuntos de #U# denominada
  #S = (S1, S2,...,Sm)#  en donde cada subconjunto #Si# tiene
  un costo asociado, se pide implementar una funcion
  #mincostsets(U,S,costos)# que retorna el costo de 
  la sublista de #S# de costo minimo, y que cubra todos los 
  elementos de !+U+. 

   [Tomado en el Trabajo Practico de Laboratorio Nro 3
   (TPL3) de 2019-10-31]
   keywords: arbol binario, conjunto

FIN DE DESCRIPCION */


using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
typedef btree<int> ::iterator bnode_t;
int spaceship(btree<int> &T1,bnode_t n1,
              btree<int> &T2,bnode_t n2) {
  if (n1==T1.end() && n2==T2.end()) return 0;
  if (n1==T1.end() && n2!=T2.end()) return -1;
  if (n1!=T1.end() && n2==T2.end()) return +1;

  int rv;
  rv = *n1-*n2; if (rv) return rv;
  rv = spaceship(T1,n1.left(),T2,n2.left()); if (rv) return rv;
  rv = spaceship(T1,n1.right(),T2,n2.right()); if (rv) return rv;
  return 0;
}

int spaceship(btree<int> &T1,btree<int> &T2) {
  int rv = spaceship(T1,T1.begin(),T2,T2.begin());
  return rv>0? 1 : rv<0? -1 : 0;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Funcion auxiliar provista por la catedra
list<pair<btree<char>,float>>::iterator
getMin(list<pair<btree<char>,float>> & bosque){
  auto it = bosque.begin();
  list<pair<btree<char>,float>>::iterator itMini = it;
  it++;
  while(it!=bosque.end()){
    if(it->second<itMini->second){
      itMini = it;
    }
    it++;
  }
  return itMini;    
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
btree<char> makeHuffmanTree(list<pair<btree<char>,float>> & bosque){
  while(bosque.size()>1){   	 
    auto it = getMin(bosque);
    btree<char> Tl;
    auto aux1 = it->first.begin();
    Tl.splice(Tl.begin(),aux1);
    int w = it->second;
    bosque.erase(it);
    
    it = getMin(bosque);
    btree<char> Tr;
    auto aux2 = it->first.begin();
    Tr.splice(Tr.begin(),aux2);
    w += it->second;
    bosque.erase(it);
    
    btree<char> Tnew; Tnew.insert(Tnew.begin(),'.');
    aux1 = Tl.begin();
    Tnew.splice(Tnew.begin().left(),aux1);
    aux2 = Tr.begin();
    Tnew.splice(Tnew.begin().right(),aux2);
    
    bosque.push_back({Tnew,w});
  }
  return bosque.begin()->first;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int minCostSets(set<int>& U, vector<set<int>>& S,
                map<set<int>, int>& costos, list<set<int>>& L,
                int pos) {
  if (U.size() == 0) {
    int costoAcum = 0;
    for (set<int> s: L) {
      costoAcum = costoAcum + costos[s]; //costos.find(s)->second;
    }
    return costoAcum;
  }
	
  if (pos < 0) {
    return INT_MAX;
  }
	
  set<int> Ucopia(U);
  list<set<int>> Laux(L);
  L.push_back(S[pos]);
  for (int elem: S[pos]) {
    U.erase(elem);
  }
	
  int cost1 = minCostSets(U, S, costos, L, pos-1);
  int cost2 = minCostSets(Ucopia, S, costos, Laux, pos-1);

  if (cost1<cost2) return cost1;
  else { L=Laux; return cost2; }
  // return min(cost1, cost2);
}

int minCostSets(set<int>& U, vector<set<int>>& S,
                map<set<int>, int>& costos) {
  list<set<int>> L;
  return minCostSets(U,S,costos,L,S.size()-1);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Otra solucion posible
int minCostSets2(set<int>& U, vector<set<int>> S,
                map<set<int>, int>& costos,
                set<int> W,int costoW) {
  if (S.empty()) {
    // Si W cubre a U entonces el costo es el costo de todos
    // las listas incluidas en W, si no ponemos un numero muy grande (INT_MAX)
    set<int> tmp;
    set_difference(U,W,tmp);
    return tmp.empty() ? costoW : INT_MAX;
  }

  set<int> S0 = *S.begin();
  S.erase(S.begin());

  // Costo SIN INCLUIR a S0 en W
  int costo_con_S0, costo_sin_S0;
  costo_sin_S0 = minCostSets2(U,S,costos,W,costoW);

  // Costo INCLUYENDO a S0 en W
  set<int> tmp;
  set_union(W,S0,tmp);
  W.swap(tmp);
  costoW += costos[S0];
  costo_con_S0 = minCostSets2(U,S,costos,W,costoW);
  return costo_con_S0<costo_sin_S0? costo_con_S0 : costo_sin_S0;
}

int minCostSets2(set<int>& U, vector<set<int>> &S_,map<set<int>, int>& costos) {
  set<int> W;
  int costoW = 0;
  vector<set<int>> S=S_;
  return minCostSets2(U,S,costos,W,costoW);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {

  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  cout << "seed: 123" << endl;
  do {
    ev.eval<1>(spaceship,vrbs);
    h1 = ev.evalr<1>(spaceship,seed,vrbs);
    
    ev.eval<2>(makeHuffmanTree,vrbs);
    h2 = ev.evalr<2>(makeHuffmanTree,seed,vrbs);
    
    ev.eval<3>(minCostSets,vrbs);
    h3 = ev.evalr<3>(minCostSets,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    cout << endl << "Siguiente seed: ";
  } while (cin>>seed);

  return 0;
  
}
