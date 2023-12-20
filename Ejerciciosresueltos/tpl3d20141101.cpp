#include "eval.hpp"
#include <cstdlib>
#include <stack>

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

  #bijsubset:#
  Dado un conjunto #S# y una funcion de mapeo #T(*f)(T)#
  determinar el conjunto #S1# de elementos #x# de #S1# tales
  que no existe otro elemento #z# con #f(x)=f(z).# Es decir,
  para los elementos de #S1# y su imagen, la relacion es
  biyectiva.

  #preimage:#
  Dados un #vector<set<int> > VX# y un #set<int> Y,# y una
  funcion de mapeo #T(*f)(T)# encontrar el conjunto de
  #VX[j]# *preimagen* de #Y# tal que si se le aplica
  #f# a sus elementos, se obtiene #Y.#

  #is-recurrent-tree:# 
  Dado un arbol binario lleno (todos sus nodos interiores
  tienen los dos hijos), verificar si es un *arbol
  recurrente.* Un arbol binario se considera recurrente si
  cada uno de sus nodos interiores es la suma de sus 2 nodos
  hijos. Se generaliza ademas para cualquier funcion
  asociativa #g(x,y),# es decir no solo para la suma.

  #ordered-tree:# 
  Dado un vector de numeros enteros positivos, se debera
  armar un arbol binario de manera que la posicion i-esima
  del vector verifica si es mayor que la raiz. En caso que
  sea mayor, intentara insertarse en el subarbol derecho de
  la misma, y sino en el subarbol izquierdo. Si el hijo
  correspondiente esta vacio entonces lo inserta alli, si no
  lo compara con el elemento, y vuelve a aplicar la regla
  recursivamente. La definicion es similar a la de un arbol
  binario, pero no representa un conjunto, es decir los
  elementos pueden estar duplicados.

  [Tomado en el Trabajo Practico de Laboratorio Nro 3 (TPL3) de 2014-11-01].  
  keywords: arbol binario, conjunto

FIN DE DESCRIPCION */


using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool is_recurrent_tree (btree<int> &T, assoc_fun_t g, 
                        btree<int>::iterator a){
  if(a == T.end()) return true;
  assert((a.left()==T.end()) == (a.right()==T.end()));
  if (a.left()==T.end()) return true;
  if(!is_recurrent_tree(T,g,a.right())) return false;
  if(!is_recurrent_tree(T,g,a.left())) return false;
  if(*a == g(*a.right(),*a.left())) return true;
  return false;
}	
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool is_recurrent_tree (btree<int> &T,assoc_fun_t g){
  if(T.begin() == T.end()) return true;
  return is_recurrent_tree(T,g,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void ordered_tree(vector<int> &V, btree<int> &t){
  t.clear();
  for(int i = 0 ; i < V.size() ; i++){
    btree<int>::iterator it = t.begin();
    while(it!=t.end()){
      if(V[i]>*it) it = it.right();
      else it = it.left();
    }
    t.insert(it,V[i]);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void bijsubset(set<int> &S, map_fun_t f, set<int> &S1) {
  set<int> Image,ImageDup;
  set<int>::iterator q = S.begin();
  while (q!=S.end()) {
    int y = f(*q);
    if (Image.find(y)!=Image.end()) ImageDup.insert(y);
    Image.insert(y);
    q++;
  }

  S1.clear();
  q = S.begin();
  while (q!=S.end()) {
    int y = f(*q);
    if (ImageDup.find(y)==ImageDup.end())
      S1.insert(*q);
    q++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool is_mapped(set<int>&X,map_fun_t f,set<int> &Y) {
  set<int> fX;
  set<int>::iterator q = X.begin();
  while (q!=X.end()) fX.insert(f(*q++));
  return Y==fX;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool preimage(vector< set<int> >&VX,map_fun_t f,
              set<int> &Y,set<int> &preY) {
  preY.clear();
  int NX = VX.size();
  for (int j=0; j<NX; j++) {
    if (is_mapped(VX[j],f,Y)) {
      preY = VX[j];
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
  int h1=0,h2=0,h3=0,h4=0;

  ev.eval_bjs(bijsubset,vrbs);
  ev.eval_pri(preimage,vrbs);
  ev.eval_irt(is_recurrent_tree,vrbs);
  ev.eval_otr(ordered_tree,vrbs);

  for (int j=0; j<30; j++) {
    seed = rand()%1000;
    if (j==0) seed = 123;
    h1 = ev.evalr_bjs(bijsubset,seed,vrbs); // para SEED=123 debe dar H=907
    h2 = ev.evalr_pri(preimage,seed,vrbs); // para SEED=123 debe dar H=631
    h3 = ev.evalr_irt(is_recurrent_tree,seed,vrbs); // para SEED=123 debe dar H=794
    h4 = ev.evalr_otr(ordered_tree,seed,vrbs); // para SEED=123 debe dar H=069

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d H4=%03d\n",
           seed,h1,h2,h3,h4);
  }

  return 0;
}
