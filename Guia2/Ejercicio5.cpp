#include <iostream>
#include <list>
using namespace std;

//Junta. Escribir una funcion void junta(list<int> &L, int c) que, dada una lista L, agrupa de
//a c elementos, dejando su suma in place. Por ejemplo, si se le pasa como argumento la lista
//L=(1,3,2,4,5,2,2,3,5,7,4,3,2,2), despues de aplicar el algoritmo junta(L,3) debe quedar
//L=(6,11,10,14,4) (notar que se agrupan los ´ultimos elementos, pese a no completar los tres
//requeridos). El algoritmo debe tener un tiempo de ejecuci´on O(n).
void junta2(list<int> &L, int n)
{
  int suma = 0;
  auto itB = L.begin();
  while (itB != L.end())
  {
    auto it2 = itB;
    for (int i = 0; i < n; ++i)
    {
      suma += *itB;
      ++itB;
      if (itB == L.end())
      {
        suma += *itB;
        break;
      }
    }
    L.erase(it2, itB);
    L.insert(itB, suma);
    suma = 0;
  }
}

void junta(list<int> &L, int n)
{
  list<int>::iterator p = L.begin();
  int suma = 0;
  while (p != L.end())
  {
    // Suma de N elementos y los elimina
    for (int j = 0; j < n; j++)
    {
      suma += *p;
      p = L.erase(p); //L.erase(p) returna la cantidad de elementos borrados
      // Atencion podrian quedar menos de N elementos
      // en la lista. En tal caso llegamos a L.end () y
      // debemos salir del lazo
      if (p == L.end())
        break;
    }
    // Inserta SUMA e incrementa P de manera de quedar apuntando
    // al comienzo de la siguiente subsecuencia.
    p = L.insert(p, suma);
    suma = 0;
    p++;
  }
}

void PrintL(list<int> &L)
{
  cout << "[ ";
  for (auto it = L.begin(); it != L.end(); ++it)
  {
    cout << *it << " ";
  }
  cout << "]";
}

int main()
{
  list<int> L = {1, 3, 2, 4, 5, 2, 2, 3, 5, 7, 4, 3, 2, 2};
  //junta(L, 3);
  junta2(L, 3);
  PrintL(L);
}
