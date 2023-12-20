#include "eval.hpp"
#include <climits>
#include <cstdlib>
#include <stack>

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   #tree2count:# Dado un arbol #T# conntruye una lista #L# 
   que contiene en preorder la cantidad de nodos de cada 
   subarbol de #T#. E.g. #T=(3 (2 1 5) (7 8))# da #L=(6 3 1 1 2 1)#. 
   Decimos que #T# es un arbol de conteo si en los nodos tiene la 
   cantidad de nodos de su subarbol. 

   #count2tree:# Es la inversa de #tree2count#, dada la lista de
   conteo reconstruye el arbol. No recupera los valores de los
   nodos del arbol sino que en los nodos quedan las conteos de hijos. 
   E.g. #L=(6 3 1 1 2 1)#.  #T=(6 (3 1 1) (2 1))#. 

   Notemos que #count2tree(tree2count(count2tree(T)))=count2tree(T)#. 
   Es decir #count2tree# es la inversa de #tree2count# asumiendo que #T# 
   ya es un arbol de conteo. 

   #hasnpath:# Dado un grafo #G#, dos vertices #a,b#, y un entero #n>=0# 
   determina si existe un camino (con posibles nodos repetidos) de 
   longitud #n# de #a# a #b#.

   #key2abbrev:# Dado una serie de strings #keys# encontrar para cada 
   uno de ellos un prefijo unico #abb# lo mas corto posible. Por ejemplo
   #(mesa metro multa) -> (me met m)#. 

   [Tomado en el Recup Trabajo Practico de Laboratorio Nro 2
   (TPL2R) de 2015-10-22].  
   keywords: arbol orientado, grafo, correspondencia

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

typedef tree<int>::iterator node_t;
typedef tree<int>::const_iterator cnode_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// TREE2COUNT: version 1, como se explica en la ayuda del TPL.
// Por composicion de mkcount y preorder
void mkcount(tree<int> &T,node_t n) {
  node_t c = n.lchild();
  int ncount =1;
  while (c!=T.end()) {
    // Aplica recursivamente mkcount a los hijos
    mkcount(T,c);
    // Acumula el count de n
    ncount += *c++;
  }
  // Pisa el valor de n
  *n = ncount;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// listado en preorder
void preorder(tree<int> &T,tree<int>::iterator n,list<int> &L) {
  L.insert(L.end(),*n);
  tree<int>::iterator c = n.lchild();
  while (c!=T.end()) {
    preorder(T,c,L);
    c = c.right();
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// No se hacen wrappers para mkcount y preorder ya que
// las usamos internameente en tree2count
void tree2count(tree<int> &T,list<int> &L) {
  mkcount(T,T.begin());
  preorder(T,T.begin(),L);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Version 2: Lo hace directamente de una sola pasada en T,
// De yapa no modifica a T, por lo tanto lo podemos declarar como const.
// retorna por Ln la lista de los count del subarbol de n (en preorder)
void tree2count2(const tree<int> &T,
                cnode_t n,list<int> &Ln) {
  if (n==T.end()) return;
  // Este valor del frente corresponde a n, por ahora
  // lo ponemos en 1 pero despues vamos a ir acumulando
  Ln.push_back(1);
  cnode_t c = n.lchild();
  while (c!=T.end()) {
    // Esta es la lista de c
    list<int> Lc;
    // Aplica recursivamente
    tree2count2(T,c++,Lc);
    // Acumula en el primer elemento (corresponde a n)
    Ln.front() += Lc.front();
    // Splicea todo Lc al final de Ln
    Ln.splice(Ln.end(),Lc);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void tree2count2(tree<int> &T,list<int> &L) {
  tree2count2(T,T.begin(),L);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Version 1: No usa listas auxiliares para Lc
node_t count2tree(list<int> &L,tree<int> &T,node_t n) {
  if (L.empty()) return n;
  int count = L.front();
  L.pop_front();
  n = T.insert(n,count); count--;
  node_t c = n.lchild();
  while (count>0) {
    count -= L.front();
    c = count2tree(L,T,c);
    c++;
  }
  assert(count==0);
  return n;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void count2tree(list<int> &L,tree<int> &T) {
  count2tree(L,T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
node_t count2tree2(list<int> &L,tree<int> &T,node_t n) {
  int count = L.front();
  L.pop_front();
  n = T.insert(n,count);
  node_t c = n.lchild();
  while (!L.empty()) {
    int ccount = L.front();
    list<int> Lc;
    for (int j=0; j<ccount; j++) {
      Lc.push_back(L.front());
      L.pop_front();
    }
    c = count2tree2(Lc,T,c);
    c++;
  }
  return n;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Version 1: Usa una lista auxiliar para Lc
void count2tree2(list<int> &L,tree<int> &T) {
  count2tree2(L,T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool hasnpath(map<int,list<int> >&M, int a, int b, int n){
  if(M.find(a)==M.end()) return false;
  // Corta la recursion
  if(n==0) return (a==b);
  // Recorre los vecinos de `a' y chequea si alguno tiene
  // un camino de longitud n-1 con `b'
  list<int> &L = M[a];
  for(list<int>::iterator it=L.begin();it!=L.end();it++){
    if(hasnpath(M, *it, b, n-1)) return true;
  }
  return false;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void key2abbrev(map<string,string> &abbrevs) {
  // Este auxiliar contendra al final la inversa de abbrevs
  map<string,string> abb2key;
  // Recorre las asignaciones de abbrevs
  map<string,string>::iterator q = abbrevs.begin();
  while (q!=abbrevs.end()) {
    // Clave
    const string &key = q->first;
    // Longitud de la clave
    int sz = key.size();
    // Va probando con todos los prefijos de longitud 1 a sz
    // hasta encontrar uno que no haya sido asignado 
    for (int len = 1; len<=sz; len++) {
      // Prefijo de longitud len
      string abbrev = key.substr(0,len);
      // Se fija si ya fue asignado
      if (abb2key.find(abbrev)==abb2key.end()) {
        // No fue asignado. Lo carga en abbrevs y en abb2key
        q->second = abbrev;
        // cout << "key,abbrev " << key << " " << abbrev << endl;
        abb2key[abbrev] = key;
        break;
      }
    }
    q++;
  }
  // Esto deberia ser verdad ya que fuimos chequeando que
  // las abbrevs eran unicas
  assert(abbrevs.size()==abb2key.size());
}

int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0,h4=0;

  ev.eval1(tree2count,vrbs);
  h1 = ev.evalr1(tree2count,seed,vrbs);

  ev.eval2(count2tree,vrbs);
  h2 = ev.evalr2(count2tree,seed,vrbs);

  ev.eval3(hasnpath,vrbs);
  h3 = ev.evalr3(hasnpath,seed,vrbs);

  ev.eval4(key2abbrev,vrbs);
  h4 = ev.evalr4(key2abbrev,seed,vrbs);

  // Para S=123 debe dar -> H1=626 H2=303 H3=334 H4=512
  printf("S=%03d -> H1=%03d H2=%03d H3=%03d H4=%03d\n",
         seed,h1,h2,h3,h4);

  return 0;
}
