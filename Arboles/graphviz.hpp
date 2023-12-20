/* 	COMIENZO DE DESCRIPCION

	__USE_WIKI__

	Funciones para visualizar (mediante graphviz) arboles (aed::tree<T> y 
	aed::btree<T>) y grafos (std::map<T,Cont<T>>, donde Cont puede ser list, 
	vector, set o similar).

	FIN DE DESCRIPCION */


// Las cuatro funciones a usar son: 
//  - tree2dot(...) para aed::tree<T>
//  - btree2dot(...) para aed::btree<T>
//  - graph2dot(...) para std::map<T,AlgunContenedor<T>> que representen grafos no dirigidos
//  - digraph2dot(...) para std::map<T,AlgunContenedor<T>> que representen grafos dirigidos
// Todas las funciones tienen los mismos argumentos:
//  1) El arbol o mapa (único obligatorio)
//  2) Un string con un nombre de archivo que va a usar para armar los temporales. Cada 
//     visualización genera uno o dos temporales con ese nombre más las extensiones 
//     ".dot" y ".png". Por defecto se usan "temp_tree", "temp_btree" y "temp_graph".
//  3) un bool que indica si hay que mostrar el resultado (true) o solo generarlo
//     (false solo guarda el .dot y/o .png en disco). Por defecto se muestra.
//  4) En GNU/Linux, si se tiene instalado xdot no hace falta generar el png, pero
//     se puede forzar que lo genere poniendo este argumento en true (por defecto es false).
//  5) (solo para grafos) El nombre del generador de graphviz que se usa, por defecto "fdp".

// En GNU/Linux requiere graphviz, y xdot (recomendado) o xdg. En Windows requiere solo 
// graphviz, pero graphviz es parte de la instalación básica de ZinjaI, por lo que si
// tiene ZinjaI actualizado (version 20170926 o superior), no debería tener que instalar
// ni configurar nada más. Si la detección automática no funciona, con un 
// #define GRAPHVIZ_PATH "ruta" antes de incluir este puede modificar el path.

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#ifdef __WIN32__
#	include <windows.h> // para shell_execute
#endif
#include "tree.hpp"
#include "btree.hpp"

namespace aed {
	
	/*** rutinas de utileria comunes para todos los graficadores ***/
	
	inline std::string graphviz_keygen() {
		static std::string key = "aaaaa";
		int i=4; 
		while (key[i]=='d') 
			key[i--]='a';
		++(key[i]);
		return key;
	}
	
#ifdef __WIN32__
	std::string get_graphviz_path() {
#	ifdef GRAPHVIZ_PATH
#		return GRAPHVIZ_PATH;
#else
		const char *zpath = getenv("ZINJAI_DIR");
		if (!zpath) return "C:\\Program Files (x86)\\ZinjaI\\third\\graphviz\\";
		else return std::string(zpath)+"third\\graphviz\\";
#	endif
	}
#endif
	
	inline void graphviz_show(std::string fname, bool show, bool force_png, std::string filter="dot") {
#ifndef __WIN32__
		if ( !force_png && system("xdot --help >/dev/null")==0 ) { // ver si esta instalado xdot
			if (show) system((std::string("xdot -f ")+filter+" \""+fname+".dot\" 2>/dev/null &").c_str());
		} else { // si no esta xdot, pasar a png
			if (!force_png) std::cerr << "WARNING: se recomienda instalar \"xdot\"" << std::endl;
			if ( system((filter+" \""+fname+".dot\" -Tpng -o \""+fname+".png\"").c_str()) == 0 ) {
				if (show) system((std::string("xdg-open \"")+fname+".png\" &").c_str()); // abrir el png
			} else { 
				std::cerr << "ERROR: se requiere instalar \"graphviz\"." << std::endl;
			}
		}
#else 
		std::string exe_path = get_graphviz_path(); exe_path+=filter+".exe";
		std::string cmd_line = std::string("\"")+exe_path+"\" \""+fname+".dot\" -Tpng -o \""+fname+".png\"";
		ShellExecute(NULL,"open", exe_path.c_str(),cmd_line.c_str(),NULL,SW_HIDE);
		fname+=".png";
		if (show) ShellExecute(NULL,"open",fname.c_str(),NULL,NULL,SW_NORMAL);
#endif
	}
	
