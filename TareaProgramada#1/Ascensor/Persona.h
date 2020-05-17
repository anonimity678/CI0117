/*
LUIS EDUARDO ROJAS CARRILLO B86875.
PERSONA.H.
DEFINICIÓN DE MÉTODOS Y ATRIBUTOS.
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "semaforo.h"
#include "Buzon.h"

using namespace std;

class Persona{

public:
        Persona(long);//CONSTRUCTOR DE PERSONA CON ID.
        ~Persona();//DESTRUCTOR DE PERSONA.
	void esperarAscensor(int n);//ESPERA EL ASCENSOR.
	void llamarAscensor();//SOLICITA EL SERVICIO DEL ASCENSOR.
	void displayUno();//MUESTRA DATOS.
	void displayDos();
	void displayTres();

private:
	long id;//ID DE LA PERSONA CREADA.
	int pisoActual;//PISO ACTUAL DE CREACIÓN.
	int pisoDestino;//PISO DE DESTINO:
	Semaforo *s;//SEMAFORO PARA SINCRONIZAR.
	Buzon *b;//BUZON PARA ENVIAR MENSAJE AL ASCENSOR.

};
