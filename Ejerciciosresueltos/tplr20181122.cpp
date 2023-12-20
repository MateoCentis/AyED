#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

using namespace aed;
using namespace std;

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   #tree_less:#
   Queremos escribir una funcion predicado #bool tree_less(tree<int> &T1,tree<int> &T2);# que sea
   una relacion de orden fuerte para AOO. Debe retornar #true# si #T1<T2.# Recordemos que una relacion de
   orden fuerte debe ser transitiva y tambien debe satisfacer que si #T1<T2# y #T2<T1# son falsos debe ser
   #T1=T2.#

   #xcommon:#
   Implemente una funcion #void xcommon(list<int> &L1,list<int> &L2,list<int> &Lcommon);# tal que
   dadas dos listas #L1# y #L2# extraiga la parte comun del comienzo de #Lcommon,# de tal forma que
   #L2=(Lcommon,Ltail1)# y #L2=(Lcommon,Ltail2).# Adicionalmente, los argumentos #L1,# #L2# deben quedar
   con las ”colas” correspondientes #Ltail1# y #Ltail2.#


   #xsubtrees:#
   Implemente la funcion void #xsubtrees(btree<int> &T, int depth, list<btree<int>> &Lout);#
   que dado un arbol binario #T# y un entero #depth# extraer del arbol #T# todos los subarboles de nodos que
   esten a profundidad #depth# (moverlos hacia la lista de subarboles #Lout# ).

   #maxsubK:#
   Escriba una funcion #int maxsubk(set<int> &S, int k);# que devuelva la maxima suma en valor absoluto
   de todos los subconjuntos posibles del conjunto #S# tomados de a #k.#

   #num-path:# Escriba una funcion 
   #int num_path(map<int,set<int>>& G, int i, int j);# que
   retorne el numero de caminos (sin ciclos) en el grafo no
   dirigido #G,# partiendo desde el vertice #i# y
   finalizando en el vertice #j.# Se garantiza que los nodos
   #i# y #j# estan en el grafo.


   #super-stable-partition:# Escribir una funcion
   #super_stable_partition# que reciba una lista con enteros
   #L# y dos listas vacias #L_low# y #L_geq,# determine si
   existe alguna posicion para particionar la lista en dos
   sublistas segun el valor de dicha posicion, sin
   reordenarla. Es decir, debe encontrar una posicion tal
   que todos los elementos previos a la misma sean menores
   al valor que hay en dicha posicion, y todos los elementos
   posteriores sean mayores o iguales. Si existe tal
   posicion (si hay mas de una, tome la primera en la
   secuencia), mueva (splice) ambas partes a las listas
   #L_low# (menores) y #L_geq# (mayores o iguales) y retorne
   #true;# si no existe retorne #false.#  

   [Tomado en el Recuperatorio de TPLs de 2018-11-22].
   keywords: lista, correspondencia, arbol binario, arbol orientado,conjunto

FIN DE DESCRIPCION */

typedef tree<int>::iterator node_t;
bool tree_less(tree<int> &T1,node_t n1,tree<int> &T2,node_t n2) {
  // Si los valores en n1 y n2 no son iguales ya esta
  if (*n1<*n2) return true;
  if (*n1>*n2) return false;
  // Chequeamos los hijos hasta encontrar uno distinto
  node_t c1=n1.lchild(), c2=n2.lchild();
  while (c1!=T1.end() && c2!=T2.end()) {
    if (tree_less(T1,c1,T2,c2)) return true;
    if (tree_less(T2,c2,T1,c1)) return false;
    c1++; c2++;
  }
  // Hast ahora son todos iguales pero se acabo una de las
  // listas de hijos. Si hay mas hijos en la lista te T2
  // entonces quiere decir que T1<T2. Si hay en T1 o no hay
  // en ninguno de los dos entonces hay que retornar false. 
  return c2!=T2.end();
}