	inline bool graphviz_pre(std::ofstream &fout, std::string fname) {
		fout.open((fname+".dot").c_str(),std::ios::trunc);
		if (!fout.is_open()) { 
			std::cerr << "ERROR: no se pudo abrir el archivo \"" << fname <<".dot\". ";
			return false;
		}
		fout << "digraph h {" << std::endl;
		return true;
	}
	
	template<typename Contenedor>
	void graphviz_print_all(std::ofstream &fout, Contenedor &v) {
		for( typename Contenedor::iterator it=v.begin(); it!=v.end(); ++it )
			fout << *it << std::endl;
	}
	
	inline void graphviz_post(std::ofstream &fout, std::string fname, bool show, bool force_png, std::string filter="dot") {
		fout << "}" << std::endl;
		fout.close();
		graphviz_show(fname,show,force_png,filter);
	}
	
	/*** grafos (std::map<T,AlgunContenedor<T>>) ***/
	
	// func auxiliar
	template<typename T, typename ContainerT>
	void aux_graph2dot(std::map<T,ContainerT> &m, bool directed, std::string fname, bool show, bool force_png, std::string filter) {
		std::ofstream fout;
		if (!graphviz_pre(fout,fname)) return;
		std::map<T,std::string> keys;
		std::list<std::string> relations;
		typename std::map<T,ContainerT>::iterator it = m.begin();
		while (it!=m.end()) {
			std::string k = keys[it->first];
			if (k=="") k = keys[it->first] = graphviz_keygen();
			typename ContainerT::iterator it2 = it->second.begin();
			while (it2!=it->second.end()) {
				std::string k2 = keys[*it2];
				if (k2=="") k2 = keys[*it2] = graphviz_keygen();
				std::list<std::string>::iterator itr = directed
					?relations.end()
					:find(relations.begin(),relations.end(),k2+"->"+k+"[arrowhead=none]");
				if (itr==relations.end())
					relations.push_back(k+"->"+k2+(directed?"":"[arrowhead=none]"));
				++it2;
			}
			++it;
		}
		for( typename std::map<T,std::string>::iterator it=keys.begin(); it!=keys.end(); ++it )
			fout << it->second << "[label=\"" << it->first << "\"]" << std::endl;
		graphviz_print_all(fout,relations);
		graphviz_post(fout,fname,show,force_png,filter);
	}
	
	// wrappers y sobecargas por comodidad
	template<typename T, typename ContainerT>
	void graph2dot(std::map<T,ContainerT> &m, std::string fname = "temp_graph", bool show=true, bool force_png=false, std::string filter="fdp") {
		aux_graph2dot(m,false,fname,show,force_png,filter);
	}
	template<typename T, typename ContainerT>
	void digraph2dot(std::map<T,ContainerT> &m, std::string fname = "temp_graph", bool show=true, bool force_png=false, std::string filter="fdp") {
		aux_graph2dot(m,true,fname,show,force_png,filter);
	}
	template<typename T, typename ContainerT>
	void graph2dot(std::map<T,ContainerT> &m, const char *fname, bool show=true, bool force_png=false, std::string filter="fdp") {
		aux_graph2dot(m,false,std::string(fname),show,force_png,filter);
	}
	template<typename T, typename ContainerT>
	void digraph2dot(std::map<T,ContainerT> &m, const char *fname, bool show=true, bool force_png=false, std::string filter="fdp") {
		aux_graph2dot(m,true,std::string(fname),show,force_png,filter);
	}
	template<typename T, typename ContainerT>
	void graph2dot(std::map<T,ContainerT> &m, bool show, bool force_png=false, std::string filter="fdp") {
		aux_graph2dot(m,false,"temp_graph",show,force_png,filter);
	}
	template<typename T, typename ContainerT>
	void digraph2dot(std::map<T,ContainerT> &m, bool show, bool force_png=false, std::string filter="fdp") {
		aux_graph2dot(m,true,"temp_graph",show,force_png,filter);
	}
	
	
	/*** Arboles Ordenados Orientados (aed::tree<T>) ***/
	
