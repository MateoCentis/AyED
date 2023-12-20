#include <iostream>
#include <list>
using namespace std;

void PrintL(list<char> &L)
{
    cout << "[ ";
    for (auto it = L.begin(); it != L.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << "]";
}
/*Pal´ındromo. Escribir un predicado bool is_palindromo(char* S), que reciba como par´ametro
una cadena de texto S y determine si ´esta es un pal´ındromo, ignorando los espacios entre palabras.
Un pal´ındromo es una secuencia de caracteres que se lee igual hacia adelante que hacia atr´as, por
ejemplo: alli si maria avisa y asi va a ir a mi silla. Recordar que un string puede indexarse como
un vector. Con el fin de utilizar la estructura <list>, primero deben pasarse los elementos del
string a una lista y solo utilizar ´esta en el algoritmo.*/
bool is_palindromo2(string s)
{
    list<char> L;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] != ' ')
        {
            L.push_back(s[i]);
        }
    }
    list<char>::iterator itB = L.begin();
    list<char>::iterator itE = L.end();
    --itE;
    while (itB != itE)
    {
        if (*itB != *itE) //Condicion de corte, que no sean iguales.
        {
            return false;
        }
        ++itB;
        --itE;
    }
    return true;
}

bool is_palindromo(string s)
{
    list<char> L;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] != ' ')
        {
            L.push_back(s[i]);
        }
    }

    list<char>::iterator itB = L.begin();
    list<char>::iterator itE = L.end();
    list<char>::iterator itt = L.end();
    --itE;

    while (itB != itE or itt != itB)
    {
        --itt;
        if (*itB != *itE)
        {
            return false;
        }
        ++itB;
        --itE;
    }

    return true;
}

bool is_palindromo(char *S)
{
}

//alli si maria avisa y asi va a ir a mi silla
int main()
{
    string s = "alli si maria avisa y asi va a ir a mi silla";
    if (is_palindromo2(s) == true)
    {
        cout << "Es palindromo" << endl;
    }
    else
    {
        cout << "No es palindromo" << endl;
    }
}