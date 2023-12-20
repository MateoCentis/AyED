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
  Implementar una funci\'on 
  #void cutoff_map(map<int, list<int> > &M,int p,int q);#
  que elimina todas las claves que NO estan en el rango
  #[p,q)#. En las asignaciones que quedan tambien debe eliminar
  los elementos de la lista que no estan en el rango. Si la lista queda
  vacia entonces la asignacion debe ser eliminada. 
  [Tomado en el primer parcial del cursado 2010, 2010-09-14.]
  keywords: lista, correspondencia
   
   FIN DE DESCRIPCION */
// -------------------------------------------------------------------

typedef map<int,list<int> > map_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void cutoff_map(map_t &M, int p,int q) {
  // `s' recorre los pares del map
  map_t::iterator s = M.begin(),t;
  while (s!=M.end()) {
    int key = s->first;
    list<int> &L = s->second;
    // si la clave no esta en el rango entonces directamente
    // limpia la lista
    if (key<p || key>=q) L.clear();
    // Ahora recorre la lista filtrando los
    // valores q no estan en el rango
    list<int>::iterator r = L.begin();
    while (r!=L.end()) {
      // OJO q si se hace el `erase' no hay q hacer
      // el ++
      if (*r < p || *r >= q) r = L.erase(r); 
      else r++;
    }

    // OJO esto es tricky. Como el erase de map
    // no retorna un iterator, entonces hay que
    // primero guardar un iterator al siguiente
    // par `t' y despues borrar `s'. OJO aca `s'
    // puede haber quedado vacia pq o bien ya
    // estaba vacia, o pq la clave no estaba en el rango
    // o pq todos los elementos fueron filtrados.
    t = s; t++;
    if (L.empty()) M.erase(s);
    s = t;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  map_t M;
  // Genera un map aleatorio con claves y valores en [0,20)
  for (int j=0; j<10; j++) {
    // Genera la entrada en el map y toma la referencia
    // a la imagen
    list<int> &L = M[rand()%20];
    // La lista tiene en promedio un largo de 5 (pq
    // la probabilidad q corte es 1/5)
    while (rand()%5)
      L.insert(L.end(),rand()%20);
  }

  printf("Antes de cutoff_map(5,15)\n");
  print_map(M);
  cutoff_map(M,5,15);
  printf("Despues de cutoff-map(5,15)\n");
  print_map(M);

  return 0;
}
