/*
PIPORSERIES IMPLEMENTADO CON BUZONES.
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Buzon.h"

double calcularSumaParcialPi( double Pi[], int proceso, long inicial, long terminos ) {
   double casiPi = 0;
   double alterna = 4;
   long divisor = 0;
   long termino;
   Buzon b;

   for ( termino = inicial; termino < terminos; termino++ ) {
      divisor = termino + termino + 1;		
      casiPi += alterna/divisor;		
      alterna *= -1;				
   }
   b.EnviarDouble(casiPi);
   Pi[ proceso ] = casiPi;			
   exit( 0 );
}


int main( int argc, char ** argv ) {
   long terminos, inicio, fin;
   int proceso;
   int pid;
   double casiPi[ 10 ] = { 0 };
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
         calcularSumaParcialPi( casiPi, proceso, inicio, fin );
      } else {
         printf("Creating process %d: starting value %ld, finish at %ld\n", pid, inicio, fin );
      }
   }

   for ( proceso = 0; proceso < 10; proceso++ ) {
      int status;
      pid_t pid = wait( &status );
   }

   for ( proceso = 0; proceso < 10; proceso++ ) {
      casiPi[ 0 ] += b.RecibirDouble();
   }

   printf( "Valor calculado de Pi es \033[91m %g \033[0m con %ld terminos\n", casiPi[ 0 ], terminos );
}
