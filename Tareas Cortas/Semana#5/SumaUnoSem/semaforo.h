/*
//LUIS EDUARDO ROJAS CARRILLO B86875
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <iostream>

#define KEY 0xA12345	// Valor de la llave del recurso

using namespace std;

class Semaforo {
   public:
      Semaforo();
      Semaforo(int ValorInicial);
      ~Semaforo();
      int Signal(int n);	// Puede llamarse V
      int Wait(int n);	// Puede llamarse P
      int getID();

        union semun{//STRUCT PARA SEMCTL
        int val;
	struct semid_ds *buf;
	ushort *array;
        struct seminfo *_buf;
	};

      int id;		// Identificador del semaforo
};
