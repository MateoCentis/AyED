#include <iostream>
#include <list>
using namespace std;

/*12) Compacta. Escribir una funci´on void compacta(list<int> &L,list<int> &S) que 
toma un elemento entero n de S y, si es positivo, saca n elementos de L 
y los reemplaza por su suma.
Esto ocurre con todos los elementos de S hasta que se acaben,
 o bien se acaben los elementos de L.
*/

void compacta2(list<int> &L, list<int> &S)
{
    list<int>::iterator itL = L.begin();
    list<int>::iterator itS = S.begin();
    list<int>::iterator itt = itL;
    int suma, cont;
    while (itS != S.end() and itL != L.end())
    {
        if (*itS <= 0)
            continue;

        suma = 0;
        cont = 0;
        while (itL != L.end() and cont < *itS)
        {
            suma += *itL;
            itL = L.erase(itL);
            ++cont;
        }
        itL = L.insert(itL, suma);
        ++itL;
        ++itS;
    }
}
/*  L = {1, 2, 3, 4, 5, 6}; Tendría que quedar [1, 5, 4, 5, 6]
    S = {1, 2, 1};*/
void compacta(list<int> &L, list<int> &S)
{
    list<int>::iterator its = S.begin();
    list<int>::iterator itl = L.begin();
    list<int>::iterator itt = itl;
    int suma, contador;

    while (its != S.end() or itl != L.end())
    {
        if (*its > 0)
        {
            contador = 0;
            suma = 0;
            while (itl != L.end() and contador < *its)
            {
                suma += *its;
                ++contador;
                ++itl;
            }
            *itt = suma;
            ++itt;
            itt = L.erase(itt, itl);
            itl = itt;
        }
        ++its;
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
    list<int> L = {1, 2, 3, 4, 5, 6}; //Tendría que quedar [1, 5, 3]
    list<int> S = {1, 2};
    cout << "VIVA PERÓN" << endl;
    compacta2(L, S);
    PrintL(L);
}