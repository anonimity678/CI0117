/*
LUIS EDUARDO ROJAS CARRILLO B86875.
SEMAFORO.H.
MÉTODOS Y ATRIBUTOS.
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <iostream>

#define KEY 0xA12345//LLAVE DEL RECURSO.

using namespace std;

class Semaforo {
   public:
      Semaforo( int ValorInicial = 0 );//CONSTRUCTOR DE SEMÁFORO.
      ~Semaforo();//DESTRUCTOR DE SEMÁFORO.
      int Signal();//SIGNAL PARA PROCESOS.	
      int Wait();//WAIT PARA PROCESOS.	

        union semun{//STRUCT PARA SEMCTL.
        int val;
	struct semid_ds *buf;
	ushort *array;
        struct seminfo *_buf;
	};

      int id;//IDENTIFICADOR DE SEMÁFORO.
};
