/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
  // Dada una correspondencia #map<string,string> M#, y una clave #k0#, se
  // desea extraer todos los pares de asignacion correspondientes a claves
  // conectadas con #k0#. 
   [Tomado en primer parcial 2011-09-13].
   keywords: correspondencia

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------

#include <cstdio>
#include <cassert>
#include <cmath>

#include <map>
#include <algorithm>

#include "./util.h"

using namespace std;

// Lo hacemos templatizado
template<typename T>
void submap(map<T,T> &M1,map<T,T> &M2,T k0) {
  T k1;
  while (1) {
    // Si k0 no es clave de M1 el proceso termino
    typename map<T,T>::iterator q = M1.find(k0);
    if (q==M1.end()) break;
    // k1=M[k0], si k1 ya esta en M2 tambien termino
    if (M2.find(k0)!=M2.end()) break;
    k1 = M1[k0];
    // Agrega la asignacion k0->k1 en M2
    M2[k0] = k1;
    // Pasa a la siguiente clave k1
    k0 = k1;
  }
}

// Funcion auxiliar que imprime un map
void printmap(map<int,int> &M) {
  map<int,int>::iterator q = M.begin();
  while (q!=M.end()) {
    printf("(%d->%d) ",q->first,q->second);
    q++;
  }
  printf("\n");
}

int main() {
  // Genera un map aleatorio de [0,N) en [0,N)
  map<int,int> M1,M2;
  int N = 20;
  for (int j=0; j<N; j++) {
    M1[rand()%N] = rand()%N;
  }
  printf("M1: ");
  printmap(M1);

  // Extrae el submap para las claves a partir de cada uno de los
  // j en [0,N)
  for (int j=0; j<N; j++) {
    map<int,int> M2;
    submap(M1,M2,j);
    printf("submap(M1,M2,%d): ",j);
    printmap(M2);
  }
  return 0;
}
