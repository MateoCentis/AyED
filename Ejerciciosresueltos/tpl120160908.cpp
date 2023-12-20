// #define USECHRONO
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

  #transpose:# Sea un vector de listas #M# que almacena los
  coeficientes de una matriz #A# de #m*n# entradas, escribir
  una funcion 
  #void transpose(vector<list<int>>  &M,vector<list<int> > &Mt);# 
  que retorna los coeficientes
  de la matriz transpuesta es decir la lista #Mt[j]#
  contiene la columna} #j-1.#

  #homogeniza:# Implemente una funcion
  #void homogeniza(list<int> &C, int hmin, int hmax);#
  que recibe una lista #C# de enteros ordenados en forma ascendente y la
  modifica de tal manera de que entre cada elemento no exista una
  diferencia menor a #hmin# ni mayor a #hmax.# 

  #bool-opers:# Dadas dos listas
  ordenadas #L1# y #L2,# escribir una funcion
  #void bool_opers(list<int> &Lxor,# #list<int> &Land, list<int> &L1,#
  #list<int> &L2);#

  que deja en #Lxor# una nueva lista ordenada con todos los
  elementos que esten en *solo una* de las dos listas
  originales, y en #Land# una nueva lista ordenada con
  todos los elementos que esten en *ambas.*

   [Tomado en el Trabajo Practico de Laboratorio Nro 1
   (TPL1) de 2016-09-08].  
   keywords: lista

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void transpose(vector<list<int> > &M,vector<list<int> > &Mt) {
  int m = M.size();
  if (!m) return;
  // Toma la cantidad de columnas (deberian ser todas iguales). 
  int n = M[0].size();

  // Mt debe tener tantas filas como columans tenia M
  Mt.resize(n);
  for (int j=0; j<m; j++) {
    // Para cada lista (fila) de M va apendizando los elementos
    // al final de las filas de Mt (ya que debe ser una columna)
    list<int> &row = M[j];
    // Chequea que todas las filas de M tengan la misma longitud
    // (es un prerequisito)
    assert(int(row.size())==n);
    auto p=row.begin();
    int k=0;
    while (p!=row.end()) Mt[k++].push_back(*p++); 
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void homogeniza(list<int>& C, int hmin, int hmax) {
  list<int>::iterator p = C.begin();
  list<int>::iterator q = ++C.begin();
  while(q!=C.end()){
    // Dados dos elementos contiguos p y q
    if((*q-*p)<hmin) {
      //si viola la condicion hmin borra a q 
      q = C.erase(q);
    } else if((*q-*p)>hmax){
      // si viola la hmax insert *p+hmax
      q = C.insert(q,*p+hmax);
      // Si no, incrementa los iteradores
    } else { p++; q++; }
  }  
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void bool_opers(list<int> &Lxor, list<int> &Land, 
                list<int> &L1, list<int> &L2) {
  // it1 it2 recorren L1 y L2
  auto it1 = L1.begin(), it2=L2.begin();
  while ( it1!=L1.end() && it2!=L2.end() ) {
    // Si son distintos inserta el menor en Lxor y avanza
    // el iterador correspondiente 
    if (*it2<*it1) {
      Lxor.push_back(*it2);
      ++it2;
    } else if (*it1<*it2) {
      Lxor.push_back(*it1);
      ++it1;
    } else {
      // Si son iguales inserta en Land y avanza los dos
      Land.push_back(*it1);
      ++it1; ++it2;
    }
  }
  // Apendiza las colas (no importa el orden
  // ya que solo una tendra elementos)
  Lxor.insert(Lxor.end(),it1,L1.end());
  Lxor.insert(Lxor.end(),it2,L2.end());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 1;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  ev.eval<1>(transpose,vrbs);
  h1 = ev.evalr<1>(transpose,seed,vrbs);
  
  ev.eval<2>(homogeniza,vrbs);
  h2 = ev.evalr<2>(homogeniza,seed,vrbs);
  
  ev.eval<3>(bool_opers,vrbs);
  h3 = ev.evalr<3>(bool_opers,seed,vrbs);

  printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
         seed,h1,h2,h3);

  return 0;
}
