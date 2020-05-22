/*
LUIS EDUARDO ROJAS CARRILLO B86875.
AGUA.C CON SEMÁFOROS.
*/
#include "semaforo.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

#define N       10


void H( int );
void O( int );

Semaforo sO;	
Semaforo sH;	

struct Compartidos {
        int nO;
        int nH;
};

typedef struct Compartidos Compartir;
Compartir * pComp;

int id = 0;



int main(){
        int i = 0;
	int pid;

        id = shmget( 0xABCDEF, sizeof( Compartir ), 0600 | IPC_CREAT );
        if ( -1 == id ) {
           perror( "main" );
           exit( 0 );
        }

        pComp = ( Compartir * ) shmat( id, NULL, 0 );


        srand( time( NULL ) );

        while( i++ < N ) {
		int r = rand();
        	pid=fork();
			if ( ! pid ) {       
             			if ( r % 2 ) {
                		printf( "Se creo un atomo de oxigeno [%d]\n", i );
                		O( i );
             			}else{
                		printf( "Se creo un atomo de hidrogeno [%d]\n", i );
                		H( i );
             			}
          		}

        }

        i = 0;
        while ( i++ < N ) {
           int status;
      	   pid_t pid = wait( &status );
        }


        printf( "Destruyendo los recursos de memoria compartida\n");
        shmdt( pComp );
        shmctl( id, IPC_RMID, NULL );
	sO.borrar();	
	sH.borrar();
}      



void O( int i ){
	if ( pComp->nH > 1 ) {
           printf( "Molecula de agua creada por un O [%d] \n", i );
	   sH.Wait();
	   sH.Wait();
	   pComp->nH -= 2;
	} else {
	   pComp->nO++;
	   sO.Signal();
	}
exit( 0 );
}

void H( int i ){
	if ( ( pComp->nH > 0) && (pComp->nO > 0) ) {
           printf( "Molecula de agua creada por un H [%d] \n", i );
	   sH.Wait();
	   sO.Wait();
	   pComp->nH --;
	   pComp->nO --;
	} else {
	   pComp->nH++;
	   sH.Signal();
	}
exit( 0 );
}

