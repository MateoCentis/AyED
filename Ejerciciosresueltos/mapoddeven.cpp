/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dada una lista de enteros #L#, construir el #map<int,list<int>># que mapea
   cada elemento impar de la lista al mayor rango que sigue al elemento
   pero solo constituido de elementos pares, por ejemplo si
   #L=(9,10,6,7,6,8,6,10,2,7)#, entonces
   #M= [9->(10,6),7->(6,8,6,10,2)]#
   [Tomado en el recup de laboratorio de 2012-10-17].  
   keywords: lista, correspondencia

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------

#include <cstdio>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include "./util.h"

using namespace std;


class Evaluar
{
	void (*crear_map) (list<int> &, map<int, list<int> >&);

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

	void prm(map<int, list<int> > &M)
	{
		map<int, list<int> >::iterator it = M.begin();
		while (it != M.end())
		{
			cout << it->first << " -> ";
			prl(it->second);
			cout << endl;
			++ it;
		}
	}

	map<int, list<int> > v2m(vector<int> v)
	{
		int i = 0;
		map<int, list<int> > M;
		while (i < v.size())
		{
			int c = i++;
			int n = v[i++];
			M[v[c]];
			for (int k = 0 ; k < n ; k ++)
			{
				M[v[c]].push_back(v[k+c+2]);
				++ i;
			}

		}
		return M;
	}

	bool ev(vector<int> A, vector<int> B, int caso)
	{
		list<int> L(A.begin(), A.end());
		map<int, list<int> > M = v2m(B);
		map<int, list<int> > R;


		//cout << "Caso #" << caso << endl;
		//cout << "L = "; prl(L); cout << endl;
		//cout << endl << "Mapa resultante:" << endl;
		//cout << "M = {" << endl;
		//prm(M); 
		//cout << "}" << endl << endl;
		//return true;


		crear_map(L, R);
		if (R == M)
		{
			cout << "Caso #" << caso << " correcto" << endl;
			return true;
		}
		else
		{
			cout << "Caso #" << caso << " incorrecto" << endl;
			cout << "Tu respuesta fue:" << endl;
			prm(R); cout << endl;
			cout << "Y la respuesta correcta es:" << endl;
			prm(M); cout << endl;
			return false;
		}
	}

	void verificar()
	{
		{
			int A[] = {9, 10, 6, 7, 6, 8, 6, 10, 2, 7};
			vector<int> Av(A, A+10);
			int B[] = {9, 2, 10, 6, 7, 5, 6, 8, 6, 10, 2};
			vector<int> Bv(B, B+11);
			if (!ev(Av, Bv, 1)) return;
		}

		{
			int A[] = {1, 2, 4, 6, 2, 4};
			vector<int> Av(A, A+6);
			int B[] = {1, 5, 2, 4, 6, 2, 4};
			vector<int> Bv(B, B+7);
			if (!ev(Av, Bv, 2)) return;
		}

		{
			int A[] = {1, 2, 3};
			vector<int> Av(A, A+3);
			int B[] = {1, 1, 2, 3, 0};
			vector<int> Bv(B, B+5);
			if (!ev(Av, Bv, 3)) return;
		}

		{
			int A[] = {1, 2, 2, 2, 1, 2, 2};
			vector<int> Av(A, A+7);
			int B[] = {1, 3, 2, 2, 2};
			vector<int> Bv(B, B+5);
			if (!ev(Av, Bv, 4)) return;
		}

		{
			int A[] = {3, 5, 7, 9};
			vector<int> Av(A, A+4);
			int B[] = {3, 0, 5, 0, 7, 0, 9, 0};
			vector<int> Bv(B, B+8);
			if (!ev(Av, Bv, 5)) return;
		}

		{
			int A[] = {1, 2, 3, 4, 5, 6, 5, 6, 6};
			vector<int> Av(A, A+9);
			int B[] = {1, 1, 2, 3, 1, 4, 5, 2, 6, 6};
			vector<int> Bv(B, B+10);
			if (!ev(Av, Bv, 6)) return;
		}

		{
			int A[] = {1, 2, 1, 2, 2, 1, 2, 2, 2};
			vector<int> Av(A, A+9);
			int B[] = {1, 3, 2, 2, 2};
			vector<int> Bv(B, B+5);
			if (!ev(Av, Bv, 7)) return;
		}
		cout << "Aprobado" << endl;
	}

public:
	Evaluar(void (*F) (list<int>&, map<int, list<int> >&)) : crear_map(F)
	{
		verificar();
	}

};

typedef map<int,list<int> > map_t;

void make_map_odd_even(list<int> &L,map_t &M) {
  list<int>::iterator p = L.begin(), q;
  M.clear();
  while (p!=L.end()) {
    if (*p%2) {
      q=p; q++;
      list<int> tmp;
      while (q!=L.end()) {
        if (*q%2) break;
        tmp.push_back(*q++);
      }
      // Notar que `current' es creado si no existe
      list<int> &current = M[*p];
      if (tmp.size()>current.size()) M[*p] = tmp;
    }
    p++;
  }
}

int main() {
  int N=10;
  list<int> L;
  map_t M;
  for (int j=0; j<N; j++) L.push_back(rand()%N);
  printf("L: ");
  printl(L);
  make_map_odd_even(L,M);
  map_t::iterator r = M.begin();
  while (r!=M.end()) {
    printf("M[%d]: ",r->first);
    printl(r->second);
    r++;
  }

  Evaluar ev(make_map_odd_even);
  
  return 0;
}
