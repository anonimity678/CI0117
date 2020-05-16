//LUIS EDUARDO ROJAS CARRILLO B86875
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include "semaforo.h"


double SumarUno( long * suma ) {
   int i;

   for ( i = 0; i < 1000; i++ ) {
      (* suma)++;			// Suma uno
//      usleep( 1 );
   }
   exit( 0 );
}


double SumarUnoControlado( int semid, long * suma ) {
   int i;
   Semaforo s;
   s.Wait(semid);
   for ( i = 0; i < 1000; i++ ) {
      (* suma)++;			// Suma uno
//      usleep( 1 );
   }

   s.Signal(semid);	// Libera el semaforo para que otros procedan

   exit( 0 );

}


/*
 * Serial test
 */
int SerialTest( int procesos, long * total ) {
   int i, proceso;

   for ( proceso = 0; proceso < procesos; proceso++ ) {

      for ( i = 0; i < 1000; i++ ) {
         (* total)++;			// Suma uno
//         usleep( 1 );
      }

   }

}


/*
 * Fork test with race condition
 */
int ForkTestRaceCondition( int procesos, long * total ) {
   int proceso, pid;

   for ( proceso = 0; proceso < procesos; proceso++ ) {
      pid = fork();
      if ( ! pid ) {
         SumarUno( total );
      }
   }

   for ( proceso = 0; proceso < procesos; proceso++ ) {
      int status;
      pid_t pid = wait( &status );
   }

}


/*
 * Fork test with NO race condition
 * Los procesos acceden a la variable en orden
 */
int ForkTestNORaceCondition( int procesos, int semid, long * total ) {
   int proceso, pid;

   for ( proceso = 0; proceso < procesos; proceso++ ) {
      pid = fork();
      if ( ! pid ) {
         SumarUnoControlado( semid, total );
      }
   }

   for ( proceso = 0; proceso < procesos; proceso++ ) {
      int status;
      pid_t pid = wait( &status );
   }

}

int main( int argc, char ** argv ) {
   long procesos;
   long * total;
   int proceso, pid, shmid, semid;
   clock_t start, finish;
   double used;
   Semaforo s(1);

// Create shared memory segment
   shmid = shmget( 0xA12345, sizeof( long ), IPC_CREAT | 0600 );
   total = (long *) shmat( shmid, NULL, 0 );

   procesos = 100;
   if ( argc > 1 ) {
      procesos = atol( argv[ 1 ] );
   }

   start = clock();
   * total = 0;
   SerialTest( procesos, total );
   finish = clock();
   used = ((double) (finish - start)) / CLOCKS_PER_SEC;
   printf( "Serial version:      Valor acumulado es \033[91m %ld \033[0m con %ld procesos in %f seconds\n", * total, procesos, used );

   start = clock();
   * total = 0;
   ForkTestRaceCondition( procesos, total );
   finish = clock();
   used = ((double) (finish - start)) / CLOCKS_PER_SEC;
   printf( "Fork, Race Cond.:    Valor acumulado es \033[91m %ld \033[0m con %ld procesos in %f seconds\n", * total, procesos, used );

   start = clock();
   * total = 0;
   ForkTestNORaceCondition( procesos, s.getID(), total );
   finish = clock();
   used = ((double) (finish - start)) / CLOCKS_PER_SEC;
   printf( "Fork, No Race Cond.: Valor acumulado es \033[91m %ld \033[0m con %ld procesos in %f seconds\n", * total, procesos, used );


// Destroy shared memory segment
   shmdt( total );
   shmctl( shmid, IPC_RMID, 0 );

}
