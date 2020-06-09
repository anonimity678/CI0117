#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "Mutex.h"

using namespace std;

Mutex *mutex;//SHARED VARIABLES.
int cantFinal;
int pareja1;
int pareja2;


struct datos{
	int num1;
	int num2;
};

void mostrar(vector<int> criba){

    for (int i = 0; i < criba.size(); i++)
        cout << criba[i] << "\t";

    cout << endl;
}

vector<int> criba_eratostenes(int n){
    vector<int> criba;
    int current_primo;  
    for (int i = 2; i <= n; i++)
        criba.push_back(i);
        
    if (n == 2 || n == 3) 
        return criba;

    vector<int>::iterator it = criba.begin();

    current_primo = *it; 

    do
    {
        vector<int>::iterator it2 = it + 1;

        for(; it2 <= criba.end(); it2++)
            if(*it2 % current_primo == 0)
                criba.erase(it2);

        it++;
        current_primo = *it;

    } while (pow(current_primo, 2) < n);

    return criba;
}

void * paralel( void * param ) {
	struct datos *d2=(struct datos*)param;
	int inicio=d2->num1;
	int final=d2->num2;
	int cuadrado1=inicio*inicio;
	int cuadrado2=final*final;
	vector<int> primos=criba_eratostenes(cuadrado2+1);
	vector<int> numeros;
	int cantidad=0;
	int valor=0;
	
	bool seguir=true;
	for(int i=0;(i<cuadrado2) && (seguir==true);i++){
		int valor=primos[i];
		if(valor>=cuadrado2){
			seguir=false;
		}
		if(valor>=cuadrado1 && valor<cuadrado2){
			numeros.push_back(valor);
			cantidad++;
		}
	}

	cout<<"("<<inicio<<","<<final<<")"<<endl;
	cout<<"Cantidad de números primos: "<<cantidad<<endl;
	cout<<"Números: "<<endl;
	mostrar(numeros);
	cout<<endl;


	   mutex->Lock();
   	   	if(cantFinal<cantidad){
			cantFinal=cantidad;
			pareja1=inicio;
			pareja2=final;
		}
   	   mutex->Unlock();	

}

void paralelPrimos(int cantWorkers, int n){

   int hilos=cantWorkers;
	int inicio=1;
	int final=n;
	mutex = new Mutex();
	
   pthread_t * pthilos;

   pthilos = (pthread_t *) calloc( hilos, sizeof( pthread_t ) );

   for ( int hilo = 0; hilo < hilos; hilo++ ) {
	struct datos *d1=new struct datos;
		d1->num1=inicio;
		d1->num2=inicio+1;
      pthread_create( & pthilos[ hilo ], NULL, paralel, (void *)d1);
	inicio=inicio+1;
   }

   for ( int hilo = 0; hilo < hilos; hilo++ ) {
      pthread_join( pthilos[ hilo ], NULL );
   }
	cout<<"Mayor número de primos en pareja: "<<endl;
	cout<<"("<<pareja1<<","<<pareja2<<")"<<endl;
	cout<<"Cantidad de números primos: "<<cantFinal<<endl;

   free( pthilos );

}

void serialPrimos(int n){
vector<int> primos=criba_eratostenes((n*n)+1);
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
	
		cout<<"Numeros: "<<endl;
		for(int j=0; seguir==true; j++){
		    int valor=primos[j];
			if(valor>=cuadrado2){
				seguir=false;
			}
			if(valor>cuadrado1 && valor<cuadrado2){
				cout<<valor<<endl;
				cantidad++;				
			}
			
		}
		cout<<"Cantidad de números primos:"<<cantidad<<endl;
		cout<<endl;

		if(cantidad>cantTotal){
		in=ini;
		f=fin;
		cantTotal=cantidad;
		}
	}
	cout<<"Mayor número de primos en pareja: "<<endl;
	cout<<"("<<in<<","<<f<<")"<<endl;
	cout<<"Cantidad de números primos: "<<cantTotal<<endl;
	
}


int main( int argc, char ** argv ) {

	clock_t start, finish;
	double used;
	double used2;
	

	cantFinal=0;
	pareja1=0;
	pareja2=0;
	int extremo=10;

	cout<<"PARALELO"<<endl;
	start = clock();
	paralelPrimos(extremo-1,extremo);//CANTIDAD DE TRABAJADORES Y EXTREMO DEL INTERVALO.
   	finish = clock();
   	used = ((double) (finish - start)) / CLOCKS_PER_SEC;
	cout<<"Time: "<<used<<endl;

	cout<<endl;

	cout<<"SERIAL"<<endl;
	cantFinal=0;
	pareja1=0;
	pareja2=0;
	start = clock();
	serialPrimos(extremo);
	finish = clock();
   	used2 = ((double) (finish - start)) / CLOCKS_PER_SEC;
	cout<<"Time: "<<used<<endl;
	cout<<"Time: "<<used2<<endl;
}
