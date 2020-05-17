/*
LUIS EDUARDO ROJAS CARRILLO B86875.
PERSONA.CPP.
IMPREMENTACIÓ DE ASCENSOR.H.
MÉTODOS UTILIZADOS POR LOS HILOS PERSONA.
*/

#include "Persona.h"

Persona::Persona(long n){//CONSTRUCTOR CON DATOS ALEATORIOS DE PERSONA.
	id=n;
	pisoActual=1+rand()%(11-1);
	pisoDestino=1+rand()%(11-1);
			
 		while(pisoDestino==pisoActual){
			pisoDestino=1+rand()%(11-1);
		}

	s= new Semaforo(0);
	b= new Buzon();
}

Persona::~Persona(){//DESTRUCTOR DE PERSONA.

}

void Persona::llamarAscensor(){//ENVÍA MENSAJE AL ASCENSOR CON SU INFORMACIÓN MEDIANTE UN BUZÓN.
	b->enviar(id, pisoActual, pisoDestino);
}

void Persona::esperarAscensor(int n){//ESPERA EL ASCENSOR MEDIANTE UN WAIT CON SU PROPIO ID.
s->Wait(id);
}


void Persona::displayUno(){//MUESTRA LOS DATOS E INSTRUCCIONES A REALIZAR.
printf("Persona con ID: %ld solicita el servicio en el piso %i, con destino al piso %i \n", id, pisoActual, pisoDestino);
}

void Persona::displayDos(){
printf("Persona con ID: %ld ingresa al ascensor \n", id);
}

void Persona::displayTres(){
printf("Persona con ID %ld sale del ascensor \n", id);
}
