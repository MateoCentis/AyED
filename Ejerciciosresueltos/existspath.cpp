#include <iostream>
#include <map>
#include <list>
#include <queue>
#include <vector>
#include <stack>
using namespace std;


/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Escribir una funcion
   #bool exists_path (map <int, list <int> > &M, int m, int n);# 
   que dado un mapa #M#, que representa un grafo dirigido
   determina si existe un camino de #m# a #n# en el grafo.
   [Tomado en el 1er parcial de 2014-09-18].  
   keywords: lista, correspondencia, cola, grafo

FIN DE DESCRIPCION */

/* 

Sebastian un buen dia queda en juntarse para comer un asado
en la casa de Santiago.  Pero resulta que si bien son buenos
para organizar reuniones, no son buenos para recordar
fechas, y olvidaron que ese dia habran varios desfiles por
el carnaval, quedando solo algunas calles de un unico
sentido habilitadas para los vehiculos.  Sebastian es un
conductor muy prudente, y no se arriesgara a que lo multen,
por lo que solo tomara los caminos en el sentido correcto.
Entonces con rapidez arma un mapa (grafo) de las calles
habilitadas que tendra a las intersecciones de las calles
como nodos y a las calles como aristas. Seba le pide a usted
(ya que el esta muy ocupado haciendo la ensalada para la
cena) que escriba una funcion bool exists_path (map <int,
list <int> > &M, int m, int n); que dado un mapa M, le haga
saber si existe al menos un camino que el pueda hacer desde
su casa (ubicada en la interseccion m) hacia la casa de
Santiago, que esta en la interseccion n.  ¿Podran juntarse,
o deberan posponer la reunion?  Ejemplo: Dado un mapa M

1 >( )
2 >( 1, 5, 8 )
4 >( 1, 7 )
5 >( 4 )
7 >( )
8 >( 1 )

Entonces si m=2, y n=7 el resultado debe ser verdadero.

FIN DE DESCRIPCION */

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// VERSION ITERATIVA #1
// Esta solucion propone el uso de una cola para almacenar
// los nodos que deben ser visitados
bool exists_path1( map < int , list<int> > &M, int m, int n){
  // Empleamos una cola auxiliar que guarde los nodos que
  // deberemos recorrer
  queue<int> q;
  // Empleamos un vector de booleanos para guardar los nodos
  // visitados. De este modo si el grafo tiene bucles, no
  // cae en lazos infinitos. La cantidad de elementos de
  // este vector sera igual a la clave mas grande almacenada
  // en la correspondencia ((--M.end())->first)+1
  vector<bool> visitados(((--M.end())->first)+1,false);
  // variable que almacena el nodo que esta siendo visitado actualmente
  int actual;
  // Insertamos el elemento M. Recordar que tanto m como n
  // suponemos que existen en el grafo
  q.push(m);
	
  // Iteramos mientras queden nodos por visitar
  while(!q.empty()){
    actual = q.front(); // obtenemos el primer nodo de la cola a analizar
    if(actual == n) return true; // si llegamos al nodo buscado, retornamos true
    visitados[actual] = true; // marcamos el nodo como visitado
    q.pop(); // eliminamos este nodo ya que no necesitamos volver a recorrerlo
    // Ahora, para el nodo que se esta visitando, recorremos
    // la lista de los nodos vecinos
    list<int>::iterator it = M[actual].begin();
    while(it!=M[actual].end()){
      // si el nodo ya fue visitado, lo ignoramos. SI no fue
      // visitado, lo agregamos a la cola para recorrelo
      // luego
      if(!visitados[*it])
        q.push(*it);
      it++;
    }
  }
  // finalmente si se han recorrido todos los nodos que
  // estan conectados a "n" y nunca se llego a "m", entonces
  // retornamos false
  return false;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// VERSION ITERATIVA #2
// Esta solucion propone el uso de dos correspondencias
// auxiliares para ir guardando los nodos visitados.  Se
// podria ver como el problema de coloreo de grafos, donde
// vamos "pintando" los nodos que visitamos.  La condicion
// de corte se da cuando pintamos todos los nodos posibles y
// ya no es posible expandirse mas.
bool exists_path2(map <int, list<int> > &M, int m, int n) {
  // Correspondencias auxiliares: M1 guardamos los nodos
  // "pintados", y M2 nos servira para saber cuando ya no
  // podemos expandirnos mas. M1 indica el estado actual de
  // coloreo del grafo, mientras que M2 representa el estado
  // de coloreo del grafo en una iteracion anterior.
  map <int, bool> M1, M2;
  list <int>::iterator itL = M[m].begin();
  // agregamos a la correspondencia auxiliar el nodo desde
  // donde partimos (es decir, "pintamos" el nodo de
  // partida)
  M1[m] = true;
  // mientras sea posible expandirse, iteramos
  while (M1 != M2) {

    // esta linea es necesaria para identificar cuando ya no
    // es posible expandirse. Si M1 = M2, entonces ya no hay
    // nodos por recorrer.
    M2=M1;	
    map <int,bool >::iterator itM1 = M1.begin();
    // para todos los nodos "pintados", recorremos la lista
    // de nodos vecinos a estos
    while (itM1 != M1.end()) {
      list <int>::iterator itL = M[itM1->first].begin();
      while (itL != M[itM1->first].end()) {
        // pintamos todos los nodos vecinos al nodo donde
        // estamos actualmente
        M1[*itL] = true ;
        ++itL;
      }
      ++itM1;
    }
  }
  // Finalmente nos expandimos tanto como fue posible
  // pintando todos los nodos a los cuales se podia llegar
  // desde "m". Entonces simplemente devolvemos el valor
  // auxiliar de M1. Si "n" nunca fue visitado, entonces no
  // esta pintado. Es decir, no se encuentra en M1. Entonces
  // devuelve falso.
  return M1[n];
}



//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// VERSION RECURSIVA #1
// Funcion recursiva que no detecta bucles. Esta version es
// de las mas sencillas
bool exists_path3(map <int, list <int> > &M, int m, int n) {
  // La condicion de corte es cuando "m" es igual a "n".
  if (m == n) return true;
  // Si no es el nodo de destino, entonces recorremos todos
  // los nodos a los cuales se puede llegar desde "m"
  // llamando a esta misma funcion para cada uno de sus
  // vecinos:
  list <int>::iterator itL = M[m].begin();
  while (itL != M[m].end()) {
    // cuando llamamos a la funcion, si se encuentra el
    // nodo, retorna true. De lo contrario, sigue buscando
    // para el resto de los vecinos.
    if (exists_path3(M, *itL, n))
      return true;
    ++itL;
  }
  // Si no se pudo llegar por ninguno de los caminos
  // posibles al nodo "n", entonces retorna falso.
  return false;
}



//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// VERSION RECURSIVA #2
// Funcion recursiva que detecta ciclos y evita caer en
// lazos infinitos.  Para guardar un vector de los nodos
// visitados, usaremos una funcion "wrapper" que nos sirva
// para invocar a la funcion recursiva con un parametro
// extra.

// funcion recursiva:
bool exists_path_interno( map < int , list<int> > &M, int m, int n, vector<bool> &visit);

// funcion wrapper
bool exists_path4( map < int , list<int> > &M, int m, int n){
  // Funcion que es llamada por nosotros desde el
  // main(). Esta funcion solo crea una estructura auxiliar
  // para ir guardando los nodos visitados. La cantidad de
  // elementos que contene el vector correspondera al numero
  // del elemento mas grande que este almacenado en el map.
  vector<bool> visitados = vector<bool>((--M.end())->first,false);
  // Llama a la funcion recursiva
  return exists_path_interno(M,m,n,visitados);
}

bool exists_path_interno( map < int , list<int> > &M, int m, int n, vector<bool> &visit){
  // Si el nodo ya fue visitado, retornamos falso (porque
  // sabemos que no hay nada por este camino)
  if(visit[m]) return false;
  // Si llegamos al nodo que estamos buscando, retornamos
  // true.
  if(m==n) return true;
  // Si m!=n y no es el nodo que buscamos, entonces lo
  // marcamos como visitado
  visit[m]=true;
  // Y por cada uno de los vecinos, llamamos a la funcion de
  // forma recursiva
  list<int>::iterator itl = M[m].begin();
  while( itl!=M[m].end() ){
    if(exists_path_interno(M,*itl,n,visit))
      return true;
    itl++;
  }
  // Si no se pudo llegar por ninguno de los caminos
  // posibles al nodo "n", entonces retorna falso.
  return false;
}

// En la funcion main generamos los casos de prueba.  Se
// proponen dos correspondencias (una que corresponde al
// enunciado del examen), y el segundo un grafo mas complejo
// para probar de forma un poco mas intensiva el
// funcionamiento de los algoritmos.
int main() {
  cout<<"\n* Para el mapa propuesto en el examen:\n";
  // Grafo propuesto en el enunciado del examen:
  //	1 > ( )
  //	2 > ( 1, 5, 8 )
  //	4 > ( 1, 7 )
  //	5 > ( 4 )
  //	7 > ( )
  //	8 > ( 1 )
	
  map <int, list <int> > M1;
  M1[1];
  M1[2].push_back(1);
  M1[2].push_back(5);
  M1[2].push_back(8);
  M1[4].push_back(1);
  M1[4].push_back(7);
  M1[5].push_back(4);
  M1[7];
  M1[8].push_back(1);
	
  int desde = 2;
  int hasta = 7;
	
  // lo escribimos de este modo para comprobar que todas las
  // soluciones sean unicas.
  if (exists_path1(M1,desde,hasta) and exists_path2(M1,desde,hasta) and exists_path3(M1,desde,hasta) and exists_path4(M1,desde,hasta))
    cout<<"SI: Existe al menos una forma de llegar de "<<desde<< " a "<<hasta<<endl;
  else
    cout<<"NO: No hay forma de llegar de "<<desde<<" a "<<hasta<<endl;
	
  //	---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // Propuesta de un grafo mas complejo con bucles.  Armarlo
  // en papel para comprobar. En este retiramos
  // exists_path3, ya que es la unica de las soluciones
  // propuestas que no admiten ciclos.
  //	1 > ( 7 )
  //	2 > ( 1 )
  //	3 > ( 2, 9 )
  //	4 > (  )
  //	5 > ( 3, 6 )
  //	6 > ( 12 )
  //	7 > ( 3, 4, 5 )
  //	8 > ( 3 )
  //	9 > ( 5, 10 )
  //	10 > ( )
  //	11 > ( 9 )
  //	12 > ( 6 )
  cout << "\n--------------------------------------------------\n*"
          " Para el segundo mapa:\n";
  map < int , list<int> > M2;
  M2[1].push_back(7);
  M2[2].push_back(1);
  M2[3].push_back(2);
  M2[3].push_back(9);
  M2[4];
  M2[5].push_back(3);
  M2[5].push_back(6);
  M2[6];
  M2[6].push_back(12);
  M2[7].push_back(4);
  M2[8].push_back(3);
  M2[9].push_back(5);
  M2[9].push_back(10);
  M2[10];
  M2[11].push_back(9);
  M2[12].push_back(6);
	
  int m = 11;
  int n = 4;
	
  if (exists_path1(M2,m,n) and exists_path2(M2,m,n) and exists_path4(M2,m,n))
    cout<<"SI: Existe al menos una forma de llegar de "<<m<< " a "<<n<<endl;
  else
    cout<<"NO: No hay forma de llegar de "<<m<<" a "<<n<<endl;
	
	
  return 0;
}
