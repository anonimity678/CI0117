/*
//LUIS EDUARDO ROJAS CARRILLO B86875
BUZON.CPP
BUZON DE MENSAJES.
DESARROLLO DE MÉTODOS.
*/

#include "Buzon.h"

Buzon::Buzon(){//CONSTRUCTOR.
	id=msgget(KEY,IPC_CREAT | 0666);

	if(id<0){
		cout<<"Error al crear la cola de mensajes"<<endl;
		exit(1);
	}
}

Buzon::~Buzon(){//DESTRUCTOR.
	msgctl(id,IPC_RMID,0);
}

void Buzon::EnviarDouble(double x){//ENVIAR DOUBLE.
	longitud=sizeof(mensajeDouble)- sizeof(mensajeDouble.tipo);
	mensajeDouble.tipo=1;
	mensajeDouble.cadena=x;
	
	if(msgsnd(id, &mensajeDouble, longitud, 0)==-1){
	cout<<"Error enviando mensaje"<<endl;	
	}
}

double Buzon::RecibirDouble(){//RECIBIR DOUBLE.
	longitud=sizeof(mensajeString)- sizeof(mensajeString.tipo);
	id=msgget(KEY, IPC_CREAT|0666);
	if(id==-1){
            perror("Recibir");
	    exit(0);	
	}
	if(msgrcv(id, &mensajeDouble, longitud,1,0)==-1){//LEE PRIMER MENSAJE.
	        cout<<"Error recibiendo mensaje"<<endl;
	}else{
		cout<<"Mensaje: "<<mensajeDouble.cadena<<endl;
		return mensajeDouble.cadena;
	}
}

void Buzon::EnviarString(string x){//ENVIAR STRING.
	longitud=sizeof(mensajeString)- sizeof(mensajeString.tipo);
	mensajeString.tipo=1;
	mensajeString.cadena=x;
	
	if(msgsnd(id, &mensajeString, longitud, 0)==-1){
	printf("Error enviando mensaje");	
	}
}

string Buzon::RecibirString(){//RECIBIR STRING.
	longitud=sizeof(mensajeString)- sizeof(mensajeString.tipo);
	id=msgget(KEY, IPC_CREAT|0666);
	if(id==-1){
            perror("Recibir");
	    exit(0);	
	}
	if(msgrcv(id, &mensajeString, longitud,1,0)==-1){//LEE PRIMER MENSAJE.
		printf("Error recibiendo mensaje");
	}else{
		cout<<mensajeString.cadena<<endl;
		return mensajeString.cadena;
	}
}
