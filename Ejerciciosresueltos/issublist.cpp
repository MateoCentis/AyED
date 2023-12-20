/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Escribir una funcion #bool# #is_sublist(list<int> &L1,# #list<int> &L1,#
   #list<list<int>::iterator> &iters);# que dadas dos listas
   #list<int> L1,L2# determina si la lista #L2# es una sublista de
   #L1#, es decir que #L2# se puede obtener a partir de #L1# solo
   eliminando algunos de sus elementos.
   [Tomado en primer parcial 2011-09-13].
   keywords: lista

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------

#include <cstdio>
#include <cassert>
#include <cmath>

#include <list>
#include <vector>
#include <map>
#include <algorithm>

#include "./util.h"

using namespace std;

// Funcion auxiliar para generar ejemplos.  Desordena
// aleatoriamente una lista, recursivamente.  Primero la
// descompone en dos listas L1, L2 de tamano n1, n2 aprox
// n/2, las desordena (con una llamada recusiva) y despues
// va tomando elementos de L1 y L2 con probabilidad n1 y n2
// respectivamente. Las probabilidades se van ajustando a
// medida que las longitudes de L1 y L2 van disminuyendo
void random_shuffle(list<int> &L) {
int n = int(L.size());
  // Corta recursion si es necesario
  if (n<2) return;
  // Calcula tamano inicial de las sublistas
  int n1 = n/2, n2= n-n1;
  // Split de L en L1, L2
  list<int> L1,L2;
  for (int j=0; j<n1; j++) {
    L1.push_back(L.front());
    L.erase(L.begin());
  }
  for (int j=0; j<n2; j++) {
    L2.push_back(L.front());
    L.erase(L.begin());
  }
  // Aplica recursivamente a L1, L2
  random_shuffle(L1);
  random_shuffle(L2);
  // Va tomando elementos aleatoriamente de L1, L2
  // con prob. proporcional a sus longitudes
  for (int j=0; j<n; j++) {
    int k = rand()%(n1+n2);
    list<int> *sbl_p;
    // sbl_p es un puntero a la L1 o L2 depende de donde se inserte
    if (k<n1) {
      sbl_p = &L1;
      n1--;
    } else {
      sbl_p = &L2;
      n2--;
    }
    // Extrae de L y apendiza en *sbl_p
    L.push_back(sbl_p->front());
    sbl_p->erase(sbl_p->begin());
  }
}

typedef list<int>::iterator iter_t;
bool is_sublist(list<int> &L1, list<int> &L2,list<iter_t> &iters) {
  iter_t p2 = L2.begin(),p1 = L1.begin();
  // p2 recorre L2, vamos viendo si encontramos el elemento *p2 a en L1
  // a partir de la ultima posicion p1
  while (p2!=L2.end()) {
    while (p1!=L1.end()) {
      // SI encuentra el elemento inserta el ITERADOR en `iters'
      // y pasa al siguiente elemento de L2
      if (*p1==*p2) {
        iters.push_back(p1);
        break;
      }
      p1++;
    }
    // Si llega al final de L1 quiere decir que no encontro el *p2
    // entonces ya sabemos que NO es sublista. Antes de salir
    // vaciamos `iters' 
    if (p1==L1.end()) {
      iters.clear();
      return false;
    }
    // *p2 fue encontrado, pasamos al siguiente
    p2++;
  }
  return true;
}

int main() {

  // Probamos con 10 listas aleatorias
  for (int k=0; k<10; k++) {
    list<int> L;
    // Ponemos `N' elementos en un vector auxiliar `v' y lo
    // desordenamos aleatoriamente
    int N=20;
    vector<int> v(N);
    for (int j=0; j<N; j++) v[j] = j;
    random_shuffle(v.begin(),v.end());
    // Ponemos todos los elementos de `v' en `L1' y
    // una fraccion del 50% (aleatoria) en `L2'
    list<int> L1,L2;
    list<iter_t> iters;
    for (int j=0; j<N; j++) {
      L1.push_back(v[j]);
      if (rand()%2) L2.push_back(v[j]);
    }
    
    // A esta altura L2 es una sublista de L1, 
    // pero ahora tira la moneda y en 50% de los casos desordena L2.
    // O sea que si shuffle==1 entonces L2 NO deberia ser sublista
    // y viceversa, si shuffle==0 SI debe ser sublista.
    // (OJO que en realidad existe una probabilidad MUY BAJA de que el shuffle
    // no haga nada.)
    int shuffle = rand()%2;
    if (shuffle) random_shuffle(L2);
    printf("================\nL1: ");
    printl(L1);
    printf("L2: ");
    printl(L2);
  
    int issbl = is_sublist(L1,L2,iters);
    printf("Is L2 sublist of L1? %d, shuffle %d\n",issbl,shuffle);
    if (issbl) {
      assert(L2.size()==iters.size());
      iter_t p = L2.begin();
      list<iter_t>::iterator q = iters.begin();
      while (p!=L2.end()) assert(*p++ == **q++);
    }
    // Hace chequeos
    if (!shuffle && !issbl) 
      printf("ERROR: L2 no fue mezclada y sin embargo no es sublista\n");
    if (shuffle && issbl) 
      printf("PROBABLE ERROR: L2 fue mezclada, pero es sublista (OJO puede estar OK!!)\n");
  }
  return 0;
}
