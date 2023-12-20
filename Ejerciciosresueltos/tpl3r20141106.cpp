#include "eval.hpp"
#include <climits>
#include <cstdlib>
#include <stack>

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   #only1:#
   Dado un vector de conjuntos #VS,# determinar el conjunto #S1# de todos
   aquellos elementos que estan en uno y solo uno de ellos. Por ejemplo,
   si #VS=[{0,1,2,3},{2,3,4,5}],# entonces #S1={0,1,4,5}.# 

   #included:# Dada un vector de conjuntos, escribir una
   funcion predicado, que determina si los conjuntos del
   vector son subconjuntos propios en forma consecutiva. Es
   decir, si #S_j\subset S_{j+1}# para
   #j=0,...,n-2#. (Recordar que #A\subset B# indica
   inclusion *propia,* es decir #A\subseteq B# y #A\neq B$.#

   #diffh:# Escribir una funcion predicado que determina si
   el arbol esta balanceado, es decir si para cada nodo
   interno del AB la diferencia de alturas de los subarboles
   de su hijo izquierdo y derecho difieren en a lo maximo 1.

   #onechild:# Dado una arbol binario (AB), determinar
   cuantos nodos de tienen exactamente un solo hijo
   *(single child count).*

   [Tomado en el Recup Trabajo Practico de Laboratorio Nro 3 
   (TPL3R) de 2014-11-06].  
   keywords: arbol binario,conjunto

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void only1(vector< set<int> > &VS,set<int> &S1) {
  S1.clear();
  set<int> Sall,s1,s2;
  vector< set<int> >::iterator 
    q = VS.begin();
  while (q!=VS.end()) {
    s2.clear();
    set_difference(S1.begin(),S1.end(),
		   q->begin(),q->end(),
		   inserter(s2,s2.begin()));
    S1 = s2;

    set_difference(q->begin(),q->end(),
		   Sall.begin(),Sall.end(),
		   inserter(S1,S1.begin()));

    s1.clear();
    set_union(q->begin(),q->end(),
	      Sall.begin(),Sall.end(),
	      inserter(s1,s1.begin()));
    Sall = s1;
    q++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool included(vector< set<int> > &VS) {
  vector<set<int> >::iterator p = VS.begin();
  if (p == VS.end()) return true;

  set<int> tmp;
  while (p != VS.end()) {
    // *p es A[j] y *q es A[j+1]
    vector<set<int> >::iterator q = p; q++;

    // Aseguramos que p y
    // q son dereferenciables
    if (q==VS.end()) break;

    // Verifica que A[j] incluido en A[j+1]
    // es decir, tmp = A[j]-A[j+1] es vacio
    set_difference(*p,*q,tmp);
    if (!tmp.empty()) {
      // printf("NO incluye!!\n");
      return false;
    }

    // Verifica que la inclusion es propia
    // es decir, tmp = A[j+1]-A[j] NO es vacio
    set_difference(*q,*p,tmp);
    if (tmp.empty()) {
      // printf("Inclusion NO propia!!\n");
      return false;
    }

    p=q;	   
  }
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
typedef btree<int>::iterator bnode_t;
bool diffh(btree<int> &T,bnode_t n,int &height) {
  height = -1;
  if (n==T.end()) return true;
  bnode_t 
    ql = n.left(),
    qr = n.right();
  int hl,hr;
  height = INT_MAX;
  if (!diffh(T,ql,hl)) return false;
  if (!diffh(T,qr,hr)) return false;
  height = (hl>hr ? hl : hr)+1;
  return abs(hl-hr)<=1;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool diffh(btree<int> &T) {
  int height;
  return diffh(T,T.begin(),height);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int onechild(btree<int> &T, bnode_t n) {
  if (n==T.end()) return 0;
  bnode_t l=n.left(), r=n.right();
  int nchild = (l==T.end()) + (r==T.end());
  return (nchild==1) + onechild(T,l) + onechild(T,r);
}
             
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
int onechild(btree<int> &T) {
  return onechild(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0,h4=0;

  ev.eval1(only1,vrbs);
  ev.eval2(included,vrbs);
  ev.eval3(diffh,vrbs);
  ev.eval4(onechild,vrbs);

  h1 = ev.evalr1(only1,seed,0); // para SEED=123 debe dar H=352
  h2 = ev.evalr2(included,seed,0); // para SEED=123 debe dar H=318
  h3 = ev.evalr3(diffh,seed,0); // para SEED=123 debe dar H=304
  h4 = ev.evalr4(onechild,seed,0); // para SEED=123 debe dar H=204

  printf("S=%03d -> H1=%03d H2=%03d H3=%03d H4=%03d\n",
         seed,h1,h2,h3,h4);
  return 0;
}
