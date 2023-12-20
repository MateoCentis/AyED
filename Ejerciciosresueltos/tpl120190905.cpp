#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   #pareto:# Se dice que un punto #x=(x1,x2,..,xn)#
   #n-dimensional domina a otro punto y=(y1,y2,..,yn)# si se
   cumple que, todas las componentes de #x# son menores o
   iguales que las de #y# y al menos una de ellas es menor estricta. 
   Dado un conjunto de vectores encontrar el frente de
   Pareto del conjunto, es decir todos los #x# tales que no
   son dominados por otro vector del conjunto.

   #merge-kway:# Implementar una funcion void
   #merge_kway(vector< queue<int> > &qords,queue<int> &merged)# que dado
   un vector de colas ordenadas #ordqs,# obtener la cola #merged#
   resultante de la fusion de todas las colas en una sola, de forma de
   que los elementos siguen ordenadas. 

   #is-balanced:# Dado un string #expr,# implementar una funcion
   #bool is_balanced(string &expr);# que determine si todos los 
   pares de parentesis, llaves y corchetes estan bien balanceados.

   [Tomado en el Trabajo Practico de Laboratorio Nro 1
   (TPL1) de 2019-09-05].
   keywords: lista, pila, cola

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

bool domina(vector<int> x, vector<int> y){
  int ndim = x.size();
  bool flag = false;
  for(int k=0;k<ndim;k++){
    if (x[k] < y[k]) flag = true;
    if (x[k] > y[k]) break;
  }
  return flag;
}

list<vector<int>> Pareto(list<vector<int>>&L){
  list<vector<int>> Lout;
  list<vector<int>>::iterator it = L.begin();
  while(it!=L.end()){
    bool es_dominado = false;
    list<vector<int>>::iterator it2 = L.begin();
    while(it2!=L.end()){
      if(domina(*it2,*it)){
        es_dominado = true;
        break;
      }
      it2++;
    }
    if(!es_dominado) Lout.push_back(*it);
    it++;
  }
  return Lout;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void merge_kway(vector< queue<int> > &qords,
                queue<int> &merged) {
  merged = queue<int>();
  while (true) {
    int minindx=-1, minfront;
    int nq = qords.size();
    for (int j=0; j<nq; j++) {
      queue<int> &q = qords[j];
      if (!q.empty()) {
        if (minindx<0 || q.front()<minfront) {
          minindx = j;
          minfront = q.front();
        }
      }
    }
    // Todas las colas esan vacias
    if (minindx<0) return;
    merged.push(minfront);
    qords[minindx].pop();
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void merge_kway2(vector< queue<int> > &qords,
                queue<int> &merged) {
  merged = queue<int>();
  while (true) {
    auto q = qords.begin();
    while (q!=qords.end()) {
      if (q->empty()) qords.erase(q);
      else q++;
    }
    if (qords.empty()) return;
    
    int minindx=-1, minfront;
    int nq = qords.size();
    for (int j=0; j<nq; j++) {
      queue<int> &q = qords[j];
      if (minindx<0 || q.front()<minfront) {
        minindx = j;
        minfront = q.front();
      }
    }
    merged.push(minfront);
    qords[minindx].pop();
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool is_balanced(string &c) {
  stack<char> s;
    
  for(unsigned int i=0; i<c.length(); i++){
    if(c[i]=='(' || c[i]=='{' || c[i]=='[') s.push(c[i]);
    else if(c[i]==')') {
      if (!s.empty() && s.top()=='(') s.pop();
      else return false;
    } else if(c[i]=='}') {
      if (!s.empty() && s.top()=='{') s.pop();
      else return false;
    } else if(c[i]==']') {
      if (!s.empty() && s.top()=='[') s.pop();
      else return false;
    }
  }
  return s.empty();
}
 
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

int main() {

  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  cout << "seed: 123" << endl;
  do {
    ev.eval<1>(Pareto,vrbs);
    h1 = ev.evalr<1>(Pareto,seed,vrbs);

    ev.eval<2>(merge_kway,vrbs);
    h2 = ev.evalr<2>(merge_kway,seed,vrbs);
    
    ev.eval<3>(is_balanced,vrbs);
    h3 = ev.evalr<3>(is_balanced,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    cout << endl << "Siguiente seed: ";
  } while (cin>>seed);

  return 0;
}
