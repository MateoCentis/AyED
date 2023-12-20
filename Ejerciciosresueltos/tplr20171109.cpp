#define USECHRONO
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>
#include <numeric>
#include "eval.hpp"

using namespace aed;
using namespace std;

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   #sum_sublist:# Implemente la funcion que dada una lista de
   enteros #L# y un entero #S,# encuentre y retorne una sublista
   cuya suma sea S. 

   #discrete_moving_mean:# Implemente la funcion que dada
   una lista de enteros #L# y un entero #w,# retorne una lista
   con los valores de la media movil con ventana fija de
   tamano #w.#

   #d10s:# Implemente la funcion que reciba un AOO #T# y retorne el
   camino  desde la raiz hasta el nodo con la etiqueta 10. 

   #is_cycle:# Implemente una funcion que determine si el
   grafo #G# es un ciclo dirigido o no.

   #existe_subc:# Implementar una funcion que dado un
   conjunto #S# y un valor #n,# determine si existe un
   subconjunto de #S# para el cual la suma de sus elementos
   sea n.

   #replace_btree:# Implemente una funcion que busque los
   nodos que cumplan con la condicion #pred# y los reemplace
   por el primero de sus descendientes que no la cumpla.

   [Tomado en el TPL Recup de 2017-11-09].  
   keywords: arbol binario, arbol orientado, conjunto, lista, programacion funcional

FIN DE DESCRIPCION */

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// sum_sublist (Valido para el TPL 1)
list<int> sum_sublist(list<int>& L, int S){
  list<int> R;
  if(S==0) return R;
  list<int>::iterator it = L.begin();
  while(it!=L.end()){
    int acum = 0;
    auto it2 = it;
    while(it2!=L.end()){
      acum += *it2;
      if(acum==S){
        R.insert(R.begin(),it,++it2);
        return R;
      }
      it2++;
    }
    it++;
  }
  return R;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// discrete_moving_mean (Valido para el TPL 1)
list<int> discrete_moving_mean(list<int>& L, int w){
  list<int> R;
  list<int>::iterator it = L.begin();
  list<int> Laux;
  for(;it!=L.end();it++){
    Laux.push_back(*it);
    if(Laux.size()==w){
      R.push_back(accumulate(Laux.begin(),Laux.end(),0)/w);
      Laux.pop_front();
    }
  }
  return R;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// d10s (Valido para el TPL 2)
list<int> d10s(tree<int> &T, tree<int>::iterator nodo){
  if(*nodo==10){
    return {*nodo};
  }
  tree<int>::iterator c = nodo.lchild();
  while(c!=T.end()){
    list<int> aux = d10s(T,c);
    if(aux.size()){
      aux.push_front(*nodo);
      return aux;
    }
    c++;
  }
  return {};
}

list<int> d10s(tree<int> &T){
	return d10s(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// is_cycle (Valido para el TPL 2)
bool is_cycle(graph_t &G){
  set<int> visited;
  int v = G.begin()->first;
  int first = v;
  while(visited.size()<G.size()){
    if(visited.count(v)) return false;
    visited.insert(v);
    if(G[v].size()!=1) return false;
    v = *(G[v].begin());
  }
  return (v==first);
}


//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// existe_subc (Valido para el TPL 3)
bool existe_subc(set<int>S,int n, set<int> S2){
  if(S.empty()){
    return (accumulate(S2.begin(),S2.end(),0)==n);
  }
  int x = *S.begin();
  S.erase(x);
  if(existe_subc(S,n,S2)) return true;
  S2.insert(x);
  if(existe_subc(S,n,S2)) return true;
  return false;
}

bool existe_subc(set<int> &S, int n) {
  return existe_subc(S,n,{});
}


//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// replace_btree (Valido para el TPL 3)

// Funcion auxiliar.
// Encuentra el primer nodo que no cumple el pred
btree<int>::iterator findX(btree<int>&T,btree<int>::iterator it,bt_fun_t f){
  if(it==T.end())
    return it;
  if(!f(*it))
    return it;
  btree<int>::iterator itl,itr;
  itl = findX(T,it.left(),f);
  itr = findX(T,it.right(),f);
  if(itl != T.end())
    return itl;
  else return itr;
}

void replaceBtree(btree<int>&T,btree<int>::iterator it,bt_fun_t f){
  if(it==T.end())
    return;
  if(f(*it)){
    btree<int>::iterator aux = findX(T,it,f);
    if(aux != T.end()){
      int remp = *aux;
      *it = remp;
    }else it = T.erase(it);
  }
  if(it != T.end()){
    replaceBtree(T,it.left(),f);
    replaceBtree(T,it.right(),f);
  }
}

void replaceBtree(btree<int>&T,bt_fun_t f){
  replaceBtree(T,T.begin(),f);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0,h4,h5,h6;
  
  do {
    ev.eval<1>(sum_sublist,vrbs);
    h1 = ev.evalr<1>(sum_sublist,seed,vrbs);
    
    ev.eval<2>(discrete_moving_mean,vrbs);
    h2 = ev.evalr<2>(discrete_moving_mean,seed,vrbs);

    ev.eval<3>(d10s,vrbs);
    h3 = ev.evalr<3>(d10s,seed,vrbs);
    
    ev.eval<4>(is_cycle,vrbs);
    h4 = ev.evalr<4>(is_cycle,seed,vrbs);

    ev.eval<5>(existe_subc,vrbs);
    h5 = ev.evalr<5>(existe_subc,seed,vrbs);
    
    //ev.eval<6>(replace_btree,vrbs);
    //h6 = ev.evalr<6>(replace_btree,seed,vrbs);
    
    printf("S=%03d  ->  H1=%03d H2=%03d  H3=%03d H4=%03d  H5=%03d H6=%03d\n",
           seed,h1,h2,h3,h4,h5,h6);
    printf("\n\nIngrese un valor para la semilla:");
  } while (cin>>seed);
  
  return 0;
}
