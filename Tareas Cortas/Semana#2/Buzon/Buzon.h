/*
BUZON.H
BUZON DE MENSAJES.
DEFINICIÓN DE MÉTODOS Y ATRIBUTOS.
*/

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

#define KEY 0xA12345//KEY DEL RECURSO.

using namespace std;

class Buzon {
   public:
      Buzon();
      ~Buzon();

      void EnviarDouble(double x);   
      double RecibirDouble();

      void EnviarString(string x);
      string RecibirString();
	
        struct{//ESTRUCTURA PARA DOUBLE.
	long tipo;
	double cadena;
	}mensajeDouble;

	struct{//ESTRUCTURA PARA STRING.
	long tipo;
	string cadena;
	}mensajeString;

   private:
      int id;//IDENTIDICADOR DE BUZON.
      int longitud;//LONGITUD DEL MENSAJE.
};
