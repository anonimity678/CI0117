/*
LUIS EDUARDO ROJAS CARRILLO - B86875.
MAIN.C.
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <thread>
#include <sys/wait.h>
#include <sys/shm.h>
#include "fileReader.h"
#include "processHTML.h"
#include "semaforo.h"

mapa global;

struct datos{//ESTRUCTURA PARA LA CREACIÓN DE HILOS FILEREADER.
 	char* archivo;
 	int id;
	double cant;
	long llave;
	double activos;
	int stra;
};

struct info{//ESTRUCTURA PARA LA CREACIÒN DE HILOS PROCESSHTML.
 	fileReader *p;
 	int id;
	mapa *m;
	char* archivo;
};

void * hiloProcess(void* args){//MÉTODO DE CADA HILO DE TIPO PROCESSHTML.
	struct info *inf=(struct info*)args;
	fileReader *monitor=(fileReader*)inf->p;//RECIBE FILEREADER COMPARTIDO.
	int id=inf->id;
	mapa *map=(mapa*)inf->m;
	
	do{
	}while(monitor->getEmpezar()==false);//LOOP DE ESPERA PARA TODOS LOS HILOS

	processHTML *process = new processHTML(monitor->getKey(),id);
	bool continuar=true;
		char* linea;
		linea = (char *)calloc( 512, 1 );

	do{	
		process->wait();//WAIT.
		continuar=monitor->hasNext(process->getId());
			if(continuar==true){
		  		linea=monitor->getNext();	
			}
		process->signal();//SIGNAL.
			if(continuar==true){
				process->processLine(linea);
			}
		sleep(0.3);
	}while(continuar==true);
	cout<<endl;
	cout<<"ETIQUETAS ARCHIVO: "<<inf->archivo<<" HILO: "<<id<<endl;
	process->muestre();

	process->wait();
	map->ingreseMapa(process->getMap());
	process->signal();

	return NULL;
}


void * hiloFileReader(void *args){//MÉTODO DE CADA HILO DE TIPO FILEREADER.
	struct datos *d2=(struct datos*)args;
	Semaforo *s=new Semaforo(1,999999);
	int hilos=d2->cant;
	int key=d2->llave;
	fileReader *monitor=new fileReader(d2->archivo,d2->activos,d2->stra,key);//DEFINE ESTRATEGIA.
	mapa *map = new mapa();//MAPA GLOBAL PARA ARCHIVO CADA ARCHIVO.

	std::thread processHTML[hilos];
	for(int i=0; i<hilos;i++){//CREACIÓN HILOS DE TIPO PROCESSHTML.
		struct info *inf = new struct info;
		inf->id=i;
		inf->p=monitor;
		inf->m=map;
		inf->archivo=d2->archivo;
		processHTML[i]= std::thread(hiloProcess,(void*)inf);
	}
	sleep(1);
	monitor->empiece();
	
	for(int i=0; i<hilos;i++){
		 processHTML[i].join();
	}
	
	cout<<endl;
	cout<<"ETIQUETAS TOTALES DEL ARCHIVO: "<<d2->archivo<<endl;
	map->muestre();

	s->Wait();
	global.ingreseMapa(*map);
	s->Signal();

	

}


int main( int argc, char ** argv ) {//HILO PRINCIPAL.
	if ( argc < 2 ) {
      		printf( "No indico el archivo a utilizar, salimos\n" );
      		exit( 1 );
  	 }
	long key=100000;//LLAVE PARA CADA HILO.
	int cantArchivos=(argc-2);//CANTIDAD DE ARCHIVOS A PROCESAR.
	double cantWorkers=atoi(argv[2]);//CANTIDAD DE HILOS A CREAR DE TIPO PROCESS.
	int workersActivos=atoi(argv[2]);//CANTIDAD DE HILO DESTINADOS A TRABAJAR.
	int strategia=atoi(argv[1]);//ESTRATEGIA A UTILIZAR.

	std::thread fileReader[cantArchivos];//CREACIÓN HILOS FILEREADER.
	for(int i=1; i<cantArchivos;i++){//CREACIÓN DE HILOS SEGÚN LA CANTIDAD DE ARCHIVOS.
		struct datos *d1=new struct datos;	
		d1->archivo= argv[i+2];
		d1->id=i;
		d1->cant=cantWorkers;
		d1->llave=key;
		d1->activos=workersActivos;
		d1->stra=strategia;
		key++;
		fileReader[i]= std::thread(hiloFileReader,(void *) d1);
	}
	
	for(int i=1; i<cantArchivos;i++){
		fileReader[i].join();
	}

	cout<<endl;
	cout<<"ETIQUETAS DE TODOS LOS ARCHIVOS: "<<endl;
	global.muestre();

	return 0;
}
