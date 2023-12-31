/* COMIENZO DE DESCRIPCION

__USE_WIKI__

Funciones auxiliares para generar arboles aleatorios de cualquier tipo de dato.

FIN DE DESCRIPCION */

// Los algoritmos de generaci�n estan tomados de make_random_tree y make_random_btree 
// de utils_tree.cpp y utils_btree.cpp, y modificados para utilizar un
// generador de datos aleatorios para los nodos. Hay una sobrecarga de esta
// funci�n que recibe como argumento otra funcion o un functor y usa eso
// para generar datos aleatorios. Si no se le pasa nada, esta versi�n tiene
// generadores por defecto para char, int, std::string, float y double.
//
// Llamar a make_random_tree y make_random_btree pasandole primero el tree o 
// btree (del cuyo tipo la funci�n deduce qu� datos generar), luego uno (para
// btree) o dos (para tree) enteros que controlan la forma y el tamanio del 
// arbol (alto y ancho), y opcionalmente una funci�n o functor para generar
// las etiquetas.
//
// Hay adem�s una funci�n replace_duplicates que recibe un tree, y 
// opcionalmente una funci�n generadora, y reempleza las etiquedas duplicadas
// con nuevas etiquetas aleatorios (verificando que estas nuevas no existan
// previamente).


#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <stack>
#include <set>
#include "tree.hpp"
#include "btree.hpp"

namespace aed {
	
	// default random T generator for make_random_tree<T>
	template<typename T> class random_keygen;
	
	// string random generator
	template<>
	class random_keygen<std::string> {
		int sils;
	public:
		random_keygen(int max_silabas=4) : sils(max_silabas) {}
		std::string operator()() const {
			const char vocales[] = "aeiou";
			const char consonantes[] = "bcdfghjklmnpqrstvwxy";
			std::string s(2*(1+rand()%(sils-1)),' ');
			for(size_t i=0;i<s.size();i++) {
				if (i%2) s[i] = vocales[rand()%(sizeof(vocales)-1)];
				else     s[i] = consonantes[rand()%(sizeof(consonantes)-1)];
			}
			return s;
		}
	};
	
	// int random generator
	template<>
	class random_keygen<int> {
		int m;
	public:
		random_keygen(int max=100) : m(max+1) {}
		int operator()() const { return rand()%m; }
	};
	
	// char random generator
	template<>
	class random_keygen<char> {
	public:
		char operator()() const { return 'A'+rand()%('Z'-'A'+1); }
	};
	
	// double random generator
	template<>
	class random_keygen<double> {
		int m,d,a;
	public:
		random_keygen(int max=100, int decs=3) : m(max), d(pow(10,decs)) {}
		double operator()() const { return (rand()%m)+double(rand()%(d+1))/d; }
	};
	
	// float random generator
	template<>
	class random_keygen<float> {
		int m,d,a;
	public:
		random_keygen(int max=100, int decs=3) : m(max), d(pow(10,decs)) {}
		float operator()() const { return (rand()%m)+float(rand()%(d+1))/d; }
	};
	
	
	
	template<typename T, typename Generator>
	void make_random_tree(aed::tree<T> &t,typename aed::tree<T>::iterator n,
						  int m,int s, const Generator &g) {
		if (!m) return;
		// Toma los m nodos y los divide en `ss' siblings donde s es aleatorio
		// en [1,s]
		int ss = rand()%s+1;
		// Inserta un nodo en la raiz
		n = t.insert(n,g());
		m--; // toma en cuenta que ya inserto 1
		// Reparte los nodos que quedan aleatoriamente en los ss hijos
		std::vector<int> v(ss,0);
		for (int j=0; j<m; j++) v[rand()%ss]++;
		// A esta altura tenemos un vector v[] con s enteros
		// cuya suma es `m'.  Algunos pueden ser nulos, pero no importa
		// porque en ese caso la llamada recursiva no va a hacer nada. 
		for (unsigned int j=0; j<v.size(); j++) 
			make_random_tree(t,n.lchild(),v[j],s,g);
	}
	
	
	template<typename T, typename Generator>
	void make_random_tree(aed::tree<T> &t, int m, int s, const Generator &g) {
		assert(t.begin()==t.end());
		make_random_tree(t,t.begin(),m,s,g);
	}
	
	template<typename T>
	void make_random_tree(tree<T> &t, int m=50, int s=5) {
		assert(t.begin()==t.end());
		make_random_tree(t,m,s,random_keygen<T>());
	}
	
	template<typename T, typename Generator>
	aed::tree<T> make_random_tree(int m, int s, const Generator &g) {
		aed::tree<T> t;
		make_random_tree(t,t.begin(),m,s,g);
		return t;
	}
	
	template<typename T>
	aed::tree<T> make_random_tree(int m=50, int s=5) {
		aed::tree<T> t;
		make_random_tree(t,m,s,random_keygen<T>());
		return t;
	}
	
	template<typename T, typename Generator>
	void replace_duplicates(tree<T> &t, const Generator &g) {
		std::stack<typename aed::tree<T>::iterator> q;
		std::set<T> labels;
		q.push(t.begin());
		while (!q.empty()) {
			typename aed::tree<T>::iterator it = q.top(); 
			q.pop();
			while (labels.count(*it)) { *it=g(); }
			labels.insert(*it);
			it = it.lchild();
			while (it!=t.end()) q.push(it++);
		}
	}
	
	template<typename T>
	void replace_duplicates(tree<T> &t) {
		replace_duplicates(t,random_keygen<T>());
	}
	
	
	template<typename T, typename Generator>
	void make_random_btree(aed::btree<T> &t, typename aed::btree<T>::iterator n,
						   int level,double siblings, const Generator &g) {
		typename aed::btree<T>::iterator c;
		n=t.insert(n,g());
		double nivel=double(level);
		double lambda = 1.0/(siblings/nivel+1.0);
		for (int j=0;j<2;j++) {
			if  (j==0) c=n.left();
			else c=n.right();
			double drand = double(rand())/double(RAND_MAX);
			if (drand>lambda)
				make_random_btree(t,c,level+1,siblings,g);
		}
	}
	
	// -----------------------------------------------------------------
	template<typename T, typename Generator>
	void make_random_btree(aed::btree<T> &t,double siblings, const Generator &randg) {
		t.clear();
		make_random_btree(t,t.begin(),0,siblings,randg);
	} 
	
	template<typename T>
	void make_random_btree(aed::btree<T> &t, double siblings=5) {
		assert(t.begin()==t.end());
		make_random_btree(t,siblings,random_keygen<T>());
	}
	
	template<typename T>
	btree<T> make_random_btree(double siblings=5) {
		btree<T> t;
		make_random_btree(t,siblings);
		return t;
	}
	
	template<typename T, typename Generator>
	btree<T> make_random_btree(double siblings, const Generator &randg) {
		btree<T> t;
		make_random_btree(t,siblings,randg);
		return t;
	}
}

