/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dado un grafo #map<int, set<int> >G#
   y una lista de vertices #list<int> L# determinar si #L# es un
   _camino hamiltoniano_ en #G#. 
   [Tomado en tercer parcial 2011-11-24].
   keywords: conjunto, grafo

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------

#include <cstdio>
#include <cassert>

#include <list>
#include <map>
#include <set>
#include <string>

using namespace std;

typedef map<int, set<int> > graph_t;
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// `cycle=1' indica si chequea para un ciclo
// Hamiltoniano, si `cycle=0' chequear para un camino
// Hamiltoniano
bool is_hamilt_path(graph_t &G,list<int> &L,int cycle=0) {
  // chequea que todos los indices en L
  // sean relamente nodos del grafo (o sea claves del map)
  list<int>::iterator x=L.begin();
  while (x!=L.end()) 
    if (G.find(*x++)==G.end()) 
      return false;

  // Guarda los vertices que ya fueron visitados
  set<int> visited;
  // x,y son dos posiciones consecutivas en la lista
  x = L.begin();
  list<int>::iterator start=x, y, last;
  // Si la lista esta vacia la unica posibilidad
  // para que sea Hamiltoniano es que el grafo este vacio
  if (x==L.end()) return G.empty();
  // Chequea si el vertice esta en el grafo o no
  if (G.find(*x)==G.end()) return false;
  while (1) {
    // Si ya fue visitado NO es Ham
    if (visited.find(*x)!=visited.end()) return false;
    visited.insert(*x);
    // apunta con y al siguiente de x
    y = x; y++;
    if (y==L.end()) break;
    // Si y no esta en el gradfo no es Ham
    if (G.find(*y)==G.end()) return false;
    // Toma los vecinos de x 
    set<int> &xngbrs = G[*x];
    // Si y no es adyacente a x NO es Ham
    if (xngbrs.find(*y)==xngbrs.end()) return false;
    x=y;
  }
  // Chequea que los haya visitado a todos, para eso
  // solo basta con chequear que los tamanos sean iguales
  if (!cycle) return L.size()==G.size();
  // Para detectar ciclos Hamiltonianos hay que chequear
  // ademas que el ultimo este conectado con el primero
  if (L.size()!=G.size()) return false;
  last = x;
  set<int> &ngbrs = G[*last];
  return ngbrs.find(*start)!=ngbrs.end();
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool is_hamilt_cycle(graph_t &G,list<int> &L) {
  return is_hamilt_path(G,L,1);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int modulo(int n,int m) {
  int r = n%m;
  if (r<0) r+= m;
  return r;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  // simple 1D graph
  int N=12;
  graph_t G;
  for (int j=0; j<N; j++) {
    set<int> &ngbrs = G[j];
    ngbrs.insert(modulo(j+1,N));
    ngbrs.insert(modulo(j-1,N));
  }

  list<int> L;
  // for (int j=0; j<N-1; j+=2) L.push_back(j);
  for (int j=0; j<N; j++) L.push_back(modulo(6+j,N));
  
  printf("is Hamilt path? %d\n",is_hamilt_path(G,L));
  printf("is Hamilt cycle? %d\n",is_hamilt_cycle(G,L));
  return 0;
}
