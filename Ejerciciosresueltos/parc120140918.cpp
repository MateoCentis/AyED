#include <cstdio>
#include <cstdlib>

#include <stack>
#include <list>
#include <map>

#include "./util.h"

using namespace std;

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
  stack-sep: Dada una pila #S#, escribir una funcion que deja en el tope los
  elementos pares y en el fondo los impares. El algoritmo
  debe ser *estable* es decir que los pares deben estar en el mismo
  orden entre si y los impares tambien. 
  exists-path: Dado un mapa #M# que representa un grafo
  dirigido, y dos nodos #m#, #n# determinar si existe un camino
  que va del vertice #m# al #n#.
  extractm: Dada una lista #L#, y un entero #m#, escribir
  una funcion 
  #void extractm(list<int> &L,int m,list<int> &Lm);#
  que genere una lista #Lm# con todos los elementos
  que aparecen exactamente #m# veces en #L#.
  [Tomado en el 1er parcial de 2014-09-18].  
  keywords: lista, correspondencia

  FIN DE DESCRIPCION */

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void stacksep(stack<int> &S) {
  // Usa pilas auxiliares S1 S0,
  // pero no usa "memoria adicional", ya que
  // a medida que la suma de los tamanos de
  // S, S1, y S0 es n. 
  stack<int> S1, S0;

  // Va sacando elementos S y los pone en S1,S0
  // Quedan invertidos en S0, S1
  while (!S.empty()) {
    int x = S.top();
    S.pop();
    if (x%2) S1.push(x);
    else S0.push(x);
  }

  // Pasa los elementos de S1 a S.
  // El orden es importante ya que si no quedan al reves.
  while (!S1.empty()) {
    S.push(S1.top());
    S1.pop();
  }

  // Pasa los elementos de S1 a S.
  while (!S0.empty()) {
    S.push(S0.top());
    S0.pop();
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Esta version es un poco mas compacta
// Hace el paso de S0,S1 a S con el mismo lazo
// usando referencias
void stacksep2(stack<int> &S) {
  stack<int> S1, S0;
  while (!S.empty()) {
    int x = S.top();
    S.pop();
    if (x%2) S1.push(x);
    else S0.push(x);
  }

  // Para j=0 transpasa de S1, y para j=1 desde S0
  for (int j=0; j<2; j++) {
    stack<int> &Sfrom = (j==0? S1 : S0);
    // Pasa los elementos de Sfrom a S.
    // El orden es importante ya que si no quedan al reves.
    while (!Sfrom.empty()) {
      S.push(Sfrom.top());
      Sfrom.pop();
    }
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Funcion auxiliar, imprime el contenido de una pila
void prints(stack<int> &S,const char *lab=NULL) {
  if (lab) printf("%s: ",lab);
  stack<int> S2=S;
  while (!S2.empty()) {
    printf("%d ",S2.top());
    S2.pop();
  }
  printf("\n");
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void extractm(list<int> &L,int m,list<int> &Lm) {
  // Freq: elementos unicos en L -> cantidad de veces que aparece en L
  map<int,int> Freq;
  Lm.clear();
  // Recorre los elementos de L y los cuenta en Freq
  list<int>::iterator q = L.begin();
  while (q!=L.end()) Freq[*q++]++;
  // Recorre Freq e inserta en Lm los que tienen conteo m
  map<int,int>::iterator r = Freq.begin();
  while (r!=Freq.end()) {
    if (r->second==m) Lm.push_back(r->first);
    r++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  // Genera una pila con [0,N)
  stack<int> S;
  printf("\nstacksep, ejemplo 1 --------------\n");
  int N=10;
  for (int j=0; j<N; j++) S.push(j);
  prints(S,"S");
  stacksep(S);
  // stacksep2(S); // Es equivalente
  prints(S,"stacksep(S)");

  for (int j=0; j<5; j++) {
    printf("\nstacksep, ejemplo 2.%d --------------\n",j+1);
    stack<int> S2;
    for (int j=0; j<N; j++) S2.push(rand()%30);
    prints(S2,"S2");
    // stacksep(S2);
    stacksep2(S2); // Es equivalente
    prints(S2,"stacksep(S2)");
  }

  for (int j=0; j<5; j++) {
    printf("\nextractm, ejemplo %d --------------\n",j+1);
    list<int> L;
    int M = 20;
    for (int j=0; j<M; j++)
      L.push_back(rand()%10);
    printf("L: ");
    printl(L);
    for (int m=1; m<M; m++) {
      list<int> Lm;
      extractm(L,m,Lm);
      if (!Lm.empty()) {
        printf("repetidos %d veces: ",m);
        printl(Lm);
      }
    }
  }
  return 0;
}
