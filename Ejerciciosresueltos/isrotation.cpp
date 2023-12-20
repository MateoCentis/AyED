// $Id$

/* 
   COMIENZO DE DESCRIPCION 
   __USE_WIKI__

   Determinar si una correspondencia !+map<int,int> M+ es una
   \emph{``rotacion''} es decir, una permutacion tal que cada elemento
   del conjunto de las claves es asignado al siguiente elemento, en
   cierto orden. 
   [Tomado en primer parcial 2011-09-15].
   keywords: correspondencia, lista
    
   FIN DE DESCRIPCION 
*/

  // Por ejemplo !+M={1->3,2->8,3->5,4->2,5->4,8->1}+
  // corresponde a una rotacion en orden
  // !+(1,3,5,4,2,8)+.\\
  // \textbf{Consigna:} escribir una funcion 
  // !+bool is_rotation(map<int,int> &M,list<int> &order);+
  // que determinar si !+M+ es una rotacion y en ese caso devuelve en
  // !+L+ la lista de los elementos de !+M+ en el orden dado por la
  // correspondencia.\\
  // \textbf{Ayuda:} Generar la lista !+L+ aplicando sucesivamente
  // $x_{i+1} = M(x_i)$ a partir de cualquier clave inicial $x_0$. La
  // correspondencia es una rotacion si
  // \begin{itemize}
  //   \compactlist 
  // \item El valor del contradominio $x_{i+1}$ siempre es una clave. 
  // \item Los elementos de la secuencia son todos distintos, salvo
  //   para el ultimo elemento, cuando $x_n=x_0$. 
  // \end{itemize}
  // %
  // (\textbf{Nota:} Utilizar una correspondencia auxiliar para saber cuales claves ya
  // fueron visitadas.)

// -----------------------------------------------------------------
#include <cassert>
#include <cstdio>
#include <cmath>
#include <map>
#include <list>
#include <algorithm>
#include "./util.h"
using namespace std ;

typedef map<int,int> map_t;

bool is_rotation(map_t &M,list<int> &order) {
  order.clear();
  if (M.empty()) return true;
  map_t::iterator p = M.begin();
  map_t aux;
  while (p!=M.end()) {
    int key = p->first;
    // printf("%d ",key);
    if (aux.find(key)!=aux.end()) break;
    aux[key] = 1;
    order.insert(order.end(),key);
    p = M.find(p->second);
  }
  if (order.size()==M.size()) return true;
  else {
    order.clear();
    return false;
  }
}

// Esta version es in-place y O(n). Generamos la secuencia x_{n+1} =
// M[x_n]. Como antes, si algun valor no es clave entonces no es
// rotacion.  Si llegamos a x_0 antes del paso n, no es rotacion. Si
// llegamos exactamente en el paso n entonces SI es rotacion. Esto
// es asi ya que entonces esta garantizado que todas las claves
// recorridas fueron distintas. Supongamos que en la secuencia se
// hubieran repetido dos claves, por ejemplo
// {x_j,x_{j+1},...,x_{j+k}=x_j} entonces a partir de ahi esa
// subsecuencia {x_{j},...,x_{j+k-1}} se repetiria
// indefinidamente. Pero sabemos que esa subsecuencia NO contiene a
// x_0 entonces nunca volveria a x_0.
bool is_rotation2(map_t &M,list<int> &order) {
  order.clear();
  if (M.empty()) return true;
  map_t::iterator p = M.begin();
  int start = p->first;
  for (int j=0; j<M.size()-1; j++) {
    p = M.find(p->second);
    if (p==M.end() || p->first==start) return false;
  }
  return p->second==start;
}

void printmap(const map_t &M,const char *s=NULL) {
  map_t::const_iterator p = M.begin();
  if (s) printf("%s: ",s);
  printf("{");
  while (p!=M.end()) {
    printf("%d->%d ",p->first,p->second);
    p++;
  }
  printf("}\n");
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  for (int k=0;k<20; k++) {
    // Crea una carrespondencia aleatoria
    int N = 5;
    vector<int> v(N);
    for (int j=0; j<N; j++) v[j] = j;
    random_shuffle(v.begin(),v.end());
    map_t M;
    for (int j=0; j<N; j++) M[j] = v[j];
    printmap(M,"M");
    list<int> order;
    int ok1 = is_rotation(M,order);
    int ok2 = is_rotation2(M,order);
    printf("is rotation? %d\n",ok1);
    printf("is_rotation2 OK? %d ",ok1==ok2);
    if (!order.empty()) {
      printf("order: ( ");
      list<int>::iterator p = order.begin();
      while (p!=order.end())
        printf("%d ",*p++);
      printf(")");
    }
    printf("\n----------\n");
  }
  return 0;
}
