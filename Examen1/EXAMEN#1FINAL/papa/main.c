#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
//LUIS EDUARDO ROJAS CARRILLO B86875

#include <time.h>
#include "hilo.h"
#include "semaforo.h"

struct bomba {
        int cont;
	int val;
};

typedef struct bomba bomb;
bomb *b;

void crearHilos(int n){
	hilo *h= new hilo(n);
	h->imprima();
	exit(1);
}



int main( int argc, char ** argv ) {

	int cant=3;
	int id=0;
	Semaforo *s= new Semaforo(cant);

	id = shmget( 0xABCDEF, sizeof( bomb ), 0600 | IPC_CREAT );
        if ( -1 == id ) {
           perror( "main" );
           exit( 0 );
        }

        b = ( bomb * ) shmat( id, NULL, 0 );

 	for(int i=0; i<=3; i++){
		if ( ! fork() ) {
			crearHilos(i);
		}
	}

	shmdt( b );
        shmctl( id, IPC_RMID, NULL );

return 0;
}



