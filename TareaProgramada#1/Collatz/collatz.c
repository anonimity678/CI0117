/*
LUIS EDUARDO ROJAS CARRILLO B86875.
COLLATZ.C
INCLUYE CLASE COLLATZ Y MAIN.
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include "semaforo.h"
#define KEY2 ((key_t) (8976))//DEFINICION DE LA LLAVE PARA SHM.

struct valores{//STRUCTURA COMPARTIDA A LOS HILOS PARA QUE REALICEN EL CÁLCULO.
	long int valor=0;
	long int veces=0;
};

void collatz(valores* v, long int inicio, long int final){//CLASE COLLATZ PARA LOS HILOS, CADA HILO REALIZA UN RANGO DE CÁLCULOS.
	long int valorFinal=0;
	long int contadorFinal=0;

	for(long int i=inicio; i<=final; i++){
	long int val=i;
	long int cont=0;	
		while(val>=2){//CÁLCULO DE CADA VALOR.
			if(val%2==0){
				val=val/2;
			}else{
				val=val*3+1;
			}
		cont++;
		}

		if(cont>contadorFinal){
			contadorFinal=cont;
			valorFinal=i;
		}
			
	}
	
	if(contadorFinal>v->veces){//SI EL CONTADOR ES MAYOR, SE GUARDA EN LA VARIABLE COMPARTIDA.
	v->veces=contadorFinal;
	v->valor=valorFinal;
	}

exit(0);
}




int main( int argc, char ** argv ){//MAIN
	clock_t start, finish;
	double used;
	long int terminos;
	int id;
	int pid;
	struct valores v;

	Semaforo s(0);//SEMÁFORO PARA EVITAR CONDICIÓN DE CARRERA.
	id = shmget(KEY2, sizeof(v), 0666 | IPC_CREAT );
	struct valores * area = (struct valores *) shmat( id, NULL, 0 );

	terminos = 1000;//CANTIDAD DE TERMINOS A CALCULAR.
	long int inicio=0;
	long int final=0;
	long int div=0;
	int hilos=10;

	div=terminos/hilos;
	final=div;

   	if (argc>1) {
      		terminos=atol(argv[1]);
   	}
	start = clock();
	for ( int i= 0; i < hilos ; i++ ) {//GENERA HILOS MEDIANTE FORK().

     		 pid = fork();
      			if ( ! pid ) {
        			s.Wait();
         			collatz(area,inicio,final);//LLAMADO A COLLATZ CON SU RANGO.
	 			s.Signal();

				_exit(0);
     			 } else {
				s.Signal();
      			}
		inicio=final;
		final=final+div;
   	}

	for (int i = 0; i < 10; i++){//ESPERA LOS HILOS.
      	int status;
      	pid_t pid = wait(&status);
   	}
	finish = clock();
	used = ((double) (finish - start)) / CLOCKS_PER_SEC;

	printf("Con %i terminos el numero con más pasos es el %i con %i pasos \n", terminos, area->valor, area->veces);
	printf("Con %i hilos el tiempo es de %f secs \n", hilos, used);
   	shmdt( area );//DESTRUYE MEMORIA COMPARTIDA
  	shmctl( id, IPC_RMID, NULL );
}
