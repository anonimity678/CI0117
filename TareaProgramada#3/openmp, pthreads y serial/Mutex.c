/*
LUIS EDUARDO ROJAS CARRILLO - B86875
MUTEX.C.
DESARROLLO DE MÉTODOS.
*/
#include <stdlib.h>
#include <pthread.h>

#include "Mutex.h"

Mutex::Mutex() {
   int resultado;
   pthread_mutexattr_t * atributos;

   this->mutex = (pthread_mutex_t *) calloc( 1, sizeof( pthread_mutex_t ) );
   resultado = pthread_mutex_init( this->mutex, NULL );
   if ( 0 != resultado ) {
      exit( resultado );
   }

}


Mutex::~Mutex() {
   int resultado;

   resultado = pthread_mutex_destroy( this->mutex );
   if ( 0 != resultado ) {
      exit( resultado );
   }

   free( this->mutex );

}

int Mutex::Lock() {
   int resultado;

   resultado = pthread_mutex_lock( this->mutex );
   if ( 0 != resultado ) {
      exit( resultado );
   }

   return resultado;

}

int Mutex::TryLock() {
   int resultado;

   resultado = pthread_mutex_trylock( this->mutex );

   return resultado;

}


int Mutex::Unlock() {
   int resultado;

   resultado = pthread_mutex_unlock( this->mutex );
   if ( 0 != resultado ) {
      exit( resultado );
   }

   return resultado;

}
