#include <iostream>
#include <list>
using namespace std;

//Invierte, escriba una funci�n void inver(list<int>&L) que invierte el orden de la lista L
//Debe ser inplace y debe ser O(n). Restricci�n: no utilizar el m�todo size();

void invert(list<int> &L)
{
	list<int>::iterator it2 = L.end();	//Fin
	list<int>::iterator it = L.begin(); //Principio
	while ((it != it2) and (it != --it2))
	{						  //Para no pasarse
		iter_swap(it++, it2); //Cambio los iteradores
	}
}

void PrintList(const list<int> &L)
{
	list<int>::const_iterator itB = L.cbegin();
	cout << "[ ";
	while (itB != L.end())
	{
		cout << *itB << " ";
		++itB;
	}
	cout << "]" << endl;
}

int main()
{
	list<int> L = {1, 2, 3, 4, 5, 6, 7};
	invert(L);
	PrintList(L);
}
