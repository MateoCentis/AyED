// $Id$
/* COMIENZO DE DESCRIPCION

 Listado de \'arboles binarios en diferentes ordenes.
 Keywords: arbol binario

   FIN DE DESCRIPCION */
// -----------------------------------------------------------------
#include <iostream>
#include "./btree.h"
#include "./util.h"
#include "./util_btree.h"
using namespace aed;
using namespace std;

// -------------------------------------------------------------------
void  orden_prev ( btree <int> & t, btree <int> :: iterator n) {
  if ( n == t.end () ) return ;
  cout << (* n) << " " ; 
  orden_prev (t, n.left  () ) ;
  orden_prev (t, n.right () ) ;
} // end void

// -------------------------------------------------------------------
void  orden_post ( btree <int> & t, btree <int> :: iterator n) {
  if ( n == t.end () ) return ;
  orden_post (t, n.left  () ) ;
  orden_post (t, n.right () ) ;
  cout << (* n) << " " ; 
} // end void

// -------------------------------------------------------------------
void  orden_sime ( btree <int> & t, btree <int> :: iterator n) {
  if ( n == t.end () ) return ;
  orden_sime (t, n.left  () ) ;
  cout << (* n) << " " ; 
  orden_sime (t, n.right () ) ;
} // end void

// -----------------------------------------------------------------
int main () {
  btree <int> t;

  cout << endl ;
  cout << "listados en un arbol binario "  << endl ; 

  for (int j = 0 ; j < 1 ; j++) {
    t.clear ();
    cout << endl ;
    cout << "arbol binario:"  << endl ; 
    make_random_btree (t, 9, 1.3);
    t.lisp_print (); cout << endl ;
    cout << endl ;
    cout << "orden previo"    << endl ; 
    orden_prev ( t, t.begin () ) ; 
    cout << endl ; cout << endl ;
    cout << "orden posterior" << endl ; 
    orden_post ( t, t.begin () ) ; 
    cout << endl ; cout << endl ;
    cout << "orden simetrico" << endl ; 
    orden_sime ( t, t.begin () ) ; 
    cout << endl ;
  } // end for
  cout << endl ;
  return 0 ;
} // end main
// -----------------------------------------------------------------
