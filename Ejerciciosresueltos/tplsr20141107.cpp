#include "eval.hpp"
#include <climits>
#include <cstdlib>
#include <stack>

using namespace aed;
using namespace std;

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__


   #isomorph Dos arboles binarios #B1,# #B2# son isomorfos
   si se pueden aplicar una serie de inversiones entre los
   hijos derechos e izquierdos de los nodos de #B2# de manera
   que quede un arbol semejante a #B1#, es decir que tiene la
   misma estructura.

   #has-sum# Dado un #set<int># y un entero #M# determinar si
   existe un subconjunto de #S# que sume exactamenet #M.#

   #find-shift# Dadas dos listas #L1# #L2# tal que #L2# es
   una permutacion ciclica de #L1# determinar el shift. 

   [Tomado en el Super Recup TPL 
   (TPLSR) de 2015-11-11].  
   keywords: lista, conjunto, arbol binario

FIN DE DESCRIPCION */

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
typedef btree<int>::iterator btn_t;
bool btisomorph(btree<int> &B1,btn_t n1,
                btree<int> &B2,btn_t n2) {
  if ((n1==B1.end()) != (n2==B1.end())) return false;
  if (n1==B1.end()) return true;
  btn_t 
    l1=n1.left(),
    l2=n2.left(),
    r1=n1.right(),
    r2=n2.right();
  if (btisomorph(B1,l1,B2,l2) && btisomorph(B1,r1,B2,r2)) return true;
  if (btisomorph(B1,l1,B2,r2) && btisomorph(B1,r1,B2,l2)) return true;
  return false;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool btisomorph(btree<int> &B1,btree<int> &B2) {
  return btisomorph(B1,B1.begin(),B2,B2.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool has_sum(set<int> &S, int M) {
  if (S.find(M)!=S.end()) return true;
  set<int>::iterator q = S.begin();
  while (q!=S.end()) {
    if (*q<M) {
      set<int> S1 = S;
      S1.erase(*q);
      if (has_sum(S1,M-*q)) return true;
    }
    q++;
  }
  return false;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int find_shift(list<int> &L1,list<int> &L2) {
  int N = L1.size();
  assert(L2.size()==N);
  for (int j=0; j<N; j++) {
    list<int>::iterator 
      q1=L1.begin(),
      q2=L2.begin();
    for (int k=0; k<j; k++) q1++;
    int ok=1;
    while (q2!=L2.end()) {
      if (*q1!=*q2) { ok=0; break;}
      q1++; q2++; if (q1==L1.end()) q1 = L1.begin();
    }
    if (ok) return j;
  }
  assert(0);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  ev.eval1(btisomorph,vrbs);
  ev.eval2(has_sum,vrbs);
  ev.eval3(find_shift,vrbs);

  for (int j=0; j<30; j++) {
    seed = rand()%1000;
    if (!j) seed = 123;
    h1 = ev.evalr1(btisomorph,seed,0); // para SEED=123 debe dar H=759
    h1 = ev.evalr1(btisomorph,seed,0); // para SEED=123 debe dar H=759
    h2 = ev.evalr2(has_sum,seed,0);    // para SEED=123 debe dar H=288
    h3 = ev.evalr3(find_shift,seed,0); // para SEED=123 debe dar H=257
    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
  }
  return 0;
}