bool tree_less(tree<int> &T1,tree<int> &T2) {
  // El arbol vacio es -INF o sea que nadie puede ser menor que el
  // Si T2 es vacio no puede ser T1<T2
  if (T2.empty()) return false;
  // Si T1 es vacio y ya sabemos que T2 no es vacio => T1 es
  // menor que T2
  if (T1.empty()) return true;
  // Aplicar la funcion recursiva, a partir de ahora los
  // arboles llamados nunca son vacios
  return tree_less(T1,T1.begin(),T2,T2.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void xcommon(list<int> &L1,list<int> &L2,list<int> &Lcommon) {
  Lcommon.clear();
  auto q1=L1.begin(), q2=L2.begin();
  while (q1!=L1.end() && q2!=L2.end()) {
    if (*q1!=*q2) break;
    Lcommon.push_back(*q1);
    q1 = L1.erase(q1);
    q2 = L2.erase(q2);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
typedef btree<int>::iterator bnode_t;
void xsubtrees(btree<int> &T,bnode_t n,int depth,
               list< btree<int> > &subtrees) {
  if (n==T.end()) return;
  if (depth==0) {
    btree<int> tmp;
    T.splice(tmp.begin(),n);
    subtrees.push_back(tmp);
  } else {
    xsubtrees(T,n.left(),depth-1,subtrees);
    xsubtrees(T,n.right(),depth-1,subtrees);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void xsubtrees(btree<int> &T, int depth,
               list< btree<int> > &subtrees) {
  subtrees.clear();
  xsubtrees(T,T.begin(),depth,subtrees);
}

int suma_set(set<int> S){
  int suma = 0;
  for(auto x:S){suma += abs(x);}
  return suma;
}

int maxSubk(set<int> S, int k, set<int> Sk){
  if(k==0) return suma_set(Sk);
  if(S.empty()) return -1;
  int elem = *S.begin();
  S.erase(S.begin());
  int suma_sin = maxSubk(S,k,Sk);
  Sk.insert(elem);
  int suma_con = maxSubk(S,k-1,Sk);
  return (suma_sin>suma_con) ? suma_sin : suma_con;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int maxSubk(set<int> S, int k){
    return maxSubk(S,k,{});
}

void num_path(map<int,set<int>>& G, int i, int j,
             int &npath, set<int> visitados) {
  visitados.insert(i);
  if(i==j) npath++;
  set<int> vecinos = G[i];
  for(int v:vecinos){
    if(!visitados.count(v)){
      num_path(G, v, j, npath, visitados);
    }
  }
}

int num_path(map<int,set<int>>& G, int i, int j){
  int npath = 0;
  set<int> visitados;
  num_path(G, i, j, npath, visitados);
  return npath;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int is_valid(list<int> &L, list<int>::iterator p) {
  for(auto it=L.begin();it!=p;++it)
    if (*it>=*p) return false;
  for(auto it=p;it!=L.end();++it)
    if (*it<*p) return false;
  return true;
}

bool super_stable_partition(list<int> &L, 
                            list<int> &L_low,
                            list<int> &L_geq) {
  for(auto it=L.begin();it!=L.end();++it) {
    if (is_valid(L,it)) {
      L_low.splice(L_low.begin(),L,L.begin(),it);
      L_geq.splice(L_geq.begin(),L,L.begin(),L.end());
      return true;
    }
  }
  return false;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0,h4=0,h5=0,h6=0;

  do {
    // Check a specific task
    ev.eval<1>(tree_less,vrbs);
    h1 = ev.evalr<1>(tree_less,seed,vrbs);

    ev.eval<2>(xcommon,vrbs);
    h2 = ev.evalr<2>(xcommon,seed,vrbs);

    ev.eval<3>(xsubtrees,vrbs);
    h3 = ev.evalr<3>(xsubtrees,seed,vrbs);

    ev.eval<4>(maxsubk,vrbs);
    h4 = ev.evalr<4>(maxsubk,seed,vrbs);
   
    ev.eval<5>(num_path,vrbs);
    h5 = ev.evalr<5>(num_path,seed,vrbs);
    
    ev.eval<6>(super_stable_partition,vrbs);
    h6 = ev.evalr<6>(super_stable_partition,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d H4=%03d H5=%03d H6=%03d\n",
           seed,h1,h2,h3,h4,h5,h6);
    
    printf("\n\nIngrese un valor para la semilla:");
  } while (cin>>seed);

  return 0;
}
