/*
LUIS EDUARDO ROJAS CARRILLO B86875.
MAIN.CPP.
SE ENCARGA DE ORGANIZAR Y EJECUTAR LOS HILOS.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>

#include "Ascensor.h"
#include "Persona.h"
#include "Buzon.h"

void * hiloAscensor( void * param ) {//RUTINA DEL HILO ASCENSOR.
	sleep(2);
	long iden;
   	iden = (long) param;
	Ascensor *ascensor;
   	ascensor = new Ascensor(iden);
	ascensor->recibirLlamados();
	sleep(1);
   	ascensor->display();

		do{
			ascensor->recibirLlamados();
			sleep(0.4);
			ascensor->recibaPersonas();
			sleep(0.4);
			ascensor->moverAscensor();
			sleep(0.4);
			if((ascensor->apagarAscensor())==true){
				sleep(3);
				ascensor->recibirLlamados();
			}
		}while((ascensor->apagarAscensor())!=true);

	ascensor->apagar();
	printf("Ascensor se apaga, no hay más personas \n");
   	return NULL;
}


void Ascensores( long cantidad ) {//CREA LOS HILOS DE TIPO ASCENSOR.
   long hilo;
   pthread_t * ascensor;

   ascensor = (pthread_t *) calloc( cantidad, sizeof( pthread_t ) );

   for ( hilo = 0; hilo < cantidad; hilo++ ) {
      pthread_create( & ascensor[ hilo ], NULL, hiloAscensor, (void *) hilo );
   }

   for ( hilo = 0; hilo < cantidad; hilo++ ) {
      pthread_join( ascensor[ hilo ], NULL );
   }

   free( ascensor );

}


void * hiloPersona( void * param ) {//RUTINA PARA LOS HILOS DE TIPO PERSONA.
	long iden;
	iden = (long) param;   
	Persona *persona;
	persona = new Persona(iden);
	persona->llamarAscensor();

	persona->esperarAscensor(iden);
	persona->displayUno();

	persona->esperarAscensor(iden);
	persona->displayDos();

	persona->esperarAscensor(iden);
	persona->displayTres();
   	return NULL;
}


void Personas( long cantidad ) {//CREA LOS HILOS DE TIPO PERSONA.
   long hilo;
   pthread_t * personas;

   personas = (pthread_t *) calloc( cantidad, sizeof( pthread_t ) );

   for ( hilo = 0; hilo < cantidad; hilo++ ) {
      pthread_create( & personas[ hilo ], NULL, hiloPersona, (void *) hilo );
   }

   for ( hilo = 0; hilo < cantidad; hilo++ ) {
      pthread_join( personas[ hilo ], NULL );
   }

   free( personas );

}


int main( int argc, char ** argv ) {//HILO PRINCIPAL, SE ENCARGA DE EJECUTAR TODOS LOS HILOS NECESARIOS.
   long hilos;
   clock_t start, finish;
   double used;

   srand( time( NULL ) );	
   int pid=fork();
	if(!pid){//GENERA LOS HILOS PERSONA.
		printf("PRIMERA OLEADA \n");
		Personas( 50 );
		sleep( 2 );
		printf("SEGUNDA OLEADA \n");
   		Personas( 40 );
    	}else{//GENERA LOS HILOS ASCENSOR.
		Ascensores( 1 );
	}

sleep(1);
}
