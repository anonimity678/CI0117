/*
LUIS EDUARDO ROJAS CARRILLO B86875.
BUZON.CPP.
BUZON DE MENSAJES.
DESARROLLO DE MÉTODOS.
*/

#include "Buzon.h"

Buzon::Buzon(){//CONSTRUCTOR DE BUZON.
	id=msgget(KEY2,IPC_CREAT | 0666);
	if(id==-1){
		cout<<"Error al crear la cola de mensajes"<<endl;
		exit(1);
	}
}


Buzon::~Buzon(){//DESTRUCTOR DE BUZON.
	//msgctl(id,IPC_RMID,0);
}

void Buzon::enviar(int a, int b, int c){//ENVÍA MENSAJE CON TRES DATOS.
	longitud=sizeof(mensaje)-sizeof(mensaje.tipo);
	mensaje.tipo=1;
	mensaje.valores[0]=a;
	mensaje.valores[1]=b;
	mensaje.valores[2]=c;
	
	if(msgsnd(id, &mensaje, longitud, 0)==-1){
	cout<<"Error enviando mensaje"<<endl;	
	}
}

datos Buzon::recibir(){//RECIBE MENSAJE CON TRES DATOS Y RETORNA UNA ESTRUCTURA CON SU INFORMACIÓN.
	datos d;
	longitud=sizeof(mensaje)-sizeof(mensaje.tipo);
	id=msgget(KEY2, IPC_CREAT|0666);
	if(id==-1){
            perror("Recibir");
	    exit(0);	
	}
	if(msgrcv(id, &mensaje, longitud,1,IPC_NOWAIT)==-1){//LEE PRIMER MENSAJE.
	}else{
	d.id=mensaje.valores[0];
	d.pisoA=mensaje.valores[1];
	d.pisoD=mensaje.valores[2];		
	}
return d;
}

void Buzon::destruir(){//DESTRUYE LA COLA DE MENSAJES.
	msgctl(id,IPC_RMID,0);
}
