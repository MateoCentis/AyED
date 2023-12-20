#include <iostream>
#include <list>
using namespace std;

/*10) Forman un c´ırculo y se escoge un n´umero n al azar. Igualmente se escoge el
nombre de un soldado. Comenzando por el soldado cuyo nombre se ha seleccionado, comienzan a
contar en la direcci´on del reloj alrededor del c´ırculo. Cuando la cuenta alcanza el valor n, este
soldado es retirado del c´ırculo y la cuenta comienza de nuevo, con el soldado siguiente. El proceso
contin´ua de tal manera que cada vez que se llega al valor de n se retira un soldado. El ´ultimo
soldado que queda es el que debe tomar el caballo y escapar. Entonces, dados un n´umero n y una
lista de nombres, que es el ordenamiento en el sentido de las agujas del reloj de los soldados en el
c´ırculo (comenzando por aqu´el a partir del cual se inicia la cuenta), escribir un procedimiento
list<string> josephus(list<string>& nombres, int n) que retorna una lista con los
nombres de los soldados en el orden que han de ser eliminados y en ´ultimo lugar el nombre del
soldado que escapa.*/

list<string> josephus2(list<string> &nombres, int n)
{
    if (n <= 1)
    {
        return nombres;
    }
    list<string> eliminados;
    list<string>::iterator itB = nombres.begin();
    int cont = 0;
    while (!nombres.empty())
    {
        if (itB == nombres.end())
            itB = nombres.begin();
        if (cont == n)
        {
            eliminados.push_back(*itB);
            itB = nombres.erase(itB);
            cont = 0;
        }
        else
            ++itB;
        cont++;
    }
    return eliminados;
}

list<string> josephus(list<string> &nombres, int n)
{
    if (n <= 1)
        return nombres;
    list<string> nombres_ordenados;
    auto it = nombres.begin();
    int cont = 0;

    while (!nombres.empty())
    {
        ++cont;
        if (it == nombres.end())
            it = nombres.begin();

        if (cont == n)
        {
            nombres_ordenados.push_back(*it);
            it = nombres.erase(it);
            cont = 0;
        }
        else
        {
            ++it;
        }
    }
}

void PrintL(list<string> &L)
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
    list<string> nombres = {"pedro", "Juan", "Javier", "Mateo", "Daniel"};
    list<string> eliminados;
    eliminados = josephus(nombres, 2);
    PrintL(eliminados);
}