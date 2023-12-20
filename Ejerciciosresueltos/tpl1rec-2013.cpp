/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

  mergekw: Dado un vector de listas ordenadas hacer una fusion
  K-way, es decir juntar todas las listas en una sola,
  tambien ordenada. El algoritmo K-way consiste en
  recorrer los primeros elementos de las listas (atencion que algunas
  pueden estar vacias), tomar el menor e insertarlo al fin de la lista
  #L# Esto se realiza hasta que todas las listas esten vacias. El
  algoritmo es similar a la fusion de dos listas, pero generalizado a
  #K# listas. 

  splitlist: Dado un vector de listas #VL1# y un entero
  #M# devolver otro vector de listas #VL2# donde las listas
  tienen a lo sumo M elementos. 

  join-list: Dado un vector de listas #VL1# escribir una
  funcion que va juntando listas de #VL1# hasta que 
  todas tengan longitud #>=M#. 

   [Tomado en el Recup TPL1 de 2013-09-19].  
   keywords: lista

  FIN DE DESCRIPCION */
// -----------------------------------------------------------------

#include <cstdio>
#include <climits>
#include <cassert>
#include "Evaluar.hpp"

void print(list<int> &L,const char*s=NULL) {
  if (s) printf("%s: ",s);
  printf("(",s);
  list<int>::iterator q = L.begin();
  while (q!=L.end()) printf("%d ",*q++);
  printf(")\n");
}

void print(vector<list<int> > &VL,const char*s=NULL) {
  if (s) printf("%s:\n",s);
  for (int j=0; j<VL.size(); j++) {
    printf("VL[%d]: ",j);
    print(VL[j]);
  }
}

void mergekw(vector<list<int> > &VL,list<int> &L) {
  L.clear();
  int N = VL.size();
#if 0
  for (int j=0; j<N; j++) {
    printf("VL[%d]: ",j);
    print(VL[j]);
  }
#endif
  while (1)  {
    int allempty=1, min=INT_MAX, jmin=-1;
    for (int j=0; j<N; j++) {
      if (!VL[j].empty()) {
        allempty=0;
        list<int>::iterator q = VL[j].begin();
        if (*q<min) {
          min=*q;
          jmin=j;
        }
      }
    }
    if (allempty) break;
    VL[jmin].erase(VL[jmin].begin());
    L.push_back(min);
  }
  // print(L,"L: ");
}

void split_list(vector<list<int> > &VL1,int M, 
                vector<list<int> > &VL2) {
  // print(VL1,"VL1");
  VL2.clear();
  int N = VL1.size();
  for (int j=0; j<N; j++) {
    list<int> &L = VL1[j];
    while (L.size()>M) {
      VL2.push_back(list<int>());  
      list<int> &dest = VL2.back();
      list<int>::iterator q = L.begin();
      for (int j=0; j<M; j++) {
        dest.push_back(*q);
        q = L.erase(q);
      }
    }
    if (!L.empty()) VL2.push_back(L);
  }
  // print(VL2,"VL2");
}

void join_list(vector<list<int> > &VL1,int M, 
               vector<list<int> > &VL2) {
  // print(VL1,"VL1");
  VL2.clear();
  int N = VL1.size();
  list<int> tmp;
  for (int j=0; j<N; j++) {
    list<int> &L = VL1[j];
    tmp.insert(tmp.end(),L.begin(),L.end());
    if (tmp.size()>=M) {
      VL2.push_back(tmp);
      tmp.clear();
    }
  }
  if (!tmp.empty()) VL2.push_back(tmp);
  // print(VL2,"VL2");
}

int main()
{
    aed::Evaluar ev;
    ev.evaluar1(mergekw);
    ev.evaluar2(split_list);
    ev.evaluar3(join_list);
    return 0;
}
