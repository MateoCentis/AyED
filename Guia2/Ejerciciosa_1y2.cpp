#include <iostream>
#include <list>
using namespace std;

//La lista no tiene sobrecarga del operador corchetes, por lo tanto debemos usar iterator
void basic_sort(list<int>&L)
{
	list<int>L2;
	while(!L.empty())
	{
		list<int>::iterator itB = L.begin();
		list<int>::iterator it = itB;
		int min = *itB;
		++itB;
		while (itB != L.end())
		{
			if(min > *itB)
			{
				min = *itB;
				it = itB;
			}
			++itB;
		}
		L.erase(it);
		L2.push_back(min);
	}
	L.swap(L2);
}

void PrintList(const list<int>&L)
{
	list<int>::const_iterator itB = L.cbegin();
	cout << "[ ";
	while(itB != L.end())
	{
		cout << *itB << " ";
		++itB;
	}
	cout << "]" << endl;
}

void selection_sort(list<int>&L)
{
	int aux;
	for(list<int>::iterator it = L.begin() ; it != L.end() ; ++it)
	{
		list<int>::iterator it2 = it;
		++it2;
		for(; it2 != L.end() ; ++it2)
		{
			if(*it > *it2)
			{
				aux = *it2;
				*it2 = *it;
				*it = aux;
			}
		}
	}
}

list<int>concatenar(list<int>&L1, list<int>&L2)
{
	list<int>L = L1; 
	L.insert(L.end(),L2.begin(),L2.end());
	return L;
}
int main()
{
	list<int>L = {1, 2 , 4, 3, -9, 7, 9};
	list<int>L2 = {17, 20, 22};
	//basic_sort(L);
	selection_sort(L);
	list<int>NuevaL = concatenar(L,L2);
	PrintList(NuevaL);
}
