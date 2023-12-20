#include "eval.hpp"
#include <cstdlib>
#include <stack>

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
  #mkmtree:# Escribir una funcion que dados dos enteros
  positivos #m#, #k#, construye un AOO, tal que tiene a #m#
  en la raiz y dado un nodo #n# los hijos de #n# son
  #(*n)-j*k#, mientras sean no negativos. Por ejemplo si
  #m=10,k=3# debe retornar #T=(10 (7 (4 1) 1) (4 1) 1)#.

  #has-equal-path:# Dado un arbol ordenado orientado (AOO)
  escribir una funcion predicado que determina si contiene
  un camino de valores iguales que va desde la raiz a una
  hoja con todos elementos iguales. 

  #pancake-sort:# Dada una pila de numeros #S#, implementar
  el algoritmo de ordenamiento Pancake Sort, el cual ordena 
  la pila solo haciendo operaciones en las cuales se invierte 
  un rango contiguo de elementos en el tope de la pila. 

  #count-cycles:# Dado un #map<int,int> &M# que representa
  una permutacion (es decir tal que el conjunto de las
  claves es igual al conjunto de las imagenes) escribir una
  funcion que cuenta sus ciclos. 

  [Tomado en el Recup Trabajo Practico de Laboratorio Nro 2 
     (TPL2R) de 2014-10-16].  
  keywords: arbol orientado,cola,pila,grafo,correspondencia

FIN DE DESCRIPCION */

using namespace aed;
using namespace std;

typedef tree<int> tree_t;
typedef tree<int>::iterator node_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void mkmtree(tree_t &T,node_t n, int k) {
  node_t c = n.lchild();
  int wc = *n-k;
  while (wc>0) {
    c = T.insert(c,wc);
    mkmtree(T,c,k);
    c++; wc -= k;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void mkmtree(tree_t &T,int m,int k) {
  T.clear();
  T.insert(T.begin(),m);
  mkmtree(T,T.begin(),k);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool has_equal_path(tree_t &T,node_t n) {
  if (n==T.end()) return true;
  node_t c = n.lchild();
  if (c==T.end()) return true;
  while (c!=T.end()) {
    if (*c==*n && has_equal_path(T,c)) return true;
    c++;
  }
  return false;
}

bool has_equal_path(tree_t &T) {
  return has_equal_path(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
//Le pasas una pila y te devuelve la posicion al valor maximo desde el
//principio de la pila hasta la n-esima posicion
int pos_of_max(stack<int> s, int n){
  if(n==1) return 1;
	
  int maxi = s.top(), pos = 0;
  s.pop();
	
  for(int i = 1 ; i < n ; i++){
    if(s.top() > maxi){
      maxi = s.top();
      pos = i;
    }
    s.pop();
  }
  return pos;
}

//Le pasas una pila y 2 enteros. Se encarga de primero invertir los primeros
//n valores de la pila, y luego se encarga de invertir los j valores de la
//pila, previamente habiendo invertido los primeros n, asi se simula el
//algoritmo de panquequeado.
stack<int> flip(stack<int> s, int n, int j){
  queue<int> q1,q2;
  stack<int> s2,s3;
	
  for(int i = 0 ; i < n ; i++){
    q1.push(s.top());
    s.pop();
  }
	
  for(int i = n ; i < j ; i++){
    q2.push(s.top());
    s.pop();
  }
	
  while(!q1.empty()){
    q2.push(q1.front());
    q1.pop();
  }
	
  while(!q2.empty()){
    s.push(q2.front());
    q2.pop();
  }
	
  return s;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void pancake_sort(stack<int> &s){
  int n;
  //a lo mas, va a requerir s.size panquequeadas
  for(int i = s.size() ; i > 0 ; i--){ 
    //se obtiene el mayor de la pila hasta la i-esima posicion
    n = pos_of_max(s,i);
    //se realiza el panquequeo para dejar ese mayor encontrado
    //en la ultima posicion posible
    s = flip(s,n,i);
    //		cout<<"Iteracion "<< s.size()-i<< ": " ;
    ////		mostrar_stack(s);
    //		cout<<endl;
  }
}

#define mii map<int,int>
#define miit map<int,int>::iterator

int count_cycles(mii &m){
  int cont = 0,first_pos,primero,segundo;
  miit mit = m.begin();
  //recorre todo el mapa, y para cada par, se fija si encuentra un ciclo
  while(mit!=m.end()){
    first_pos = mit->first;
    primero = mit->second;
    int cont_aux = m.size(); //por si las moscas no corta con algun ciclo, igualmente el erase me lo evitaria
    //el while se fija si se puede formar un ciclo
    while(first_pos != primero && cont_aux>0 ){
      if(m.find(primero)==m.end()) break;
      segundo = primero;
      primero = m[segundo];
      //elimino del mapa para evitar contar ciclos repetidos
      m.erase(segundo);
      cont_aux--;
    }
    if(first_pos == primero) cont++;
    mit++;
  }
  return cont;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0,h4=0;

  ev.eval1(mkmtree,vrbs);
  ev.eval2(has_equal_path,vrbs);
  ev.eval3(pancake_sort,vrbs);
  ev.eval4(count_cycles,vrbs);

  for (int j=0; j<30; j++) {
    seed = rand()%1000;
    if (j==0) seed = 123;
    h1 = ev.eval1r(mkmtree,seed); // para SEED=123 debe dar H1=170
    h2 = ev.eval2r(has_equal_path,seed); // para SEED=123 debe dar H2=959
    h3 = ev.eval3r(pancake_sort,seed); // para SEED=123 debe dar H3=489
    h4 = ev.eval4r(count_cycles,seed); // para SEED=123 debe dar H4=392
    printf("SEED=%03d -> HASH1=%03d, HASH2=%03d, "
           "HASH3=%03d, HASH4=%03d\n",
           seed,h1,h2,h3,h4);
  }

  return 0;
}
