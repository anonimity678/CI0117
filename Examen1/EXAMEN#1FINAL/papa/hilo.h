#ifndef HILO_H
#define HILO_H
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <iostream>

#include "semaforo.h"

using namespace std;

class hilo{
	public:
		hilo(int);
		~hilo();
		void wait(int id);
		void signal(int id);
		void imprima();	
	private:
		int id;	
		Semaforo *s;

};
#endif
