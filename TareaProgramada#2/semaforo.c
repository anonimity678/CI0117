/*
LUIS EDUARDO ROJAS CARRILLO - B86875.
SEMÁFORO.C.
DESARROLLO DE MÉTODOS E IMPLEMENTACIÓN.
*/
#include "semaforo.h"

Semaforo::Semaforo(int vi, int key){//CONSTRUCTOR.
	llave=key;
	int status;
	
	id = semget(llave,1,IPC_CREAT|0600);//CREA SEMÁFORO, LLAVE DE .H,  1 SEMÁFORO, IPC_CREAT CREA.

	if(id==-1){//ERROR DE CONSTRUCCIÓN, RETORNA -1 SEMGET.
	perror("Construccion");
	exit(1);//SALIDA.
	}

	semun u;//CREA SEMUN
        u.val=vi;//INGRESA EN VALOR->VI.

	status=semctl(id,0, SETVAL, u);//IDENTIFICADOR DE SEMAFOROS, SEMAFORO A ACCEDER, OPERACION A REALIZAR, ARG SENUM.

	if(status==-1){//ERROR DE INICIALIZACIÓN.
	perror("Error inicialización");
	exit(2);//SALIDA.
	}
}

Semaforo::~Semaforo(){//DESTRUCTOR.
	//semctl(id,0,IPC_RMID);//ID,0,BORRA GRUPO DE SEMAFOROS.
}

int Semaforo::Wait(){//WAIT.

	sembuf s={0,-1,0};
	
        int status=semop(id,&s,1);
	
	if(status==-1){//ERROR.
	perror("Error wait");
	exit(1);//SALIDA.
	}

	return 0;
}

int Semaforo::Signal(){//SIGNAL.
	sembuf s={0,1,0};
	
        int status=semop(id,&s,1);
	
	if(status==-1){//ERROR
	perror("Error wait");
	exit(1);//SALIDA.
	}

	return 0;
}

void Semaforo::borrar(){//BORRA EL SEMÁFORO.
	semctl(id,0,IPC_RMID);
}

