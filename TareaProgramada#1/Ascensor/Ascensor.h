/*
LUIS EDUARDO ROJAS CARRILLO B86875.
ASCENSOR.H.
DEFINICIÓN DE MÉTODOS Y ATRIBUTOS.
*/

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <queue>
#include <bits/stdc++.h>

#include "semaforo.h"
#include "Buzon.h"


class Ascensor{

public:
        Ascensor(long);
        ~Ascensor();
	void display();
	void recibirLlamados();
	void aceptarPersona(int n);
	void moverAscensor();
	void recibaPersonas();
	bool apagarAscensor();
	void apagar();

	struct arriba {//SOBRECARGA DE OPERADOR PARA EL USO DE LA COLA DE PRIORIDAD.
		bool operator()(const datos& lhs, const datos& rhs){
		return lhs.pisoD<rhs.pisoD;	
		}
	};

	struct abajo {//SOBRECARGA DE OPERADOR PARA EL USO DE LA COLA DE PRIORIDAD.
		bool operator()(const datos& lhs, const datos& rhs){
		return lhs.pisoD>rhs.pisoD;	
		}
	};
private:
	int cantMax;//CANTIDAD MÁXIMA DE PERSONAS.
	int cantActual;//CANTIDAD ACTUAL DE PERSONAS.
	int pisoActual;//PISO ACTUAL DEL ASCENSOR.
	bool dir;//DIRECCIÓN DEL ASCENSOR.
 	long id;//ID DEL ASCENSOR.
	bool mov;//DIRECCIÓN DEL ASCENSOR.
	Buzon *b;//BUZON PARA RECIBIR MENSAJES DE LAS PERSONAS.
	Semaforo *s;//SEMÁFORO PARA SINCRONIZAR HILOS. 
	
	std::priority_queue<datos,std::vector<datos>,abajo> prioridadSubida;//COLA PRIORIDAD CUANDO VA SUBIENDO.
	std::priority_queue<datos,std::vector<datos>,arriba> prioridadBajada;//COLA PRIORIDAD CUANDO VA BAJANDO.
	std::queue<datos>piso1;//COLAS PARA CADA PISO.
	std::queue<datos>piso2;
	std::queue<datos>piso3;
	std::queue<datos>piso4;
	std::queue<datos>piso5;
	std::queue<datos>piso6;
	std::queue<datos>piso7;
	std::queue<datos>piso8;
	std::queue<datos>piso9;
	std::queue<datos>piso10;
};
