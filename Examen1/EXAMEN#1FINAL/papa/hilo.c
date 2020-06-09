#include "hilo.h"

hilo::hilo(int id){

}

hilo::~hilo(){

}
		
void hilo::wait(int id){
	s->Wait(id);
}

void hilo::signal(int id){
	s->Signal(id);
}

void hilo::imprima(){
 cout<<"Recibo la papa"<<endl;
}	

