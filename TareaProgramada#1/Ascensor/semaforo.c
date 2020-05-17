/*
LUIS EDUARDO ROJAS CARRILLO B86875.
SEMAFORO.CPP.
MÉTODOS UTILIZADOS POR SEMÁFORO.
*/
#include "semaforo.h"

Semaforo::Semaforo(){//CONSTRUCTOR DE SEMÁFORO SIN SEMCTL.
	int status;
	
	id = semget(KEY, 100, IPC_CREAT|0666);//CREA SEMÁFORO, LLAVE DE .H,  1 SEMÁFORO, IPC_CREAT CREA.

	if(id==-1){//ERROR DE CONSTRUCCIÓN, RETORNA -1 SEMGET.
	perror("Construccion 1");
	//exit(1);//SALIDA
	}

}


Semaforo::Semaforo(int vi){//CONSTRUCTOR DE SEMÁFORO ORIGINAL.

	int status;
	
	id = semget(KEY, 100 ,IPC_CREAT|0666);//CREA SEMÁFORO, LLAVE DE .H,  1 SEMÁFORO, IPC_CREAT CREA.

	if(id==-1){//ERROR DE CONSTRUCCIÓN, RETORNA -1 SEMGET.
	perror("Construccion 2");
	//exit(1);//SALIDA
	}

	semun u;//CREA SEMUN
        u.val=vi;//INGRESA EN VALOR->VI

	status=semctl(id,0, SETVAL, u);//IDENTIFICADOR DE SEMAFOROS, SEMAFORO A ACCEDER, OPERACION A REALIZAR, ARG SENUM.

	if(status==-1){//ERROR DE INICIALIZACIÓN
	perror("Error inicialización");
	//exit(2);//SALIDA.
	}
}

Semaforo::~Semaforo(){//DESTRUCTOR.
	//semctl(id,0,IPC_RMID);//ID,0,BORRA GRUPO DE SEMAFOROS.
}

int Semaforo::Wait(int n){//WAIT, RECIBE ID SOBRE EL CUAL INTERACTUAR.
int a=n;
	sembuf s={a,-1,0};
	
        int status=semop(id,&s,1);
	
	if(status==-1){//ERROR
	perror("Error wait");
	//exit(1);//SALIDA.
	}

	return 0;
}

int Semaforo::Signal(int n){//SIGNAL, RECIBE ID SOBRE CUAL INTERACTUAR.
int a=n;	
	sembuf s={a,1,0};
	
        int status=semop(id,&s,1);
	
	if(status==-1){//ERROR
	perror("Error wait");
	//exit(1);//SALIDA.
	}

	return 0;
}


int Semaforo::getID(){//RETORNA ID DEL SEMÁFORO.
return id;
}

void Semaforo::destruir(){//DESTRUYE EL GRUPÓ DE SEMÁFOROS.
      semctl(id,0,IPC_RMID);//ID,0,BORRA GRUPO DE SEMAFOROS.
}

