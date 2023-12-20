/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Escribir una funcion #bool nullsum(list<int> &L, list<int> &L2);# 
   que dada una lista #L#, determina si hay
   un rango de iteradores no vacio #[p,q)# tal que su suma
   sea 0. Adicionalmente: escribir una funcion #void#
   #nullsum_filt(map<int,list<int>> &M, map<int,list<int>>#
   #&M2);# que extrae de todos los pares de asignacion
   #(k,L)# para los cuales #L# tiene un rango de suma zero,
   e inserta en #M2# la asignacion #(k,L')# donde #L'# es el
   rango de #L# que tiene suma 0.
   [Tomado en el parcial de laboratorio de 2012-10-06].  
   keywords: lista, correspondencia

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------

#include <cstdio>
#include <cassert>
#include <cmath>

#include <list>
#include <map>
#include <string>
#include <iostream>
#include <sstream>

#include "./util.h"

using namespace std;

typedef map< int,list<int> > map_t;

bool nullsum(list<int> &L, list<int> &L2) {
  list<int>::iterator p = L.begin(),q;
  // Hay que limpiar la lista de salida
  L2.clear();
  while (p!=L.end()) {
    // Inicializa acumulador
    int sum=0;
    // q va a recorrer desde p hasta encontrar un rango
    // de suma nula. 
    q = p;
    while (q!=L.end()) {
      sum += *q++;
      // Notar que esta garantizado que el rango no es vacio
      // ya que al menos suma el elemento de la posicion `p'
      if (sum==0) break;
    }
    // Chequea si encontro un rango de suma nula. En ese caso
    // lo pone en L2 (acordarse que esta vacia) y retorna el valor. 
    if (sum==0) {
      L2.insert(L2.end(),p,q);
      return true;
    }
    p++;
  }
  return false;
}

void nullsum_filt(map_t &M1, map_t &M2) {
  // p recorre los pares de asignacion de M
  map_t::iterator p = M1.begin();
  while (p!=M1.end()) {
    list<int> L1;
    // L1 es auxiliar y almacena el rango de suma nula (si
    // existe). Si contiene un rango lo inserta en M2. 
    int ok = nullsum(p->second,L1);
    if (ok) M2[p->first] = L1;
    p++;
  }
}

class Evaluar
{
	void (*nullsum_filt) (map<int, list<int> >&, map<int, list<int> >&);

	list<int> string2list(string s)
	{
		list<int> L;
		istringstream is(s);
		int n;
		while (is >> n)
			L.push_back(n);
		return L;
	}

	bool zerosum(list<int> &L)
	{
		if (L.empty()) return false;
		int s = 0;
		for (list<int>::iterator it = L.begin(); it != L.end(); ++ it)
			s += *it;
		
		return s == 0;
	}

	bool sub(list<int> &L, list<int> &L2)
	{
		if (L.empty() || L2.empty())
			return false;
		list<int>::iterator it = L.begin();
		list<int>::iterator it2 = L2.begin();

		while (it != L.end())
		{
			list<int>::iterator it_aux = it;
			while (it != L.end() && *it != *it2)
				++ it;

			if (it == L.end())
				return false;

			while (it2 != L2.end() && *it == *it2)
			{
				++ it;
				++ it2;
			}

			if (it2 == L2.end())
				return true;

			it2 = L2.begin();
			it = it_aux;
			++ it;
		}

		return false;
	}

	void prl(list<int> &L)
	{

		cout << "[";
		list<int>::iterator il = L.begin();
		while (il != L.end())
		{
			cout << *il;
			++ il;
			if (il != L.end())
				cout << ", ";
		}
		cout << "]";
	}

