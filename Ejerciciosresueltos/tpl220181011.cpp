#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   #classify_relative:# Implemente una funcion 
   #void classify_relative(tree<int> &T,int n1,int n2,int &m1, int&m2);#
   que dados dos valores nodales #n1# y #n2# en un arbol #T# retorna
   las distancias #m1# y #m2# de ambos nodos al antecesor comun mas
   cercano. Por ejemplo si #T1=(5 (1 8 (9 2)) (7 3))#, #n1=8# y #n2=7#
   entonces el antecesor comun es el nodo #5# (la raiz) y las
   distancias correspondientes son #m1=2# y #m2=1#.

   #prom-path:#
   Dado un arbol #T#, escribir una funcion
   #float prom_path(tree<int> &T);#
   que retorne la longitud
   promedio de los caminos desde la raiz a las hojas. Por ejemplo, para
   el arbol #T=(1 (2 3 4 (5 6)) 7 8)#, los 5 posibles caminos desde la
   raiz a una hoja son:\\
   #{1,2,3}, {1,2,4}, {1,2,5,6}, {1,7}, {1,8};#
   cuyas longitudes son 2, 2, 3, 1 y 1; lo cual da un promedio de
   (2+2+3+1+1)/5 = 9/5 = 1.8.

   #filtra-deps:# Se tiene un #map<string,list<string>>#
   que representa un grafo dirigido donde los nodos son nombres
   paquetes de software en un repositorio, y los arcos dependencias
   entre paquetes.

   [Tomado en el Trabajo Practico de Laboratorio Nro 2
   (TPL2) de 2018-10-11].
   keywords: arbol orientado, correspondencia

FIN DE DESCRIPCION */


using namespace aed;
using namespace std;

typedef tree<int>::iterator node_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Extraer el camino desde el nodo que contiene el entero
// "n". La lista contiene todos los nodos desde la raiz
// hasta el nodo.  Funcion recursiva auxiliar. Extrae el
// camino desde el nodo "q". Si el entero "n" no esta en el
// subarbol de "q" entonces retorna la lista vacia. 
void get_path(tree<int> &T,node_t q,int n,list<int> &L) {
  // Si el nodo es Lambda entonces retorna la lista vacia
  if (q==T.end()) return;
  // Si el nodo contiene el valor buscado retorna una lista
  // solo con el valor del nodo
  if (*q==n) {
    L.clear();
    L.push_back(n);
    return;
  }

  // Busca en los hijos "c" de "q". Si alguno retorna un
  // lista no vacia es que ahi esta el nodo y solo basta con
  // prependizar el valor del nodo "q"
  auto c =q.lchild();
  while (c!=T.end()) {
    get_path(T,c,n,L);
    if (!L.empty()) {
      // Lo encontro. Prependiza *q y retorna
      L.push_front(*q);
      return;
    }
    // Incrementa c
    c++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper llama desde la raiz
void get_path(tree<int> &T,int n,list<int> &L) {
  L.clear();
  get_path(T,T.begin(),n,L);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Retorna los indices m1 m2 de n1 y n2 que contabilizan la
// distancia al antecesor comun
void classify_relative(tree<int> &T,
                       int n1,int n2,int &m1, int&m2) {
  // Busca el camino de la raiz a n1 y a n2
  list<int> L1,L2;
  get_path(T,n1,L1);
  get_path(T,n2,L2);
  // Busca el ultimo antecesor comun 
  auto q1=L1.begin(), q2=L2.begin();
  while (q1!=L1.end() && q2!=L2.end()
         && *q1==*q2) {
    q1++; q2++;
  }
  m1=0; m2=0;
  // Cuenta cuantos nodos hay desde el antecesor comun hasta n1
  while (q1!=L1.end()) { q1++; m1++; }
  // Cuenta cuantos nodos hay desde el antecesor comun hasta n2
  while (q2!=L2.end()) { q2++; m2++; }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void prom_path(tree<int> &T, tree<int>::iterator it,
               int l, int &sum, int &cant) {
 auto itC = it.lchild();
 if (itC==T.end()) { cant++; sum+=l; return; }
 while(itC!=T.end()) {
   prom_path(T,itC,l+1,sum,cant);
   ++itC;
 }
}

float prom_path(tree<int> &T) {
 int sum=0,cant=0;
 prom_path(T,T.begin(),0,sum,cant);
 return float(sum)/cant;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void marca_necesarios(map<string,list<string>> &G,
                      std::string s, std::set<std::string> &necesarios) {
  if (necesarios.count(s)) return;
  necesarios.insert(s);
  for(auto d:G[s]) marca_necesarios(G,d,necesarios);
}

void filtra_deps(map<string,list<string>> &G, list<string> &L) {
  std::set<std::string> necesarios;
  for(auto s:L) 
    marca_necesarios(G,s,necesarios);
 
  for(auto itG=G.begin();itG!=G.end();) {
    if (necesarios.count(itG->first)) {
      auto &D=itG->second;
      for(auto itD=D.begin();itD!=D.end();) {
        if (necesarios.count(*itD)) ++itD;
        else itD = D.erase(itD);
      }
      ++itG;
    } else {
      itG = G.erase(itG);
    }
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  do {

    ev.eval<1>(classify_relative,vrbs);
    h1 = ev.evalr<1>(classify_relative,seed,vrbs);

    ev.eval<2>(prom_path,vrbs);
    h2 = ev.evalr<2>(prom_path,seed,vrbs);

    ev.eval<3>(filtra_deps,vrbs);
    h3 = ev.evalr<3>(filtra_deps,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    printf("\n\nIngrese un valor para la semilla:");
  } while (cin>>seed);

  return 0;
}
