/*
LUIS EDUARDO ROJAS CARRILLO - B86875.
FILEREADER.H.
DEFINICIÓN DE MÉTODOS.
*/
#ifndef FILEREADER_H
#define FILEREADER_H
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <thread>
#include <math.h>
#include "mapa.h"
#include "processHTML.h"
#include "semaforo.h"
using namespace std;

class fileReader {//CLASE FILEREADER.

	public:
   		fileReader( const char * fileName, double work,double act, int strate, int llave);//CONSTRUCTOR.
   		~fileReader();//DESTRUCTOR.
   		char* getNext();//RETORNA SIGUIENTE LINEA.
		bool hasNext(int worker);//VERIFICA SI HAY SIGUIENTE LINEA.
		bool bloque(int worker);//MÉTODO PARA ESTÁTICO BLOQUE.
		bool dinamico(int worker);//MÉTODO PARA DINÁMICO.
		bool ciclico(int woker);//MÉTODO PARA ESTÁTICO CICLICO.		
		int getKey();//RETORNA LA LLAVE.
		void empiece();//VERIFICA COMIENZO DE LOS HILOS.
		bool getEmpezar();//RETORNA BOOL EMPEZAR.

	private:
   		double workers;//CANTIDAD DE TRABAJADORES A CREAR.
		double activos;//CANTIDAD DE TRABAJADORES ACTIVOS.
   		int strategy;//ESTRATEGIA A UTILIZAR.			
   		int totalLines;//TOTAL DE LINEAS DEL DOCUMENTO.			
   		FILE * fileId;//FILE ID
		int key;//LLAVE DEL SEMÁFORO.
		Semaforo *s;//SEMÁFORO.	
		size_t size;//TAMAÑO DEL BUFFER.
		char * line;//LINEA.
		int chars;//CUENTA CHAR DE GETLINE.
		bool continuar;
		bool empezar;
		double cantLineas;//CANTIDAD TOTAL DE LINEAS.
		double cantChars;//CANTIDAD TOTAL DE CHARS.

		bool first;
		int f;
		int total;
		int tam;

		int vectInicio[10];//POSICIÓN DE INICIO DE LOS HILOS.
		int vectActual[10];//POSICIÓN ACTUAL DE LOS HILOS.
		int divisor; 
};
#endif
