/*
LUIS EDUARDO ROJAS CARRILLO B86875.
AGUASTD.C.
MAIN E IMPLEMENTACIÓN.
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "Mutex.h"

#define N       10

        int nO=0;
        int nH=0;

Mutex * sO;
Mutex * sH;



void* O( void *args ){
long i=(long) args;
	if ( nH > 1 ) {
           printf( "Molecula de agua creada por un O [%ld] \n", i );
	   sH->Lock();
	   nH -= 2;
	   sH->Unlock();
	} else {
	   sO->Lock();
	   nO++;
	   sO->Unlock();
	}
pthread_exit( 0 );
}

void* H( void *args ){
long i=(long) args;
	if ( ( nH > 0) && (nO > 0) ) {
           printf( "Molecula de agua creada por un H [%ld] \n", i );
	   sH->Lock();
	   nH --;
	   sH->Unlock();
	   
           sO->Lock();
	   nO --;
	   sO->Unlock();
	} else {
	   sH->Lock();
	   nH++;
	   sH->Unlock();
	}
pthread_exit( 0 );
}

int main(int argc, char ** argv){
	long hilo;
	pthread_t hilos[ 10 ];

	 sO = new Mutex();
	 sH = new Mutex();


    srand( time( NULL ) );  

   for ( hilo = 0; hilo < N; hilo++ ) {
	int r = rand();
	if ( r % 2 ) {
                printf( "Se creo un atomo de oxigeno [%ld]\n",hilo );
		pthread_create( & hilos[ hilo ], NULL, O,(void *)hilo );
        }else{
                printf( "Se creo un atomo de hidrogeno [%ld]\n",hilo );
 		pthread_create( & hilos[ hilo ], NULL, H, (void *)hilo );
       	}

   }

   for ( hilo = 0; hilo < N; hilo++ ) {
      pthread_join( hilos[ hilo ], NULL );
   }
delete sO;
delete sH;

printf("Fin\n");

}// main