	// func auxiliar
	template<typename T>
	void tree2dot(std::ostream &fout, std::vector<std::string> &relations, 
				  std::string father_key, aed::tree<T> &t, typename aed::tree<T>::iterator it) 
	{
		fout << father_key << "[label=\"" << *it << "\"]" << std::endl;
		it = it.lchild();
		std::string child_key = father_key;
		while (it!=t.end()) {
			std::string child_key = graphviz_keygen(); // get next key
			relations.push_back(father_key+"->"+child_key);
			tree2dot(fout,relations,child_key,t,it);
			it = it.right();
		}
	}
	
	// wrapper
	template<typename T>
	void tree2dot(aed::tree<T> &t, std::string fname = "temp_tree", bool show=true, bool force_png=false) {
		std::ofstream fout;
		if (!graphviz_pre(fout,fname)) return;
		std::vector<std::string> relations;
		if (t.begin()!=t.end())
			tree2dot(fout,relations,graphviz_keygen(),t,t.begin());
		graphviz_print_all(fout,relations);
		graphviz_post(fout,fname,show,force_png,"dot");
	}
	
	// sobrecargas solo por comodidad	
	template<typename T>
	void tree2dot(aed::tree<T> &t, const char *fname, bool show=true, bool force_png=false) {
		tree2dot(t,std::string(fname),show,force_png);
	}
	template<typename T>
	void tree2dot(aed::tree<T> &t, bool show, bool force_png=false) {
		tree2dot(t,"temp_tree",show,force_png);
	}
	
	/*** Arboles Binarios (aed::btree<T>) ***/
	
	// func auxiliar
	template<typename T>
	void btree2dot(std::ostream &fout, std::vector<std::string> &relations, 
				   std::string father_key, aed::btree<T> &t, typename aed::btree<T>::iterator it) 
	{
		fout << father_key << "[label=\"" << *it << "\"]" << std::endl;
		typename btree<T>::iterator itc[2]; itc[0] = it.left(); itc[1] = it.right();
		std::string key[2]; key[0] = graphviz_keygen(); key[1] = graphviz_keygen();
		for(int i=0;i<2;i++) { 
			if (itc[i]!=t.end()) {
				relations.push_back(father_key+"->"+key[i]);
				btree2dot(fout,relations,key[i],t,itc[i]);
			} else if (itc[(i+1)%2]!=t.end()) {
				fout << key[i] << "[label=\" \",color=\"#FFFFFF\"]" << std::endl;
				relations.push_back(father_key+"->"+key[i]+"[color=\"#999999\"]");
			}
		}
	}
	
	// wrapper
	template<typename T>
	void btree2dot(aed::btree<T> &t, std::string fname = "temp_btree", bool show=true, bool force_png=false) {
		std::ofstream fout;
		if (!graphviz_pre(fout,fname)) return;
		std::vector<std::string> relations;
		if (t.begin()!=t.end())
			btree2dot(fout,relations,graphviz_keygen(),t,t.begin());
		graphviz_print_all(fout,relations);
		graphviz_post(fout,fname,show,force_png);
	}
	
	// sobrecargas solo por comodidad	
	template<typename T>
	void btree2dot(aed::btree<T> &t, const char *fname, bool show=true, bool force_png=false) {
		btree2dot(t,std::string(fname),show,force_png);
	}
	template<typename T>
	void btree2dot(aed::btree<T> &t, bool show, bool force_png=false) {
		btree2dot(t,"temp_btree",show,force_png);
	}
	
} // aed