	bool ev1()
	{
		map<int, list<int> > M, Mr;
		M[0] = string2list("-7 -4 7 5 3 5 -4 2 -1 -9");
		M[1] = string2list("-8 -3 0 9 -7 -4 -10 -4 2 6");
		M[2] = string2list("1 -2 -3 -1 -8 0 -8 -7 -3 5");
		M[3] = string2list("-1 -8 -8 8 -1 -3 3 6 1 -8");
		M[4] = string2list("1 3 5 -2");
		M[5] = string2list("3 -4 1 -10 6 3 -8 0 6 -9");
		M[6] = string2list("-5 -5 -6 -3 6 -5 -4 -1 3 7");
		M[7] = string2list("-6 5 -8 -5 4 -3 4 -6 -7 0");
		M[8] = string2list("1 5 4");
		M[9] = string2list("2 -10 6 -2 9 2 -4 -4 4 9");

		//for (int i = 0 ; i < 10 ; i ++)
		//	cout << "vb[" << i << "] = " << (nullsum(M[i])?"true":"false") << ";" << endl;
		
		vector<bool> vb(10);
		vb[0] = false;
		vb[1] = true;
		vb[2] = true;
		vb[3] = true;
		vb[4] = false;
		vb[5] = true;
		vb[6] = true;
		vb[7] = true;
		vb[8] = false;
		vb[9] = true;    

		nullsum_filt(M, Mr);

		map<int, list<int> >::iterator it = Mr.begin();
		while (it != Mr.end())
		{
			if (!zerosum(it->second))
			{
				cout << "Incorrecto" << endl;
				cout << "La lista enviada como:" << endl;
				cout << "M[" << it->first << "] ="; prl(it->second); cout << endl;
				cout << "No suma cero" << endl;
				return false;
			}

			if (!sub(M[it->first], it->second))
			{
				cout << "Incorrecto" << endl;
				cout << "La lista enviada como:" << endl;
				cout << "M[" << it->first << "] ="; prl(it->second); cout << endl;
				cout << "No es sublista contigua de:" << endl;
				cout << "M[" << it->first << "] ="; prl(M[it->first]); cout << endl;
				return false;
			}

			++ it;
		}

		for (int i = 0 ; i < vb.size() ; i ++)
		{
			if (!vb[i]) continue;
			if (Mr.find(i) == Mr.end())
			{
				cout << "Incorrecto" << endl;
				cout << "La lista:" << endl;
				cout << "M[" << i << "] = "; prl(M[i]); cout << endl;
				cout << "Cumple con nullsum, sin embargo no fue considerada" << endl;

				return false;
			}
		}

		cout << "Correcto" << endl;
		return true;
	}
	bool ev2()
	{
		map<int, list<int> > M, Mr;
		M[0] = string2list("-1 8 -3 8 -1 6 8 -1");
		M[1] = string2list("-7 8 1 -3 -8 5 ");
		M[2] = string2list("4 1 -3 -8 -8 -5 -8");
		M[3] = string2list("2 6 7 4 -4");
		M[4] = string2list("8 -6 5 -4 -8  3 5 6 4");
		M[5] = string2list("5 -7 -1 -5");
		M[6] = string2list("-6 4 7 7 -2 -2 8 -7 -3");
		M[7] = string2list("2 1 6 5 -2 -3 -2 -7 1 -8 -2 5");
		M[8] = string2list("1 -2 -2 -4 5 -5 -1 -8 -3 -6 7 7 5 1 -8 1 5 -5 -1 4 8");
		M[9] = string2list("7 -7 -6 -4 -1 -2 3 -8 -2 -2 4 7"); 

		//for (int i = 0 ; i < 10 ; i ++)
		//	cout << "vb[" << i << "] = " << (nullsum(M[i])?"true":"false") << ";" << endl;
		
		vector<bool> vb(10);
		vb[0] = false;
		vb[1] = false;
		vb[2] = false;
		vb[3] = true;
		vb[4] = true;
		vb[5] = false;
		vb[6] = false;
		vb[7] = true;
		vb[8] = true;
		vb[9] = true; 

		nullsum_filt(M, Mr);

		map<int, list<int> >::iterator it = Mr.begin();
		while (it != Mr.end())
		{
			if (!zerosum(it->second))
			{
				cout << "Incorrecto" << endl;
				cout << "La lista enviada como:" << endl;
				cout << "M[" << it->first << "] ="; prl(it->second); cout << endl;
				cout << "No suma cero" << endl;
				return false;
			}

			if (!sub(M[it->first], it->second))
			{
				cout << "Incorrecto" << endl;
				cout << "La lista enviada como:" << endl;
				cout << "M[" << it->first << "] ="; prl(it->second); cout << endl;
				cout << "No es sublista contigua de:" << endl;
				cout << "M[" << it->first << "] ="; prl(M[it->first]); cout << endl;
				return false;
			}

			++ it;
		}

		for (int i = 0 ; i < vb.size() ; i ++)
		{
			if (!vb[i]) continue;
			if (Mr.find(i) == Mr.end())
			{
				cout << "Incorrecto" << endl;
				cout << "La lista:" << endl;
				cout << "M[" << i << "] = "; prl(M[i]); cout << endl;
				cout << "Cumple con nullsum, sin embargo no fue considerada" << endl;

				return false;
			}
		}

		cout << "Correcto" << endl;
		return true;
	}

	public:
	Evaluar(void (*F) (map<int, list<int> >&, map<int, list<int> >&))
	{
		nullsum_filt = F;
		if (ev1() && ev2())
		{
			cout << "Aprobado" << endl;
		}
	}
};


int main() {
  map_t M1, M2;

  // Probamos con 10 listas aleatorias
  printf("----------------\nChequeando nullsum():\n");
  int N=10;
  for (int k=0; k<N; k++) {
    list<int> L,L1;
    int fac=1;
    for (int j=0; j<N; j++) L.push_back((rand()%(2*fac*N)-fac*N));
    printf("================\nM[%d] -> L: ",k);
    printl(L);
    int ok = nullsum(L,L1);
    if (ok) {
      printf("tiene sublista: ");
      printl(L1);
    } else {
      printf("NO tiene sublista!\n");
    }
    M1[k] = L1;
  }

  printf("----------------\nChequeando nullsum_filt():\n");
  nullsum_filt(M1,M2);

  printf("--- Filtered M2:\n");
  map_t::iterator p = M2.begin();
  while (p!=M2.end()) {
    printf("M2[%d] = ",p->first);
    printl(p->second);
    p++;
  }
  
  printf("================================\n");
  printf("CORRE EL EVALUADOR DEL EXAMEN: \n");
  Evaluar ev(nullsum_filt);
  return 0;
}
