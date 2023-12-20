#include "eval.hpp"
#include <climits>
#include <cstdlib>
#include <stack>

using namespace aed;
using namespace std;

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

  #iscomb:# Dado un vector de listas #VL# y una lista
  #L#, determinar si #L# es una combinacion de las listas de #VL#
  en alguna permutacion dada. Cada una de las #VL[j]# debe aparecer
  una y solo una vez en #L#.

  #max-sublist:# Programar una funcion
  #list<int> max_sublist(list<int> &L);#
  la cual recibe una lista de enteros y encuentra y retorna la
  sublista consecutiva #Lmax# que obtenga la mayor suma entre todos
  sus elementos. Notar que debido a que algunos elementos pueden ser
  negativos el problema no se resuelve simplemente tomando todos los
  elementos. Tambien es posible que la sublista resultado no contenga
  ningun elemento, en el caso de que todos los elementos de #L# sean
  negativos.

  #mergesort#: Programar una funcion
  #void mergesort(list<int> &L);#
  que reciba una lista #L# desordenada y la
  ordene en forma ascendente.

   [Tomado en el Trabajo Practico de Laboratorio Nro 1
   (TPL1) de 2015-08-29].
   keywords: lista

FIN DE DESCRIPCION */

// Retorna true si L1 es prefijo de L2
bool isprefix(list<int> &L1, list<int> &L2) {
  list<int>::iterator q1=L1.begin(), q2=L2.begin();
  while (q1!=L1.end() && q2!=L2.end()) {
    if (*q1!=*q2) return false;
    q1++; q2++;
  }
  return q1==L1.end();
}

typedef vector< list<int> > vl_t;
// Retorna true si L es una combinacion de los VL
bool iscomb(vl_t &VL, list<int> &L) {
  // Corta la recursion
  if (L.empty() && VL.empty()) return true;
  // Si uno de ellos esta vacio y el otro no
  // es porque no es combinacion
  if (L.empty() || VL.empty()) return false;
  int NL = VL.size();
  for (int j=0; j<NL; j++) {
    // Revisa para cada lista de VL si es prefijo de L
    if (!isprefix(VL[j],L)) continue;
    // Si VL[j] es prefijo de la L entonces
    // elimina la VL[j] y el prefijo de L
    // y vuelve a comparar
    vl_t VL1 = VL;
    VL1.erase(VL1.begin()+j);
    int Nj = VL[j].size();
    list<int> L1=L;
    for (int k=0; k<Nj; k++) L1.erase(L1.begin());
    if (iscomb(VL1,L1)) return true;
  }
  // Si ninguna de las listas VL[j] es prefijo de L
  // iscomb() -> false
  return false;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
list<int> max_sublist(list<int> &L){
  int max_suma = 0;
  list<int> Lmax;
  list<int>::iterator it = L.begin();
  while(it!=L.end()){
    list<int>::iterator it2 = it, itend = it;
    int suma = 0, max_suma_parcial = 0;
    while(it2!=L.end()){
      suma += *it2++;
      if(suma>max_suma_parcial){
        max_suma_parcial = suma;
        itend=it2;
      }
    }
    if(max_suma_parcial>max_suma){
      max_suma = max_suma_parcial;
      Lmax.clear();
      Lmax.insert(Lmax.begin(),it,itend);
    }
    it++;
  }
  return Lmax;
}

void merge(list<int> &L1, list<int> &L2, list<int>& L){
    list<int>::iterator it1 = L1.begin();
    list<int>::iterator it2 = L2.begin();
    while(it1!=L1.end() && it2!=L2.end()){
        if(*it1<*it2){
            L.push_back(*it1);
            it1++;
        }
        else{
            L.push_back(*it2);
            it2++;
        }
    }
    if(it1!=L1.end()) L.insert(L.end(),it1,L1.end());
    if(it2!=L2.end()) L.insert(L.end(),it2,L2.end());
    return;
}

void mergesort(list<int>&L){
  if(L.size()<=1){
    return;
  }else{
    list<int> L1,L2;
    L1.swap(L);
    list<int>::iterator it1=L1.begin();
    for(unsigned int i=0;i<L1.size()/2;i++) it1++;
    L2.splice(L2.begin(),L1,it1,L1.end());
    mergesort(L1);
    mergesort(L2);
    merge(L1,L2,L);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;

  ev.eval1(iscomb,vrbs);
  ev.eval2(max_sublist,vrbs);
  ev.eval3(mergesort,vrbs);
  return 0;
}
