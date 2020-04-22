/*
  Calcula el numero PI utilizando una serie "infinita"
  Debe recibir la cantidad de iteraciones como parametro
  pi = (-1)^i x 4/(2xi + 1)
 * Semana 02, deben crear dos programas:
 *    Agregar Semaforos y un segmento de memoria compartida para lograr la solución correcta
 *    Agregar Paso de mensajes para lograr la solución correcta
 *
 */


/*SALIDA DEL PROGRAMA...

Creating process 5409: starting value 0, finish at 100000
Creating process 5410: starting value 100000, finish at 200000
Creating process 5411: starting value 200000, finish at 300000
Creating process 5412: starting value 300000, finish at 400000
Creating process 5413: starting value 400000, finish at 500000
Creating process 5414: starting value 500000, finish at 600000
Creating process 5415: starting value 600000, finish at 700000
Creating process 5416: starting value 700000, finish at 800000
Creating process 5417: starting value 800000, finish at 900000
Creating process 5418: starting value 900000, finish at 1000000
Valor calculado de Pi es  3.14159  con 1000000 terminos
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semaforo.h"

#define KEY2 ((key_t) (8976))//DEFINICION DE LA LLAVE PARA SHM.

/*
Realiza la acumulacion de terminos desde una posicion inicial hasta un termino final
*/

double calcularSumaParcialPi( double Pi[], int proceso, long inicial, long terminos ) {
   double casiPi = 0;
   double alterna = 4;
   long divisor = 0;
   long termino;

   for ( termino = inicial; termino < terminos; termino++ ) {
      divisor = termino + termino + 1;		// 2 x termino + 1
      casiPi += alterna/divisor;		// 4 / (2xi + 1)
      alterna *= -1;				// Pasa de 4 a -4 y viceversa, para realizar la aproximacion de los terminos
   }
   Pi[ proceso ] = casiPi;			// Guarda el resultado en el vector y finaliza
   exit( 0 );
}


int main( int argc, char ** argv ) {

   long terminos, inicio, fin;
   int proceso;
   int pid;
   double casiPi[ 10 ] = { 0 };

   Semaforo s(0);
   int id = shmget(KEY2, sizeof(casiPi), 0666 | IPC_CREAT );
   double * area = (double *) shmat( id, NULL, 0 );

   terminos = 1000000;
   if ( argc > 1 ) {
      terminos = atol( argv[ 1 ] );
   }

   for ( proceso = 0; proceso < 10; proceso++ ) {
      inicio = proceso * terminos/10;
      fin = (proceso + 1) * terminos/10;
      pid = fork();
      if ( ! pid ) {
         s.Wait();

         calcularSumaParcialPi(area, proceso, inicio, fin);

	 s.Signal();

	_exit(0);
      } else {
      printf("Creating process %d: starting value %ld, finish at %ld\n", pid, inicio, fin );
	s.Signal();
      }
   }

   for ( proceso = 0; proceso < 10; proceso++ ) {
      int status;
      pid_t pid = wait( &status );
   }

   for ( proceso = 1; proceso < 10; proceso++ ) {
      area[ 0 ] += area[ proceso ];
   }

   printf( "Valor calculado de Pi es \033[91m %g \033[0m con %ld terminos\n", area[ 0 ], terminos );

   shmdt( area );
   shmctl( id, IPC_RMID, NULL );
}
