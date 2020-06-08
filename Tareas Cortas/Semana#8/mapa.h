/* 
LUIS EDUARDO ROJAS CARRILLO - B86875.
MAPA.H.
DEFINICIÓN DE MÉTODOS.
ESTRUCTURA DE DATOS PARA GUARDAR LA CANTIDAD DE ETIQUETAS.
*/
#ifndef MAPA_H
#define MAPA_H
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>

using namespace std;

class mapa{//CLASE MAPA.
	public:
		mapa();//CONSTRUCTOR.
		~mapa();//DESTRUCTOR.
		void insertar(string);//INSERTA ELEMENTOS AL MAPA.
		void muestre();//MUESTRA EL MAPA.
	private:
		std::map <string,int> map;//MAPA CON EL NOMBRE DE LA ETIQUETA COMO LLAVE Y CANTIDAD DE VECES COMO DATO.
		std::map <string,int>::iterator it;//ITERADOR DE MAPA.
		int cant;//CUENTA CANTIDAD DE ETIQUETAS.
};
#endif //MAPA.H
