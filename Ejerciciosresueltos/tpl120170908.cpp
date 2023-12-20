#define USECHRONO
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include "eval.hpp"

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   #extract-range:# Dada una lista de enteros #L1# y dos
   iteradores en la misma #p,q#, extraer el rango #[p,q)# de
   #L1# en la lista #L2#. Nota: ambos #p,q# pueden ser
   #end()# y no necesariamente #p# esta antes de #q#.

   #add-elements:# Insertar cada uno de los elementos de la
   pila #S# en la lista ordenada #L#, la cual debe permanecer ordenada
   luego de la insercion. La funcion debe retornar la cantidad de
   numeros repetidos en la lista #L# luego de la insercion. Tener en
   cuenta que si hay mas de dos ocurrencias del mismo numero, dicho
   numero cuenta una unica vez en la suma de elementos repetidos.

   #coprimos:# Escribir una funcion #bool coprimos(list<int>
   &L);# que retorna #true# si todos los elementos de #L#
   son coprimos entre si. Recordemos que dos enteros son
   coprimos entre si el unico entero que divide a ambos es
   1. 

   [Tomado en el TPL1 de 2017-09-08].  
   keywords: lista, pila, cola

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int distance(list<int> &L,list<int>::iterator p) {
  // Calcula la distancia entre begin y la posicion.
  // Notar que funciona tambien si p es end()
  int j=0;
  auto z=L.begin();
  while (z!=p) { j++; z++; }
  return j;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void extract_range(list<int> &L1, list<int>::iterator p, 
                   list<int>::iterator q, list<int> &L2)  {
  // La funcion distance calcula la distancia entre el origen y
  // el iterador. En caso de no conocerla es muy facil de implementar
#if 0
  // Usa la distancia de la libreria standard
  int dp = std::distance(L1.begin(),p);
  int dq = std::distance(L1.begin(),q);
#else
  // Usa la distancia implementada arriba
  int dp = distance(L1,p);
  int dq = distance(L1,q);
#endif
  // q esta antes de p, no hay que hacer nada
  if (dq<=dp) return;
  L2.insert(L2.begin(),p,q);
  L1.erase(p,q);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void extract_range2(list<int> &L1, list<int>::iterator p, 
                    list<int>::iterator q, list<int> &L2)  {
  // Asegurarse que L2 este vacia
  L2.clear();
  // Si p es end entonces no hay ningun elemento despues de p
  if (p==L1.end()) return;
  // Verifica si se puede llegar a q desde p
  // Notar que funciona incluso si q es end
  auto z=p;
  while (z!=L1.end() && z!=q) z++;
  // No se llega a q, por lo tanto no hay que hacer nada
  if (z!=q) return;
  // Recorre desde p a q y va eliminando los elementos de
  // L1 y los pone en L2. 
  z=p;
  while (z!=q) {
    L2.push_back(*z);
    z = L1.erase(z);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void extract_range3(list<int> &L1, list<int>::iterator p, 
                    list<int>::iterator q, list<int> &L2)  {
  // Asegurarse que L2 este vacia
  L2.clear();
  if (p==L1.end()) return;
  auto z = L1.begin();
  // Se fija si llega primero a p o a q
  while (z!=L1.end() && z!=p && z!=q) z++;
  // Si llega primero a q no hay que hacer nada
  if (z==q) return;
  z=p; // De todas formas esto deberia ser cierto
  // Recorre desde p a q y va eliminando los elementos de
  // L1 y los pone en L2. 
  while (z!=q) {
    L2.push_back(*z);
    z = L1.erase(z);
  }
  
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int add_elements(list<int>& L, stack<int> &S) {
  // Inserta todos los elementos de S en L
  // manteniendo L ordenada
  while(!S.empty()) {
    int x = S.top(); S.pop();
    list<int>::iterator it = L.begin();
    while(it!=L.end() && *it<x) ++it;
    L.insert(it,x);
  }
  // Cuenta los valores repetidos
  int ret = 0;
  for( list<int>::iterator it=L.begin(); it!=L.end(); ++it ) { 
    bool rep = false;
    while (next(it)!=L.end() && *it==*next(it)) {
      ++it; rep=true;
    }
    if (rep) ret++;
  }
  return ret;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int add_elements2(list<int>& L, stack<int> &S) {
  // Otra solucion
  auto p=L.begin();
  while (!S.empty()) {
    int x = S.top(); S.pop();
    // S no esta necesariamente ordenada hay
    // que buscar desde el principio
    p=L.begin();
    while (p!=L.end() && *p<x) p++;
    L.insert(p,x);
  }
  // Cuenta los repetidos
  int reps=0;
  p=L.begin();
  while (p!=L.end()) {
    auto q=p; q++;
    if (q!=L.end() && *q==*p) reps++;
    // Avanza p hasta encontrar end() o un elemento distinto
    while (q!=L.end() && *q==*p) q++;
    p=q;
  }
  return reps;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Retorna en L los divisores (>=2) de x
void divisores(int x,list<int>&L){
  int i = 2;
  while(i<=x){
    if(x%i == 0)
      L.push_back(i);
    i++;
  }
}

// Retorna true si x esta en la lista L
bool contiene(int x, list<int>&L){
  for(auto y: L){
    if(y == x)
      return true;
  }
  return false;
}

bool repetidos(list<int>::iterator it1,list<int>::iterator it2){
  if(it1 == it2) return false;
  list<int>::iterator ita = it1;ita++;
  while(ita != it2){
    if(*ita == *it1)
      return true;
    ita++;
  }
  it1++;
  return repetidos(it1,it2);
}

bool coprimos(list<int>&L) {
  list<int>::iterator it = L.begin(),it2;
  it2 = it;it2++;
  if(repetidos(L.begin(),L.end()))return false;
  list<int> divs;
  divisores(*(L.begin()), divs);
  it++;
  while(it!= L.end()){
    list<int> aux;
    divisores(*it, aux);
    for(auto x : aux){
      if(contiene(x,divs))
        return false;
      else divs.push_back(x);
    }
    it++;
  }
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Otra posible solucion
bool coprimos2(list<int>&L) {
  // p,q recorren todos los pares distintos en L.
  // p recorre [begin,end)
  auto p=L.begin();
  while (p!=L.end()) {
    auto q=p; q++;
    // para cada p, q recorre [p+1,end)
    while (q!=L.end()) {
      // Determina si *p y *q son coprimos
      // recorre con k entre [2,min(*p,*q)] y para cada
      // k verifica si divide a *p y *q
      int k=2, min=(*p<*q? *p : *q);
      while (k<=min) {
        // Si k divide a *p y *q entonces no son coprimos
        if (*p%k==0 && *q%k==0) return false;
        k++;
      }
      q++;
    }
    p++;
  }
  // Todos los elementos son coprimos entre si
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

#if 0
  // User typical call
  ev.eval<1>(extract_range,vrbs);
  h1 = ev.evalr<1>(extract_range,seed,vrbs);
  
  ev.eval<2>(add_elements,vrbs);
  h2 = ev.evalr<2>(add_elements,seed,vrbs);
  
  ev.eval<3>(coprimos,vrbs);
  h3 = ev.evalr<3>(coprimos,seed,vrbs);
  printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
         seed,h1,h2,h3);
#else
#include "./tasks.cpp"
#endif
  
  return 0;
}
