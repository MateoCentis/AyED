#include <iostream>
#include <stack>
#include <queue>
using namespace std;

/*1)Varios. Utilizando las operaciones del contenedor stack<> de STL, construir una serie de
procedimientos que realicen cada una de las actividades siguientes en una pila:
a)0 Asignar i al segundo elemento desde la parte superior de la pila, dejando la pila sin sus dos
elementos de la parte superior.
b)0 Asignar i al segundo elemento desde la parte superior de la pila, sin modificarla
c)0 Dado un entero n, asignar i al elemento n-´esimo desde la parte superior de la pila, dejando la
pila sin sus n elementos superiores.
d)0 Asignar i al elemento del fondo de la pila, dejando la pila vac´ıa.
e)0 Asignar i al elemento del fondo de la pila, dejando la pila sin modificar.
*/

void PrintStack(stack<int> P)
{
    while (!P.empty())
    {
        cout << P.top() << endl;
        P.pop();
    }
}
int main()
{
    stack<int> P;
    int i = 10;
    P.push(1);
    P.push(2);
    P.push(3);
    P.push(4);
    P.push(5);
    P.push(6);

    //a)
    /*
    P.pop();   //Elimina el 5
    P.pop();   //Elimina el 4
    P.push(i); //Inserto i
    */
    //b)
    /* int aux = P.top();
    P.pop();
    P.pop();
    P.push(i);
    P.push(aux);
    */
    //c)
    cout << "Pila antes" << endl;
    PrintStack(P);
    int n = 3;
    if (P.size() < n)
    {
        cout << "La pila es muy chiquita" << endl;
    }
    stack<int> P2;
    for (int i = 0; i < n - 1; ++i)
    {
        P2.push(P.top());
        P.pop();
    }
    P.pop();
    P.push(i);
    while (!P2.empty())
    {
        P.push(P2.top());
        P2.pop();
    }
    cout << "Pila despues" << endl;
    PrintStack(P);
}