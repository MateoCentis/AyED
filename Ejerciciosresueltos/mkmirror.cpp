/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
  Escribir una funcion #void make_mirror(tree<int> &T);# que
  convierte in-place al arbol #T# en su espejo. 
   [Tomado en segundo parcial 2011-10-27].
   keywords: arbol orientado

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------

// Por ejemplo
//   si !+T=(1 (5 3 2 1) (10 9 7))+ entonces despues de hacer
//   !+make_mirror(T)+ debe quedar !+T=(1 (10 7 9) (5 1 2 3))+. 
//   \textbf{Ayuda:} Debe ir invirtiendo la lista de hijos para
//   cada nodo !+n+ y aplicar la funcion recursivamente sobre los
//   hijos. Para invertir los hijos se puede usar alguna de las
//   siguientes opciones:
//   % FIXME:= poner ejemplo
//   \begin{itemize}
//     \compactlist 
//   \item Usar un arbol auxiliar !+Taux+, insertar un elemento
//     cualquiera (p.ej. 0) en la raiz y hacer \emph{splice} para ir
//     moviendo cada uno de de los hijos de !+n+ a !+Taux+. Luego volver
//     a mover (con \emph{splice}) todos los hijos de !+Taux+ en !+n+,
//     pero de forma que queden invertidos.
//   \item Usar una lista de arboles !+list<tree<int>> L+. Mover los
//     hijos de !+n+ sucesivamente en nuevos arboles en la lista. Para
//     insertar un nuevo arbol en la lista simplemente hacemos
//     !+L.push_back(tree<int>())+. 
//   \item No usar ningun contenedor auxiliar, ir recorriendo los hijos
//     de !+n+ y moverlos en !+n.lchild()+. En este caso tener cuidado
//     con los iteradores.
//   \end{itemize}
//   %
//   \textbf{Curiosidad:} Notar que
//   !+ordprev(make_mirror(T))=reverse(ordpost(T))+ y 
//   !+ordpost(make_mirror(T))=reverse(ordprev(T))+.
//    keywords: arbol orientado

#include <cstdarg>
#include <cstdio>

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "./util.h"
#include "./tree.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
typedef tree<int>::iterator node_t;
void make_mirror(tree<int> &T,node_t n) {
  node_t c = n.lchild();
  if (c==T.end()) return;
  // Crea un arbol temporario `aux'. Mueve todos los hijos
  // de `n' com hijos de la raiz de `aux'. Como `aux'
  // inicialmente est'a vacio inserta algo en la raiz de
  // `aux'. Para eso inserta un nodo con cualquier etiqueta
  // (en este caso 0). En este proceso los hijos de `n' quedan
  // en orden invertido en `aux'
  tree<int> aux;
  node_t m = aux.insert(aux.begin(),0);
  node_t d = m.lchild();
  while (c!=T.end()) {
    d = aux.splice(d,c);
    c = n.lchild();
  }

  // Ahora trate todos los hijos de la raiz de `aux' a
  // `n' en el mismo orden (de manera que queden invertidos). 
  c = n.lchild();
  d = m.lchild();
  while (d!=aux.end()) {
    c = T.splice(c,d); c++;
    d = m.lchild();
  }

  // Aplica recursivamente `make_mirror()' a los hijos de `n'
  c = n.lchild();
  while (c!=T.end()) make_mirror(T,c++);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void make_mirror(tree<int> &T) {
  make_mirror(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Esta implementacion es completamente similar pero
// en vez de usar un arbol auxiliar usa una lista de
// arboles. 
typedef tree<int>::iterator node_t;
void make_mirror2(tree<int> &T,node_t n) {
  
  node_t c = n.lchild();
  if (c==T.end()) return;

  typedef list< tree<int> > list_t;
  list_t L;
  while (c!=T.end()) {
    L.push_back(tree<int>());
    tree<int> &tmp = L.back();
    tmp.splice(tmp.begin(),c);
    c = n.lchild();
  }

  list_t::iterator q = L.begin();
  c = n.lchild();
  while (q!=L.end()) {
    c = T.splice(c,q->begin());
    q = L.erase(q);
  }

  c = n.lchild();
  while (c!=T.end()) make_mirror2(T,c++);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void make_mirror2(tree<int> &T) {
  make_mirror2(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {

  for (int j=0; j<10; j++) {
    printf("---- TRY TREE #%d ---------\n" ,j);
    tree<int> T, T2;
    make_random_tree(T,10,2);
    T2 = T;
    print_tree(T);
    make_mirror(T);
    printf("Con make_mirror():\n");
    print_tree(T);
    
    make_mirror2(T2);
    printf("Con make_mirror2():\n");
    print_tree(T2);
  }
  return 0;
}
