// $Id$

/* 
   COMIENZO DE DESCRIPCION 
   __USE_WIKI__
   Escribir una funcion 
   #void expand(list<int>  &L,int m);# 
   que transforma los elementos de una lista #L# de tal
   forma que todos los elementos de #L# resulten ser menores o igual
   que #m#, pero de tal forma que su suma se mantenga inalterada. 
   [Tomado en primer parcial 2011-09-15].
   keywords: lista
    
   FIN DE DESCRIPCION 
*/

// Para esto, si un elemento !+x+ es mayor que !+m+
// entonces, lo divide en tantas partes como haga falta
// para satisfacer la condicion; por ejemplo si !+m=3+
// podemos dividir a !+10+ en !+3,3,3,1+.  Es decir si
// !+L=(7,2,3,1,4,5)+, entonces despues de hacer
// !+expand(L,2)+ debe quedar
// !+L=(2,2,2,1,2,2,1,1,2,2,2,2,1)+.

// -----------------------------------------------------------------
#include <cassert>
#include <cstdio>
#include <cmath>
#include <vector>
#include <set>
#include "./util.h"
using namespace std ;

void expand(list<int>  &L,int m) {
  list<int>::iterator p = L.begin();
  while (p!=L.end()) {
    int x = *p;
    p = L.erase(p);
    while (x>0) {
      int val = (x>m ? m : x);
      p = L.insert(p,val);
      x -= val;
      p++;
    }
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  for (int k=0; k<10; k++) {
    list<int> L;
    for (int j=0; j<10; j++) L.insert(L.end(),rand()%10);
    int m = rand()%5 + 3; // m va entre 3 y 7
    printf("Before expand:\n");;
    printl(L);
    expand(L,m);
    printf("After expand(L,%d):\n---------\n",m);
    printl(L);
  }
  return 0;
}
