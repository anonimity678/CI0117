/*
LUIS EDUARDO ROJAS CARRILLO - B86875
PRIMOS.C.
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <omp.h>
#include <cstring>
#include "Mutex.h"

using namespace std;

Mutex *mutex;//SHARED VARIABLES.
int cantFinal;
int pareja1;
int pareja2;
vector<int> primos;

vector<vector<int>> matriz;//MATRIZ DE DATOS.
vector <vector<int>>::iterator fila;
vector<int>::iterator colum;

struct datos{//ESTRUCTURA PARA DATOS DE PTHREADS.
	int num1;
	int num2;
};

void mostrar(vector<int> criba){//MUESTRA EL VECTOR DE NÚMEROS PRIMOS.
	for (int i = 0; i < criba.size(); i++){
	        cout << criba[i] << "\t";
	    	cout << endl;
	}
}

vector<int> criba_eratostenes(int n){//CREA EL VECTOR DE NÚMEROS PRIMOS. 	
vector<int> criba;
int current_primo;  	
	for (int i = 2; i <= n; i++){
        	criba.push_back(i);
	}
        
	if (n == 2 || n == 3){ 
		return criba;
	}

vector<int>::iterator it = criba.begin();
current_primo = *it; 

	do{
        vector<int>::iterator it2 = it + 1;
        	for(; it2 <= criba.end(); it2++){
            		if(*it2 % current_primo == 0){
                		criba.erase(it2);
			}
		}
        it++;
        current_primo = *it;

    	}while(pow(current_primo, 2) < n);
 return criba;
}

void openMP(int workers, int n){//MÉTODO CON OPENMP.
	
   double hilos=workers;
   int final=n;
   double totalNum=n*n;
   int divisor=ceil(totalNum/hilos);
   int actual=divisor;
   vector<int> inf;

	for(int i=0;i<workers;i++){
		if(i==0){
		    inf.push_back(0);	
		}else{
		    inf.push_back(actual);
		    actual+=divisor;
		}
	}
	
	omp_set_num_threads(hilos);
	#pragma omp parallel for
	for(int i=0; i<workers; i++){
		int cuadrado1=inf[i];
		int cuadrado2=cuadrado1+divisor;
		bool seguir=true;

		for (std::vector<int>::iterator it = primos.begin() ; ((it != primos.end()) && (seguir==true)); it++){
			if(*it>=cuadrado2){
				seguir=false;
			}
			if(*it>=cuadrado1 && *it<=cuadrado2){
				#pragma omp critical
				matriz[(floor(sqrt(*it)))-1].push_back(*it);
			}
		}
		actual+=divisor;
	}
}

void * paralel( void * param ){//MÉTODO PARA PTHREADS.
	struct datos *d2=(struct datos*)param;
	int cuadrado1=d2->num1;
	int cuadrado2=d2->num2;
	int valor=0;
	
	bool seguir=true;

	for (std::vector<int>::iterator it = primos.begin() ; ((it != primos.end()) && (seguir==true)); it++){
		if(*it>=cuadrado2){
			seguir=false;
		}
		if(*it>=cuadrado1 && *it<=cuadrado2){
			matriz[(floor(sqrt(*it)))-1].push_back(*it);
		}
	}
}

void paralelPrimos(int cantWorkers, int n){//CREACIÓN DE PTHREADS.

   int hilos=cantWorkers;
   int inicio=0;
   int final=n;
   int totalNum=n*n;
   int divisor=totalNum/hilos;

	mutex = new Mutex();
	
   pthread_t * pthilos;

   pthilos = (pthread_t *) calloc( hilos, sizeof( pthread_t ) );

   for ( int hilo = 0; hilo < hilos; hilo++ ) {
	struct datos *d1=new struct datos;
		d1->num1=inicio;
		d1->num2=inicio+divisor;
      pthread_create( & pthilos[ hilo ], NULL, paralel, (void *)d1);
	inicio=inicio+divisor;
   }

   for ( int hilo = 0; hilo < hilos; hilo++ ) {
      pthread_join( pthilos[ hilo ], NULL );
   }

   free( pthilos );

}

void serialPrimos(int n){//MÉTODO SERIAL.
int cantTotal=0;
int in=0;
int f=0;

	for(int i=1; i<n; i++){
		cout<<"("<<i<<","<<i+1<<")"<<endl;
		bool seguir=true;

		int ini=i;
		int fin=i+1;

		int cuadrado1=ini*ini;

		int cuadrado2=fin*fin;
	
		int cantidad=0;


		cout<<"NÚMEROS: "<<endl;
	for (std::vector<int>::iterator it = primos.begin() ; ((it != primos.end()) && (seguir==true)); it++){
		    int valor=*it;
			if(valor>cuadrado2){
				seguir=false;
			}
			if(valor>cuadrado1 && valor<cuadrado2){
				cout<<valor<<"\t";
				cantidad++;				
			}			
		}
		cout<<endl;
		cout<<"CANTIDAD DE NÚMEROS PRIMOS: "<<cantidad<<endl;
		cout<<endl;

		if(cantidad>=cantTotal){
		in=ini;
		f=fin;
		cantTotal=cantidad;
		}
	}
	cout<<"MAYOR NÚMERO DE PRIMOS EN PAREJA: "<<endl;
	cout<<"("<<in<<","<<f<<")"<<endl;
	cout<<"CANTIDAD DE NÚMEROS PRIMOS: "<<cantTotal<<endl;
	
}

void muestreMatriz(){
	int cont=1;
	int intervalo=0;
	int cant=0;
	int cantFinal=0;
	for(fila=matriz.begin(); fila!=matriz.end(); fila++){
		cout<<"("<<cont<<","<<cont+1<<")"<<endl;
		cant=fila->size();
		cout<<"NUMEROS: "<<endl;
			for(colum=fila->begin(); colum!=fila->end(); colum++){
				cout<<*colum<<"\t";
			}
		cout<<endl;
		cout<<"CANTIDAD DE NÚMEROS PRIMOS: "<<cant<<endl;
	if(cant>=cantFinal){
		cantFinal=cant;
		intervalo=cont;
	}
	cout<<endl;
	cont++;
	}	
	cout<<"MAYOR NÚMERO DE PRIMOS EN PAREJA: "<<endl;
	cout<<"("<<intervalo<<","<<intervalo+1<<")"<<endl;
	cout<<"CANTIDAD DE NÚMEROS PRIMOS: "<<cantFinal<<endl;
}

int main( int argc, char ** argv ) {//MAIN, HILO PRINCIPAL.
	
	cantFinal=0;
	pareja1=0;
	pareja2=0;
	int extremo=10;//EXTREMO DEL INTERVALO.
	int cantHilos=5;//CANTIDAD DE HILOS.	
	primos=criba_eratostenes(extremo*extremo);
	matriz.resize(extremo-1);
	
	struct timespec start1, finish1;
	double elapsed1;
	clock_gettime(CLOCK_MONOTONIC, &start1);

	cout<<"PTHREADS"<<endl;//PARALELO.
	paralelPrimos(cantHilos,extremo);//CANTIDAD DE TRABAJADORES Y EXTREMO DEL INTERVALO.
	muestreMatriz();

	clock_gettime(CLOCK_MONOTONIC, &finish1);
	elapsed1 = (finish1.tv_sec - start1.tv_sec);
	elapsed1 += ((finish1.tv_nsec - start1.tv_nsec)/1000000000.0);
	cout<<"TIEMPO PTHREADS: "<<elapsed1<<endl;

	matriz.clear();
	matriz.resize(extremo-1);

	
	cout<<endl;
	cout<<"------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	struct timespec start2, finish2;
	double elapsed2;
	clock_gettime(CLOCK_MONOTONIC, &start2);

	cout<<"SERIAL"<<endl;//SERIAL.
	serialPrimos(extremo);

	clock_gettime(CLOCK_MONOTONIC, &finish2);
	elapsed2 = (finish2.tv_sec - start2.tv_sec);
	elapsed2 += ((finish2.tv_nsec - start2.tv_nsec)/1000000000.0);
	cout<<"TIEMPO SERIAL: "<<elapsed2<<endl;

	cout<<endl;
	cout<<"------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;


	struct timespec start3, finish3;
	double elapsed3;
	clock_gettime(CLOCK_MONOTONIC, &start3);

	cout<<"OPENMP"<<endl;//OPENMP.
	openMP(cantHilos,extremo);
	muestreMatriz();

	clock_gettime(CLOCK_MONOTONIC, &finish3);
	elapsed3 = (finish3.tv_sec - start3.tv_sec);
	elapsed3 += ((finish3.tv_nsec - start3.tv_nsec)/1000000000.0);
	cout<<"TIEMPO OPENMP: "<<elapsed3<<endl;

	matriz.clear();
	matriz.resize(extremo-1);
}
