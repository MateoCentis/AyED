#include "./eval.hpp"

using namespace aed;

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
  #large-even-list:# Dado un #vector<list<int>> &VL# buscar
  aquella lista #VL[j]# que contiene la maxima cantidad de
  pares y retornar la sublista de pares correspondientes (en
  el mismo orden que estan en #VL[j]# ).  Si hay varias
  listas con la maxima longitud retornar la primera.
 
  #interlaced-split# Dada una lista de enteros #L# y un
  entero positivo #m# dividir a #L# en #m# sublistas (en un vector
  de listas #vector< list<int> > VL# ) en forma
  _entrelazada_ es decir #(a0,a1,a2...)# van
  correspondientemente a las listas #VL[0]#, #VL[1]#, #VL[m-1],#
  #VL[0],# #VL[1]# ... Es decir, el elemento  #aj# va a la lista
  #VL[k]# donde #k=j%m# y #j# es la posicion entera en la lista. 

  #interlaced-join:# Es la inversa de
  #interlaced_split()#. Dado un  #vector< list<int> > VL# 
  juntarlos en una lista #L# de uno a la vez. Es decir, primero los
  primeros elementos de #VL[0]#, #VL[1]#, #...#, #VL[m-1]#,
  despues los segundos elementos, hasta que se acaben todas las
  listas. 

   [Tomado en el TPL1 de 2014-08-30].  
   keywords: lista

  FIN DE DESCRIPCION */

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void large_even_list(vector< list<int> >&VL,list<int>&L) {
  // Cantidad de listas
  int m = VL.size();
  // Limpiar la lista de salidad por las dudas
  L.clear();
  // La lista maxima actual es directamente L
  for (int j=0; j<m; j++) {
    // Lj es una referencia a lista VL[j]
    // tmp es un auxiliar que contendra los pares de VL[j]
    list<int> tmp, &Lj = VL[j];
    // Pone los pares de Lj en tmp
    list<int>::iterator q = Lj.begin();
    while (q!=Lj.end()) {
      if (*q%2==0) tmp.push_back(*q);
      q++;
    }
    // Si Lj tenia mas pares que el maximo actual L lo reemplaza
    if (tmp.size()>L.size()) L=tmp;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void interlaced_split(list<int>&L, int m, 
                      vector< list<int> >&VL) {
  // Limpia VL por si acaso y lo resizea a m
  VL.clear();
  VL.resize(m);
  // j va a ser el indice del elemento en la lista L
  int j=0;
  list<int>::iterator q = L.begin();
  // Recorre L y lo pone en la posicion correspondiente en VL
  while (q!=L.end()) VL[(j++)%m].push_back(*q++);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Esta es la misma version que arriba pero `vanilla' 
void interlaced_split2(list<int>&L, int m, 
                      vector< list<int> >&VL) {
  // Limpia VL por si acaso y lo resizea a m
  VL.clear();
  VL.resize(m);
  // j va a ser el indice del elemento en la lista L
  int j=0;
  list<int>::iterator q = L.begin();
  // Recorre L y lo pone en la posicion correspondiente en VL
  while (q!=L.end()) {
    int k= j%m;
    VL[k].push_back(*q);
    j++; q++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Version vanilla
void interlaced_join(vector< list<int> >&VL, list<int>&L) {
  // Limpiar L por si acaso
  L.clear();
  // Cantidad de listas
  int m = VL.size();
  while (1) {
    int allempty=1;
    for (int j=0; j<m; j++) 
      if (!VL[j].empty()) allempty=0;
    // Despues del lazo si allempty==true si estan todos vacios
    if (allempty) break;
    // Recorre cada lista VL[j] si no esta vacia
    // toma el primer elemento y lo inserta en L. 
    for (int j=0; j<m; j++) {
      list<int> &Lj = VL[j];
      if (!Lj.empty()) {
        L.push_back(Lj.front());
        Lj.pop_front();
      }
    }
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// En esta version se chequea si estan todos vacios en
// el mismo lazo que se extraen los 1ros elementos
// de los VL[j]
void interlaced_join2(vector< list<int> >&VL, list<int>&L) {
  // Limpiar L por si acaso
  L.clear();
  // Cantidad de listas
  int m = VL.size();
  while (1) {
    int allempty=1;
    for (int j=0; j<m; j++) {
      list<int> &Lj = VL[j];
      if (!Lj.empty()) {
        allempty = 0;
        L.push_back(Lj.front());
        Lj.pop_front();
      }
    }
    if (allempty) break;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  printf("sizeof(int) %d\n",sizeof(int));
  printf("sizeof(long int) %d\n",sizeof(long int));

  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1,h2,h3;
  ev.eval1(large_even_list,vrbs);
  h1 = ev.eval1r(large_even_list,seed,0); // para SEED=123 debe retornar H1=581
  
  ev.eval2(interlaced_split,vrbs);
  h2 = ev.eval2r(interlaced_split,seed,0); // para SEED=123 debe retornar H2=421
  
  ev.eval3(interlaced_join2,vrbs);
  h3 = ev.eval3r(interlaced_join2,seed,0); // para SEED=123 debe retornar H3=505
  printf("SEED=%03d -> HASH1=%03d, HASH2=%03d, HASH3=%03d\n",
         seed,h1,h2,h3);
  return 0;
}
