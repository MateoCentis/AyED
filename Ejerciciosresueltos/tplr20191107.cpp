#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

#include <set>
#include <vector>
#include <list>
#include <numeric>

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   #media-movil-entera:# Implemente la funcion #list<int>
   mediaMovilEntera(list<int>& L, int v)# que dada una lista de
   enteros #L,# retorne una lista con los valores de la media
   movil con ventana fija de tamano #v.#

   #nSumaK:# Implementar la funcion #bool nSumaK(set<int>
   &S, int k)# que dado un conjunto #S# y un valor #k,#
   retorne el numero de subconjuntos de #S# para los cuales
   la suma de sus elementos sea #k.#

   #nCaminosK:# Dado un grafo simple #map<int,set<int>> G#
   y dos vertices #a# y #b,# implementar una funcion
   #int nCaminosK(graph& G, int a, int b, int k)# que
   retorne el numero de caminos de longitud #k# entre los
   vertices #a# y #b.# El camino puede repetir nodos.

   #make-heap:# Escribir una funcion void
   #make_heap(btree<int> &T);# que convierte in-place el
   arbol binario en parcialmente ordenado, aplicando el
   algoritmo make-heap.

   #sort-stack:# Escribir un programa que ordene una pila
   #S# utilizando recursion de forma tal que los elementos
   de mayor valor se encuentren en el tope. No esta
   permitido el uso de constructores iterativos (#while#,
   #for#, etc) ni tampoco el uso estructuras de datos
   adicionales. Solo pueden utilizarse metodos de la pila.

   [Tomado en el Recup de Trabajo Practico de Laboratorio 
   (TPLR) de 2019-11-07]
   keywords: arbol binario, conjunto, lista, pila

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

//VALIDO TPL 1
list<int> mediaMovilEntera(list<int>& L, int v){
  list<int> R;
  list<int>::iterator it = L.begin();
  list<int> Laux;
  for(;it!=L.end();it++){
    Laux.push_back(*it);
    if(int(Laux.size())==v){
      R.push_back(accumulate(Laux.begin(),Laux.end(),0)/v);
      Laux.pop_front();
    }
  }
  return R;
}

int nSumaK(set<int> S, set<int> Saux, int k){
  if(S.empty()){
    return (accumulate(Saux.begin(),Saux.end(),0)==k);
  }
  int lastEle = *S.begin();
  S.erase(S.begin());
  int a = nSumaK(S, Saux, k);
  Saux.insert(lastEle);
  int b = nSumaK(S, Saux, k);
  return a+b;
}

//VALIDO TPL 3
int nSumaK(set<int> &S, int k) {
  return nSumaK(S,{},k);
}

//VALIDO TPL 2
int nCaminosK(map<int,set<int>> &G, int a, int b, int k) {
  // Si K==0 entonces debe retornar 1 en el caso que A==B y
  // 0 caso contrario
  if(k==0) return a==b;
  // Para K>0 aplica recursion sobre K, es decir calcula la
  // suma de los caminos de longitud K-1 de los vertices V
  // que seon vecinos de A
  int n=0;
  for(auto v:G[a]) n+=nCaminosK(G,v,b,k-1);
  return n;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void make_heap(btree<int> &T,btree<int>::iterator n) {
  // Si el nodo es Lambda corta recursion
  if (n==T.end()) return;
  // LLama recursivamente sobre los hijos
  make_heap(T,n.right());
  make_heap(T,n.left());
  // Va intercambiando el valor del nodo N con el menor de los
  // hijos Q asumiendo que *Q<*N
  while (true) {
    // Q es el minimo de los hijos. Si es una hoja queda apuntando a N
    auto q=n, l=n.left(), r=n.right();
    // Va buscando el minimo
    if (l!=T.end() && *l<*q) q=l;
    if (r!=T.end() && *r<*q) q=r;
    // Si el minimo N es Q entonces es porque N es una hoja
    // o bien *N es menor que el minimo de los hijos y no
    // tiene que bajar. En ese caso sale del lazo ya que no
    // hay que seguir bajando
    if (q==n) break;
    // Intercambia los valores de Q y N
    int tmp=*n;
    *n=*q;
    *q=tmp;
    // Baja N a Q
    n=q;
  }
}

void make_heap(btree<int> &T) {
  // Wrapper, llama a la recursiva
  make_heap(T,T.begin());
}

//VALIDO TPL 1
void sortedInsert(stack<int>& s, int x) {
  if (s.empty() || x > s.top()) {
    s.push(x);
    return;
  }
  
  int temp = s.top();
  s.pop();
  sortedInsert(s, x);
  
  s.push(temp);
}

void printstack(stack<int> &S,const char *lab=NULL) {
  stack<int> S2;
  if (lab) cout << lab << " ";
  while (!S.empty()) {
    int w = S.top(); S.pop();
    cout << w << " ";
    S2.push(w);
  }
  cout << endl;

  while (!S2.empty()) {
    int w = S2.top(); S2.pop();
    S.push(w);
  }
}

//VALIDO TPL 1
void sortStack(stack<int>& s) {
  // printstack(s,"before sort");
  if (!s.empty()) {
    int x = s.top();
    s.pop();
    sortStack(s);
    sortedInsert(s, x);
  }
  // printstack(s,"after sort");
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0,h4=0,h5=0;

  cout << "seed: 123" << endl;
  do {
    ev.eval<1>(mediaMovilEntera,vrbs);
    h1 = ev.evalr<1>(mediaMovilEntera,seed,vrbs);
    
    ev.eval<2>(nSumaK,vrbs);
    h2 = ev.evalr<2>(nSumaK,seed,vrbs);

    ev.eval<3>(nCaminosK,vrbs);
    h3 = ev.evalr<3>(nCaminosK,seed,vrbs);
    
    ev.eval<4>(make_heap,vrbs);
    h4 = ev.evalr<4>(make_heap,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d H4=%03d H5=%03d\n",
           seed,h1,h2,h3,h4,h5);
    
    cout << endl << "Siguiente seed: ";
  } while (cin>>seed);
  
  return 0;
}
