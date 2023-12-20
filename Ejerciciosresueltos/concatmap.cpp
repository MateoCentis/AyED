//__INSERT_LICENSE__
// $Id$

#include <cstdio>
#include <cstdlib>
#include <list>
#include <map>
#include "./util.h"

using namespace std;

/* COMIENZO DE DESCRIPCION
   
   __USE_WIKI__
   Escribir una funci\'on 
   #void concat_map(map<int,list<int> >& M, list<int>& L);# tal que 
   reemplaza los elementos de #L# por su imagen en #M#. Si un
   elemento de #L# no es clave de #M# entonces se asume que su imagen
   es la lista vac\'\i{}a.
   [Tomado en el primer parcial del cursado 2010, 2010-09-14.]
   keywords: lista, correspondencia
   
   FIN DE DESCRIPCION */
// -------------------------------------------------------------------

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void concat_map(map<int,list<int> >& M, list<int>& L) {
  // `p' recorre la lista
  list<int>::iterator p=L.begin();
  while (p!=L.end()) {
    // Toma la clave en una variable auxiliar `k'
    // y elimina el elemento
    int k = *p;
    p = L.erase(p);
    // Busca si hay una entrada en el map
    map<int, list<int> >::iterator q = M.find(k);
    // Si la entrada esta inserta la lista
    if (q!=M.end()) {
      // L2 es una ref a la lista en el map
      list<int> &L2 = q->second;
      list<int>::iterator r = L2.begin();
      while (r!=L2.end()) {
        // inserta en la posicion `p' que quedo en `L'
        p = L.insert(p,*r++);
        p++;
      }
    }
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  // Genera un map con MAPSZ claves en [0,NK)
  // LSZ es el tamano en promedio de las listas
  // Los elementos de la lista estaen en [0,NELEM)
  int NK = 15, MAPSZ=10, LSZ=3, NELEM=5;
  for (int j=0; j<5; j++) {
    printf("\n\n----------------\n");
    map<int,list<int> > M;
    for (int j=0; j<MAPSZ; j++) {
      int key = rand()%NK;
      // Inserta la clave y se queda con una ref
      // a la lista
      list<int> &L = M[key];
      L.clear();
      while(rand()%LSZ)
        L.push_back(rand()%NELEM);
    }
    print_map(M);

    list<int> L;
    for (int j=0; j<MAPSZ; j++) 
      L.push_back(rand()%NK);
    printl(L);

    concat_map(M,L);
    printl(L);
  }

  return 0;
}
