/*
LUIS EDUARDO ROJAS CARRILLO B86876.
BUZON.H.
BUZON DE MENSAJES.
DEFINICIÓN DE MÉTODOS Y ATRIBUTOS.
*/
#ifndef BUZON_H
#define BUZON_H

#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

#define KEY2 0xA67891//KEY DEL RECURSO.

using namespace std;

class datos{//ESTRUCTURA PARA GUARDAR DATOS DE LOS MENSAJES, SE UTILIZA EN ASCENSOR.CPP Y PERSONA.CPP.
public:
	int pisoA=0;
	int pisoD=0;
	int id=-1;
};

class Buzon {
   public:
	Buzon();//CONSTRUCTOR BUZON.     
       ~Buzon();//DESTRUCTOR BUZON.

      	void enviar(int a, int b, int c);//ENVIA MENSAJE CON LOS DATOS NECESARIOS.   
      	datos recibir();//RECIBE EL MENSAJE Y RETORNA DATOS NECESARIOS.

	void destruir();//DESTRUYE LA COLA DE MENSAJES.

	struct{//ESTRUCTURA NECESARIA PARA ENVIAR MENSAJE.
	long tipo;
	int valores[3];
	}mensaje;

   private:
      int id;//IDENTIDICADOR DE BUZON.
      int longitud;//LONGITUD DEL MENSAJE.	
};
#endif // BUZON_H
