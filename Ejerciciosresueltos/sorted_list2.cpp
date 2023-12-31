// $Id$

/* 
   COMIENZO DE DESCRIPCION 

   Escriba procedimientos para insertar, suprimir y buscar    
   un elemento en una lista ordenada {\tt L}. 
   Versi\'on {\bf \'unicamente} con {\tt funciones gen\'ericas} 
   (comparar con {\tt sorted_list1.cpp} y {\tt sorted_list3.cpp}). 
   keywords: lista

   FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
#include <iostream>
#include "./util.h"
using namespace std ;

// -----------------------------------------------------------------
// inserta un item "x" en la lista ordenada "L"
template <typename T> 
void inserta_ord (list <T> & L, const T & x) {
  typename list<T>::iterator p ;
  p = L.begin ();
  while (p != L.end () && *p < x) p++;     // avanza si *p < x
  L.insert (p, x);
} // end void

// -----------------------------------------------------------------
// suprime un item "x" en la lista ordenada "L"
template <typename T>
void suprime_ord (list <T> & L, const T & x) { 
  typename list<T>::iterator p ;
  p = L.begin ();  
  while (p != L.end () && *p < x) p++;        // avanza si *p < x
  if (p != L.end () && *p == x) L.erase (p);  // suprime "p"
} // end void

// -----------------------------------------------------------------
// busca posicion "p" de un item "x" en la lista ordenada "L"
template <typename T> 
typename list<T>::iterator busca_ord (list <T> & L, const T & x) {
  typename list<T>::iterator p ; 
  p = L.begin ();
  while (p != L.end() && *p < x) p++;  // avanza si *p < x
  if ( p != L.end () && *p == x ) 
    return p ;                         // la posicion de "x" en "L"
  else
    return L.end ();                   // retorna fin de lista
} // end iterator

//--------------------------------------------------------------------
int main() {

  int v1[] = {4,2,6,3,7,1,-1}  ;  int const n1 = 6 ;
  int v2[] = {9,0,3,2,7,8,4,-1};  int const n2 = 7 ;
  list<int> S;
  list<int> :: iterator p;
  int x ;

  cout << endl;
  cout << "Tareas simples sobre una lista ordenada S " << endl;

  for (int i=0; i<n1; i++) inserta_ord (S,v1[i]);
  for (int i=0; i<n2; i++) inserta_ord (S,v2[i]);
  cout << "Lista ordenada actual S: "; printl (S); cout << endl;

  for (int i=0; i<n1; i++) inserta_ord (S,v1[i]);
  cout << "Lista ordenada actual S: "; printl (S); cout << endl;

  for (int i=0; i<n1; i++) suprime_ord (S,v1[i]);
  cout << "Lista ordenada actual S: "; printl (S); cout << endl;

  x = 6 ; cout << endl << "Busca elemento x = " << x << endl;
  p = busca_ord (S,x);
  if ( p != S.end () )
    cout << "se lo encontro en la lista " << endl;
  else
    cout << "no se lo encontro en la lista " << endl;

  x = 5 ; cout << endl << "Busca elemento x = " << x << endl;
  p = busca_ord (S,x);
  if (p != S.end () )
    cout << "se lo encontro en la lista " << endl;
  else
    cout << "no se lo encontro en la lista " << endl;

  inserta_ord (S,-758);
  inserta_ord (S, 364);
  suprime_ord (S,   0);
  inserta_ord (S,   5);
  suprime_ord (S,   3);
  cout << "Lista ordenada actual S: "; printl (S);

  S.clear ();
  cout << "Lista ordenada actual S: "; printl (S);

  cout << endl;
  return 0;
}
//--------------------------------------------------------------------
