/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dados dos conjuntos #set<int> A,B# y una funcion *biyectiva*
   #int f(int)# determinar si es #B=f(A)# es decir *todos* los
   elementos de #B# se obtienen como imagen de #A# aplicando #f()#.\\

   [Tomado en el 3er parcial de 2012-11-22].  
   keywords: correspondencia

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------

#include <cstdio>
#include <cassert>
#include <cmath>

#include <map>
#include <set>

#include "./util.h"

using namespace std;

typedef map<int, set<int> > graph_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool ismapped(const set<int> &A,const set<int> &B,int (*f)(int)) {
  // Como la funcion es biyectiva los tamanos de A y B
  // deben ser el mismo
  if (A.size()!=B.size()) return false;
  // `q' itera sobre y verifica que los
  // valores `f(*q)' esten en B
  set<int>::iterator q = A.begin();
  while (q!=A.end()) 
    if (B.find(f(*q++))==B.end()) return false;
  return true;
}

// Funcion cubo (no puede ser el cuadrado
// porque no es biyectiva, a menos que se restrinja
// a valores no negativos)
int cube(int j) { return j*j*j; }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  set<int> A,B;
  for (int j=-3; j<4; j++) {
    A.insert(j);
    B.insert(j*j*j);
  }
  printf("ismapped(A,B,cube): %d\n",ismapped(A,B,cube));
  
  return 0;
}
