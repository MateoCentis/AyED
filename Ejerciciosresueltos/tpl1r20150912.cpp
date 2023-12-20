#include "eval.hpp"
#include <climits>
#include <cstdlib>
#include <stack>

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   #iscomb:# Dado un vector de listas #VL# y una lista
   #L#, determinar si #L# es una combinacion de las listas de #VL#
   en alguna permutacion dada. Cada una de las #VL[j]# debe aparecer
   una y solo una vez en #L#. 

   #max-sublist:# Escribir una funcion
   que recibe una lista de enteros y encuentra y retorna la
   sublista consecutiva que obtenga la mayor suma entre todos
   sus elementos. 

   #mergesort:# Programar una funcion void
   #mergesort(list<int> &L);# que ordane una lista #L#
   desordenada y la ordene en forma ascendente mediante una
   estrategia recursiva.

   [Tomado en el Recup Trabajo Practico de Laboratorio Nro 1
   (TPL1R) de 2015-09-12].  
   keywords: lista

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

list<int> mochila(list<int> &P,int K) {
  list<int> P1, M;
  if (K==0 || P.empty()) return M;

  // a0 es el primer elemento
  int a0 = P.front();
  // P1 es P sin el primer elemento
  P1 = P;
  P1.erase(P1.begin());

  list<int> M_cona0, M_sina0;
  M_sina0 = mochila(P1,K);
  if (a0>K) return M_sina0;
  
  M_cona0 = mochila(P1,K-a0);
  M_cona0.push_back(a0);

  if (M_sina0.size()>M_cona0.size()) 
    return M_sina0;
  else return M_cona0;
}

// busco el elemento x en L
bool encuentra_x (list <int> &L, int x) {
  list <int>::iterator it = L.begin();
  while (it != L.end()) if (*it++ == x) return true;
  return false;
}

bool enunosolo(list<list <int> > &LL, list<int> &L) {
  list <int>::iterator itL = L.begin();
  while (itL != L.end()) {
    list <list<int> >::iterator itLL = LL.begin();
    int count=0;
    while (itLL != LL.end()) {
      count += encuentra_x(*itLL++,*itL);
      if (count>1) return false;
    }
    if (count!=1) return false;
    itL++;
  }
  return true;
}

int ppt(list<int> &H, int n) {
  if (int(H.size())<n) return 0;

  list<int>::iterator q = H.end(); q--;
  list<int> aux;
  for (int j=0; j<n; j++)
    aux.insert(aux.begin(),*q--);
  list<int>::iterator p = H.begin();
  int nextplay = 0;
  while (p!=H.end()) {
    list<int>::iterator p2 = p++, q= aux.begin();
    while (p2!=H.end() && q!=aux.end() && *p2==*q) {
      p2++; q++;
    }
    if (q!=aux.end() || p2==H.end()) continue;
    nextplay = *p2;
  }
  return nextplay;
}

// VERSION 2
// Iterando al reves (desde end hacia begin)
int ppt2(list<int> &H, int n) {
  if (int(H.size())<n) return 0;

  list<int>::iterator q = H.end(); q--;
  list<int> aux;
  for (int j=0; j<n; j++)
    aux.insert(aux.begin(),*q--);
  list<int>::iterator p = H.begin();

  if (H.empty()) return 0;
  
  p = H.end(); p--;
  while (1) {
    list<int>::iterator p2 = p, q= aux.begin();
    while (p2!=H.end() && q!=aux.end() && *p2==*q) {
      p2++; q++;
    }
    if (q==aux.end() && p2!=H.end()) return *p2;
    if (p==H.begin()) return 0;
    p--;
  }
  return 0;
}

// VERSION 3
// Iterando al reves (desde end hacia begin)
// pero con reverse_iterator. OJO que los reverse_iterator
// p++ avanza al reves (hacia begin()). 
int ppt3(list<int> &H, int n) {
  if (int(H.size())<n) return 0;

  list<int>::reverse_iterator p = H.rbegin();
  list<int> aux;
  for (int j=0; j<n; j++)
    aux.insert(aux.begin(),*p++);

  p = H.rbegin();  
  while (p!=H.rend()) {
    // Para convertir de reverse_iterator a iterator
    // hay que usar el metodo `base()'
    list<int>::iterator p2=p.base(), q=aux.begin();
    // Al convertir el reverse_iterator a iterator
    // se corre en uno hacia end(), por eso hay que
    // hacer este --
    p2--;
    while (p2!=H.end() && q!=aux.end() && *p2==*q) {
      p2++; q++;
    }
    if (q==aux.end() && p2!=H.end()) return *p2;
    p++; 
  }
  return 0;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  ev.eval1(mochila,vrbs);
  h1 = ev.evalr1(mochila,seed,vrbs);

  ev.eval2(enunosolo,vrbs);
  h2 = ev.evalr2(enunosolo,seed,vrbs);


#define PPT ppt3
  ev.eval3(PPT,vrbs);
  h3 = ev.evalr3(PPT,seed,vrbs);

  // para S=123 -> H1=333 H2=357 H3=340
  printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
         seed,h1,h2,h3);

  ev.eval3(ppt3,vrbs);
  h3 = ev.evalr3(ppt3,seed,vrbs);
  printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
         seed,h1,h2,h3);

  return 0;
}
