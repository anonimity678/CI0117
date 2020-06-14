/*
LUIS EDUARDO ROJAS CARRILLO - B86875.
PROCESSHTML.H.
DEFINICIÓN DE MÉTODOS.
*/
#ifndef PROCESSHTML_H
#define PROCESSHTML_H
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <pthread.h>
#include "mapa.h"
#include "semaforo.h"
using namespace std;

class processHTML{//CLASE PROCESSHTML.
	public:
		processHTML(int,int);//CONSTRUCTOR.
		~processHTML();//DESTRUCTOR.
		void signal();//SIGNAL.
		void wait();//WAIT.
		void processLine(char*);//PROCESA LA LINEA.
		void muestre();//MUESTRA EL MAPA.
		int getId();//RETORNA EL ID.
		mapa getMap();//RETORNA EL MAPA.
		
	private:	
		mapa map;//MAPA ALMACENA ETIQUETAS.
   		char * token;//TOKENIZER.
   		char *saveptr1;//SAVEPTR PARA HILOS.
		Semaforo *s;//SEMÁFORO.
		int key;//LLAVE DEL SEMÁFORO.
		int id;//ID DEL PROCESO.
};
#endif
