#define USECHRONO
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>

using namespace aed;
using namespace std;

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   #unordered-equal:#
   Escribir una funcion bool que
   reciba dos Arboles Ordenados Orientados (AOO) y retorne #true# si
   son desordenadmente iguales. Es decir si se pueden transformar uno en el otro 
   conpermutaciones en la lista de hermanos de cada nod. 

   #hay-camino:# Un viajante quiere viajar desde una
   ciudad a otra siguiendo algun camino del grafo conexo de rutas
   #M.# Lamentablemente se tiene la informacion de que en algunas
   ciudades hay piquetes y es imposible pasar por ellas. Para
   determinar si es posible realizar el viaje se debe implementar una
   funcion, que recibe el mapa de rutas disponibles (cada arista del grafo
   representa una ruta directa disponible entre las ciudades de los
   vortices que conecta), y la lista de ciudades con piquetes. La
   funcion debe retornar verdadero si existe alguna ruta que comience
   en la ciudad #cini# y finalice en #cend# sin pasar por ninguna de las
   ciudades con piquetes.

   #enhance-html:# Los desarrolladores de un sitio web
   desean resaltar los links que aparecen dentro de cada
   pagina del sitio. Para ello es necesario que cada link
   (tag #<a># en HTML) se encuentre dentro de un tag
   #<strong>.# Para resolver este problema ya contamos con
   un parser del codigo HTML que lo representa en un
   #tree<string>.# Escribir una funcion que recorre dicho
   arbol y si encuentra una hoja con tag #a# le agrega un padre #strong#. 

   [Tomado en el Trabajo Practico de Laboratorio Nro 2
   (TPL2) de 2016-10-13].  
   keywords: correspondencia, arbol orientado

FIN DE DESCRIPCION */

bool unordered_equal(tree<int> &A,tree<int> &B,
                     tree<int>::iterator itA,
                     tree<int>::iterator itB) {
  map<int,tree<int>::iterator> MA, MB;
  for(auto it = itA.lchild(); it!=A.end(); ++it) MA[*it] = it;
  for(auto it = itB.lchild(); it!=B.end(); ++it) MB[*it] = it;
  if (MA.size()!=MB.size()) 
    return false;
  for (auto itMA = MA.begin(), itMB = MB.begin(); itMA!=MA.end(); ++itMA, ++itMB) {
    if (itMA->first!=itMB->first) 
      return false;
    if (!unordered_equal(A,B,itMA->second,itMB->second)) 
      return false;
  }
  return true;
}

bool unordered_equal(tree<int> &A,tree<int> &B) {
  if (*A.begin()!=*B.begin()) 
    return false;
  return unordered_equal(A,B,A.begin(),B.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Otra posibilidad: Hace que cada arbol este en forma
// `canonica' es decir que todos sus hijos estan ordenados.
// make_canonical(T) -> hace que T quede en forma canonica
// Entonces podemos hacer make_canonical(A),
// make_canonical(B) y despues retornar A==B, ya que son
// `unordered_equal' si y solo si sus formas canonicas son iguales. 
typedef tree<int>::iterator node_t;
void make_canonical(tree<int> &T, node_t n) {
  if (n==T.end()) return;
  // M contiene para los hijos de `n': *c -> subarbbol de c
  // Lo hace con splice
  map<int,tree<int> > M;
  node_t c = n.lchild(),d;
  while (c!=T.end()) {
    d = c; d++;
    tree<int> &C = M[*c];
    c = C.splice(C.begin(),c);
    c = n.lchild();
  }

  // Ahora recorre los hijos de n y les vuelve a aplicar el
  // make_canonical recursivamente a los hijos y los vuelve
  // a insertar como hijos de `n'
  c = n.lchild();
  for (auto q=M.begin(); q!=M.end(); q++) {
    tree<int> &C = q->second;
    make_canonical(C,C.begin());
    auto cb = C.begin();
    c = T.splice(c,cb);
  }
}

bool unordered_equal2(tree<int> &A,tree<int> &B) {
  make_canonical(A,A.begin());
  make_canonical(B,B.begin());
  return A==B;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool hay_camino(map<string,list<string> > &M, string cini, string cfin,
                map<string,bool> visited) {
  visited[cini] = true;
  auto &L = M[cini];
  for(auto &cvec:L) {
    if (cvec==cfin) 
      return true;
    if (!visited[cvec] && hay_camino(M,cvec,cfin,visited)) 
      return true;
  }
  return false;
}

bool hay_camino(map<string,list<string> > &M, list<string> &P,
                string cini, string cfin) {
  map<string,bool> visited; 
  for(auto &p:M) 
    visited[p.first] = false;
  for(string &c:P) 
    visited[c] = true;
  return hay_camino(M,cini,cfin,visited);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void enhance_html(tree<string> &T, string father,
                  tree<string>::iterator it) {
  if (*it=="a" && father!="strong") {
    *it="strong";
    T.insert(it.lchild(),"a");
  } else {
    for(auto c = it.lchild(); c!=T.end(); ++c) {
      enhance_html(T,*it,c);
    }
  }
}

void enhance_html(tree<string> &T) {
  enhance_html(T,"",T.begin());
}


//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  ev.eval<1>(unordered_equal2,vrbs);
  h1 = ev.evalr<1>(unordered_equal,seed,vrbs);
  
  ev.eval<2>(hay_camino,vrbs);
  h2 = ev.evalr<2>(hay_camino,seed,vrbs);
  
  ev.eval<3>(enhance_html,vrbs);
  h3 = ev.evalr<3>(enhance_html,seed,vrbs);

  printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
         seed,h1,h2,h3);

  return 0;
}
