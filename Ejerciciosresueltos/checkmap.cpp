// $Id$

/* 
   COMIENZO DE DESCRIPCION 
   __USE_WIKI__

   Dado un #map<int, list<bool> > M#, verificar que para
   todas las claves pares, la lista correspondiente tenga todos
   sus elementos en true o bien que sea vacia. Si el map no
   tiene elementos, la salida debe ser true.
   [Tomado en primer parcial de lab 2011-09-17].
   keywords: correspondencia, lista
    
   FIN DE DESCRIPCION 
*/

// Ejemplos:

// \medskip
// \begin{Verbatim}
// M = {2 -> [true, true], 4 ->[]} -> returns true
// M = {1 -> [false]} -> returns true
// M = {2 -> [true, true, true], 3 -> [true, false]} -> returns true
// M = {} -> returns true
// M = {6 -> [false, true], 4 -> [true, true]} -> returns false
// \end{Verbatim}
// \medskip
 
// La funcion debe tener la siguiente signatura 
// !+bool mostrar_map(map<int, list<bool> >&);+

// -----------------------------------------------------------------
#include <string>
#include <map>
#include <list>
#include <sstream>
#include <iostream>
using namespace std;

typedef map<int,list<bool> > map_t;
bool checkmap(map_t &M) {
  map_t::iterator p = M.begin();
  while (p!=M.end()) {
    if (p->first%2==0) {
      list<bool> &L = p->second;
      list<bool>::iterator q = L.begin();
      while (q!=L.end()) 
        if (!*q++) return false;
    }
    p++;
  }
  return true;
}

class Evaluar
{
	bool (*F) (map<int, list<bool> >&);
public:
	Evaluar(bool (*f) (map<int, list<bool> >&)) : F(f) { evaluar(); };
	void s2m(string s, map<int, list<bool> > &M)
	{
		M.clear();
		istringstream is(s);

		int k, n, v;
		while (is >> k >> n)
		{
			list<bool> L;

			for (int i = 0 ; i < n ; i ++)
			{
				is >> v;
				L.push_back(v);
			}
			M[k] = L;
		}
	}

	void printmap(map<int, list<bool> >& M) {
		cout << "M = {";
		map<int, list<bool> >::iterator p = M.begin();
		while (p!=M.end()) {
			cout << p->first << "->[";
			list<bool> &L = p->second;
			list<bool>::iterator q = L.begin();
			while (q!=L.end()) {
				cout << (*q ? "true" : "false");
				q++;
				if (q!=L.end()) cout << ", ";
			}
			cout << "]";
			p++;
			if (p!=M.end()) cout << ", ";
		}
		cout << "}" << endl;
	}

	void verificar(string s, bool r)
	{
		map<int, list<bool> > M;
		s2m(s, M);
		bool ret = F(M);
		if (ret == r)
			cout << "BIEN" << endl;
		else
		{
			cout << "==============" << endl;
			cout << "MAL" << endl;
			cout << "Para el map:" << endl;
			printmap(M);
			cout << "Tu salida fue: " << endl;
			cout << (ret ? "true" : "false") << endl;
			cout << "y deberia ser: " << endl;
			cout << (r ? "true" : "false") << endl;
			cout << "==============" << endl;
		}

	}

	void evaluar()
	{
		/*
		   M = {2 -> [true, true], 4 ->[]}
		   returns true

		   M = {1 -> [false]}
		   returns true

		   M = {2 -> [true, true, true], 3 -> [true, false]}
		   returns true

		   M = {}
		   returns true

		   M = {6 -> [false, true], 4 -> [true, true]}
		   returns false
		 */
		verificar("2 2 1 1 4 0", true);
		verificar("1 1 0", true);
		verificar("2 3 1 1 1 3 2 1 0", true);
		verificar("", true);
		verificar("6 2 0 1 4 2 1 1", false);
		verificar("0 1 1 1 1 1 2 1 1 3 1 1 4 1 1 5 1 1 6 1 1", true);
		verificar("0 1 1 1 3 1 0 0 2 3 0 1 0 3 3 0 1 1 4 4 1 1 0 1 5 0 6 1 0 7 4 0 0 0 0", false);
		verificar("0 1 1 1 4 1 0 1 1 2 2 1 0 3 3 1 1 0 4 4 0 0 1 1 5 0 6 4 1 0 0 1 7 4 0 0 0 0 8 0", false);
		verificar("0 4 1 1 0 1 1 1 1", false);
		verificar("0 3 1 0 0 1 4 1 1 0 1 2 3 0 1 0 3 2 1 1 4 1 0", false);
		verificar("0 1 1 1 4 1 1 1 0 2 4 0 1 1 1 3 2 0 1 4 4 0 1 1 0 5 3 0 1 0 6 2 0 0 7 1 1", false);
		verificar("0 0 1 4 0 0 0 1 2 4 1 1 0 1 3 1 0", false);
		verificar("0 2 0 0 1 3 0 1 0", false);
		verificar("0 0 1 4 0 1 0 0 2 3 1 1 1 3 3 1 0 0 4 2 0 0 5 1 0 6 4 1 1 0 0", false);
		verificar("0 1 1 1 0 2 4 0 1 0 0 3 4 1 0 0 0 4 4 1 0 1 1 5 2 1 0 6 2 1 0 7 4 1 1 1 1 8 0", false);
		verificar("0 4 1 1 1 1 1 3 1 1 1 2 2 0 1 3 4 0 1 0 1 4 1 1 5 1 0 6 1 0", false);
		verificar("0 0 1 0 2 0 3 0 4 0 5 0 6 0 7 0 8 0 9 0 10 0 11 0 12 0 13 0 14 0 15 0", true);
	}
};

int main() {
  Evaluar obj(checkmap);
  return 0;
}

