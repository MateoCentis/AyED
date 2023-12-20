// $Id$

/* COMIENZO DE DESCRIPCION 

   __USE_WIKI__
   Dada una lista #L+, escribir una funcion #void odd2even(list<int>#
   #&L,map<int,list<int>> &M);# que mapea cada elemento impar de #L# a la
   siguiente subsecuencia de elementos pares. 
   [Tomado en el TPL2 2013-10-12].
   keywords: correspondencia, lista

   FIN DE DESCRIPCION */

// Por ejemplo si 
// !+L=(1,2,4,3,2,5,2,7,1,6,9,2,14)+ entonces debe dejar
// !+M={1->(2,4,6),3->{2},5->{2},7->{},9->(2,14)}+. 
// Si un numero impar aparece seguido de otro impar entonces el valor
// correspondiente debe ser la lista vacia (por ejemplo el 7
// arriba). Si un numero impar aparece mas de una vez, entonces el
// valor correspondiente debe ser la concatenacion de todas las
// subsecuencias correspondiente (por ejemplo el 1 arriba). 

#include <cstdio>

#include <list>
#include "./util.h"

using namespace std ;


//--------------------------------------------------------------------
void odd2even(list<int> &L,map<int,list<int> > &M) {
  M.clear();
  // Avanza hasta el primer impar
  list<int>::iterator q = L.begin();
  while (q!=L.end() && *q%2==0) q++;
  while (q!=L.end()) {
    list<int> &L2 = M[*q++];
    while (q!=L.end() && *q%2==0) L2.push_back(*q++);
  }
}

//--------------------------------------------------------------------
int main() {
  list<int> L;
  for (int j=0; j<20; j++) L.push_back(rand()%10);
  printf("L: ");
  printl(L);

  typedef map<int,list<int> > map_t;
  map_t M;
  odd2even(L,M);
  map_t::iterator q = M.begin();
  while (q!=M.end()) {
    printf("M[%d] -> ",q->first);
    printl(q->second);
    q++;
  }
  return 0;
}
