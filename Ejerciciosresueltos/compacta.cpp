//__INSERT_LICENSE__
// $Id$

#include <cstdio>
#include <cstdlib>
#include <list>
#include <stack>
#include "./util.h"

using namespace std;

/* COMIENZO DE DESCRIPCION
   
   __USE_WIKI__
   Escribir una funci\'on #void compacta(list<int> &L,stack<int> &S);# que
   toma un elemento entero #n# de #S# y, si es positivo,
   saca #n# elementos de #L# y los reemplaza por su suma. Esto ocurre
   con todos los elementos de #S# hasta que se acaben, o bien se acaben
   los elementos de #L#. 
   [Tomado en el primer parcial del cursado 2010, 2010-09-14.]
   keywords: lista, correspondencia
   
   FIN DE DESCRIPCION */
// -------------------------------------------------------------------

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void compacta(list<int> &L,stack<int> &S) {
  // `p' va recorriendo la lista
  list<int>::iterator p = L.begin();
  while (!S.empty() && p!=L.end()) {
    // Toma un elemento de `S'
    int n = S.top();
    S.pop();
    // Si es >0 hace la manip
    if (n>0) {
      // Acumula en `sum'
      // `k' es el contador de los elementos
      int sum = 0, k=0;
      // OJO corta pq se llegan a los `n' elementos
      // o pq se acaba la lista
      while (k<n && p!=L.end()) {
        sum += *p;
        p = L.erase(p);
        k++;
      }
      // Inserta la suma en `L'
      p = L.insert(p,sum);
      p++;
    }
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  for (int j=0; j<10; j++) {
    printf("\n\n--------------\n");
    list<int> L;
    stack<int> S;
    for (int j=0; j<10; j++) 
      L.push_back(rand()%5);
    
    for (int j=0; j<5; j++) 
      S.push(rand()%5-1);

    printl(L);
    print_stack(S);
    compacta(L,S);
    printl(L);
    print_stack(S);
  }
  return 0;
}
