/*
LUIS EDUARDO ROJAS CARRILLO B86875.
AGUASTD.C.
MAIN E IMPLEMENTACIÓN DE AGUA CON STD.
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
#include <iostream>
#include <thread>
#include <mutex>

#define N       10

        int nO=0;
        int nH=0;

	std::mutex sO;
	std::mutex sH;

void O( int args ){
	if ( nH > 1 ) {
           printf( "Molecula de agua creada por un O [%i] \n", args );
	   sH.lock();
	   nH -= 2;
	   sH.unlock();
	} else {
	   sO.lock();
	   nO++;
	   sO.unlock();
	}
}

void H( int args ){
	if ( ( nH > 0) && (nO > 0) ) {
           printf( "Molecula de agua creada por un H [%i] \n", args);
	   sH.lock();
	   nH --;
	   sH.unlock();
	   
           sO.lock();
	   nO --;
	   sO.unlock();
	} else {
	   sH.lock();
	   nH++;
	   sH.unlock();
	}
}

int main(int argc, char ** argv){
	int hilo;
	std::thread hilos[ 10 ];

	srand( time( NULL ) );  

   	for ( hilo = 0; hilo < N; hilo++ ) {
		int r = rand();
		if ( r % 2 ) {
                	printf( "Se creo un atomo de oxigeno [%i]\n",hilo );
			hilos[hilo]=std::thread(O,hilo);
        	}else{
                	printf( "Se creo un atomo de hidrogeno [%i]\n",hilo );
 			hilos[hilo]=std::thread(H,hilo);
       		}

   	}

   	for ( hilo = 0; hilo < N; hilo++ ) {
      		hilos[hilo].join();
   	}

	printf("Fin\n");
	return 0;
}// main

