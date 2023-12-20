#include <iostream>
#include <sstream>
#include "tree.h"
using namespace std;
using aed::tree;

/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   Esta version delega la conversion de string a #T# al
   #operator>>(istream,T)...# entonces se hace generico y
   funciona para cualquier tipo de dato al que se le pueda
   hacer un #cin>>d;#

   keywords: arbol orientado

FIN DE DESCRIPCION */

template<typename T>
bool lisp2tree(stringstream &ss, aed::tree<T> &t,
         typename aed::tree<T>::iterator it) {
  char aux;
  streampos pos = ss.tellg();
  while (ss>>aux) {
    if (aux=='(') {
      T data; if (!(ss>>data)) return false;
      it = t.insert(it, data);
      if (!lisp2tree(ss, t, it.lchild())) return false;
      ++ it;
    } else if (aux == ')') {
      return true;
    } else {
      ss.seekg(pos);
      T data; if (!(ss>>data)) return false;
      it = t.insert(it, data);
      ++ it;
    }
    pos = ss.tellg();
  }
  return true;
}

template<typename T>
bool lisp2tree(string s, tree<T> &t) {
  assert(t.empty());
  stringstream ss; ss<<s;
  return lisp2tree(ss,t,t.begin());
}

int main() {
  tree<char> t2; 
  lisp2tree("(A (B C (D (E F G))) (H I (J K L) (M N)))",t2);
  cout << "t2 = "; t2.lisp_print(); cout << endl;
}
