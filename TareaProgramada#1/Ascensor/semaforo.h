/*
LUIS EDUARDO ROJAS CARRILLO B86875.
SEMAFORO.H.
DEFINICIÓN DE MÉTODOS Y ATRIBUTOS.
*/

#ifndef SEMAFORO_H
#define SEMAFORO_H
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <iostream>
#include <string>

#define KEY 0xA12345	//KEY DEL RECURSO

using namespace std;

class Semaforo {
   public:
      Semaforo();//CONSTRUCTOR DE SEMÁFORO.
      Semaforo(int ValorInicial);//CONSTRUCTOR DE SEMÁFORO.
      ~Semaforo();//DESTRUCTOR DE SEMÁFORO.
      int Signal(int n);//SIGNAL PARA SEMÁFORO.	
      int Wait(int n);//WAIT PARA SEMÁFORO.	
      int getID();//RETORNA EL ID DEL SEMÁFORO.
      void destruir();//DESTRUYE EL GRUPO DE SEMÁFOROS.

        union semun{//STRUCT PARA SEMCTL
        int val;
	struct semid_ds *buf;
	ushort *array;
        struct seminfo *_buf;
	};

      int id;//IENTIFICADOR DE SEMÁFORO.		
};

#endif // SEMAFORO_H
