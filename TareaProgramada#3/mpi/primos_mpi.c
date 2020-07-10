/*
LUIS EDUARDO ROJAS CARRILLO - B86875
PRIMOS_MPI.C.
MÉTODO MPI PARA PRIMOS.
DEFINICIÓN Y EJECUCIÓN DE MÉTODOS.
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
#include <cstring>
#include <mpi.h>

using namespace std;

vector<int> primos;//VECTOR DE NUMEROS PRIMOS.
vector<vector<int>> matriz;//MATRIZ DE DATOS TOTALES.
vector <vector<int>>::iterator fila;
vector<int>::iterator colum;

void muestreMatriz(){//MUESTRA LA MATRIZ DE DATOS.
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

int main( int argc, char ** argv ) {//MAIN, EJECUCUÓN MPI.
   int comm_sz;               
   int my_rank;               
   int valor;

   MPI_Init(NULL, NULL);//INICIALIZACIÓN MPI.
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 	
   
	int extremo=10;//EXTREMO DEL INTERVALO.
	int cantHilos=comm_sz;//CANTIDAD DE HILOS.	
	primos=criba_eratostenes(extremo*extremo);//VECTOR DE NÚMEROS PRIMOS.
	matriz.resize(extremo-1);//TAMAÑO MATRIZ DE DATOS.

	struct timespec start1, finish1;
	double elapsed1;
	
	if(my_rank==0){//RANK 0 CUENTA TIEMPO.
		clock_gettime(CLOCK_MONOTONIC, &start1);
	}
	
   	int final=extremo;
   	double totalNum=extremo*extremo;
   	int divisor=ceil(totalNum/cantHilos);
   	int actual=divisor;
   	vector<int> inf;

	
	for(int i=0;i<cantHilos;i++){//DISTRIBUCIÓN DE TAREAS POR RANK.
		if(i==0){
		    inf.push_back(0);	
		}else{
		    inf.push_back(actual);
		    actual+=divisor;
		}
	}

	
       if (my_rank != 0) {//TRABAJO DE CADA RANK.
    		int cuadrado1=inf[my_rank];
		int cuadrado2=cuadrado1+divisor;
		bool seguir=true;

		for (std::vector<int>::iterator it = primos.begin() ; ((it != primos.end()) && (seguir==true)); it++){
			if(*it>=cuadrado2){
				seguir=false;
			}
			if(*it>=cuadrado1 && *it<=cuadrado2){
				valor=*it;
				MPI_Send(&valor,1,MPI_INT, 0, 0, MPI_COMM_WORLD);//ENVÍO DE TRABAJO AL PROGRAMA 0.
			}
		}
		valor=-1;
		MPI_Send(&valor,1,MPI_INT, 0, 0, MPI_COMM_WORLD);
   } else {  
   
		int cuadrado1=inf[my_rank];
		int cuadrado2=cuadrado1+divisor;
		bool seguir=true;
		for (std::vector<int>::iterator it = primos.begin() ; ((it != primos.end()) && (seguir==true)); it++){//TRABAJO PROGRAMA 0.
			if(*it>=cuadrado2){
				seguir=false;
			}
			if(*it>=cuadrado1 && *it<=cuadrado2){
				matriz[(floor(sqrt(*it)))-1].push_back(*it);
			}
		}   	     		
      		for (int q = 1; q < comm_sz; q++) {
      			do{
         		MPI_Recv(&valor, 1, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);//RECIBE TRABAJO OTROS PROCESOS.
         			if(valor!=-1){
         				matriz[(floor(sqrt(valor)))-1].push_back(valor);
         			}
         		}while(valor!=-1);
      		} 
   }  
   
   if(my_rank==0){//DETIENE EL TIEMPO.
        clock_gettime(CLOCK_MONOTONIC, &finish1);
	elapsed1 = (finish1.tv_sec - start1.tv_sec);
	elapsed1 += ((finish1.tv_nsec - start1.tv_nsec)/1000000000.0);
   }
   
   if(my_rank==0){ //MUESTRA MATRIZ DE DATOS Y TIEMPO. 
   	muestreMatriz();
   	cout<<"TIEMPO MPI: "<<elapsed1<<endl;
   }
   
   MPI_Finalize(); //FINALIZA MPI.

   return 0;
}
