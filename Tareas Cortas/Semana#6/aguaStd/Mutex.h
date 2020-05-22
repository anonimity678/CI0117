/*
LUIS EDUARDO ROJAS CARRILLO B86875.
MUTEX.H.
MÉTODOS Y DEFINICIONES.
*/
#ifndef _MUTEX_H
#define _MUTEX_H

#include <pthread.h>

class Mutex {
public:
   Mutex();
   ~Mutex();
   int Lock();
   int TryLock();
   int Unlock();

private:
   pthread_mutex_t * mutex;

};

#endif
