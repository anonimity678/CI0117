//LUIS EDUARDO ROJAS CARRILLO B86875

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "Buzon.h"
double calcularSumaParcialPi(int proceso, long inicial, long terminos ) {
   Buzon b;
   double casiPi = 0;
   double alterna = 4;
   long divisor = 0;
   struct msgbuf mensaje;

   for ( long termino = inicial; termino < terminos; termino++ ) {
      divisor = termino + termino + 1;		// 2 x termino + 1
      casiPi += alterna/divisor;		// 4 / (2xi + 1)
      alterna *= -1;				// Pasa de 4 a -4 y viceversa, para realizar la aproximacion de los terminos
   }

	b.EnviarDouble(casiPi);


   exit( 0 );

}


int main( int argc, char ** argv ) {
   long terminos, inicio, fin;
   int proceso;
   int pid;
   double resultado;
   Buzon b;

 

   terminos = 1000000;
   if ( argc > 1 ) {
      terminos = atol( argv[ 1 ] );
   }

   for ( proceso = 0; proceso < 10; proceso++ ) {
      inicio = proceso * terminos/10;
      fin = (proceso + 1) * terminos/10;
      pid = fork();
      if ( ! pid ) {
         calcularSumaParcialPi( proceso, inicio, fin );
      } else {
         printf("Creando el proceso %d: termino inicial %ld, termino final %ld\n", pid, inicio, fin );
      }
   }

   resultado = 0.0;
   for ( proceso = 0; proceso < 10; proceso++ ) {
      resultado += b.RecibirDouble();
   }

   printf( "Valor calculado de Pi es \033[91m %15.10g \033[0m con %ld terminos\n", resultado, terminos );

   //msgctl( msgid, IPC_RMID, NULL );

}
