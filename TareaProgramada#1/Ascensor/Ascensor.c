/*
LUIS EDUARDO ROJAS CARRILLO B86875.
ASCENSOR.CPP.
IMPREMENTACIÓ DE ASCENSOR.H.
MÉTODOS UTILIZADOS POR LOS HILOS ASCENSOR.
*/

#include "Ascensor.h"

Ascensor::Ascensor(long i){//CONSTRUCTOR ASCENSOR.
	cantMax=8;
	cantActual=0;
	pisoActual=1;
        mov=true;
	dir=false;
	id=i;
	b= new Buzon();
	s= new Semaforo();	
}

Ascensor::~Ascensor(){//DESTRUCTOR.

}

void Ascensor::recibirLlamados(){//RECIBE TODOS LOS LLAMADOS DE LAS PERSONAS POR MEDIO DE UN BUZON Y LOS COLOCA EN UNA COLA SEGÚN PISO ACTUAL DE LAS PERSONAS.
	datos d;
	bool seguir=true;
		while(seguir==true){
		d=b->recibir();
			if(d.id!=-1){
				switch(d.pisoA){
					case 1:
					piso1.push(d);
					aceptarPersona(d.id);
					break;

					case 2:
					piso2.push(d);
					aceptarPersona(d.id);
					break;

					case 3:
					piso3.push(d);
					aceptarPersona(d.id);
					break;

					case 4:
					piso4.push(d);
					aceptarPersona(d.id);
					break;

					case 5:
					piso5.push(d);
					aceptarPersona(d.id);
					break;

					case 6:
					piso6.push(d);
					aceptarPersona(d.id);
					break;

					case 7:
					piso7.push(d);
					aceptarPersona(d.id);
					break;

					case 8:
					piso8.push(d);
					aceptarPersona(d.id);
					break;

					case 9:
					piso9.push(d);
					aceptarPersona(d.id);
					break;

					case 10:
					piso10.push(d);
					aceptarPersona(d.id);
					break;

					default:
					printf("DEFAULT");
					piso1.push(d);
					
				}
			}else{
			seguir=false;		
			}
		}	
}

void Ascensor::recibaPersonas(){//RECIBE PERSONAS SEGÚN EL PISO ACTUAL DEL ASCENSOR.
			datos d;
				switch(pisoActual){
					case 1:
					if(!piso1.empty()){
							while((!piso1.empty())&&(cantActual<cantMax)){
					                      d=piso1.front();
								if(d.pisoD>pisoActual){
									prioridadSubida.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso1.pop();
								}else{
									prioridadBajada.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso1.pop();
								}
							}			
					}
					break;

					case 2:
					if(!piso2.empty()){
							while((!piso2.empty())&&(cantActual<cantMax)){
					                      d=piso2.front();
								if(d.pisoD>pisoActual){
									prioridadSubida.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso2.pop();
								}else{
									prioridadBajada.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso2.pop();
								}
							}			

					}
					break;

					case 3:
					if(!piso3.empty()){
							while((!piso3.empty())&&(cantActual<cantMax)){
					                      d=piso3.front();
								if(d.pisoD>pisoActual){
									prioridadSubida.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso3.pop();
								}else{
									prioridadBajada.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso3.pop();
								}
							}			

					}
					break;

					case 4:
					if(!piso4.empty()){
							while((!piso4.empty())&&(cantActual<cantMax)){
					                      d=piso4.front();
								if(d.pisoD>pisoActual){
									prioridadSubida.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso4.pop();
								}else{
									prioridadBajada.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso4.pop();
								}
							}			

					}
					break;

					case 5:
					if(!piso5.empty()){
							while((!piso5.empty())&&(cantActual<cantMax)){
					                      d=piso5.front();
								if(d.pisoD>pisoActual){
									prioridadSubida.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso5.pop();
								}else{
									prioridadBajada.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso5.pop();
								}
							}			

					}
					break;

					case 6:
					if(!piso6.empty()){
							while((!piso6.empty())&&(cantActual<cantMax)){
					                      d=piso6.front();
								if(d.pisoD>pisoActual){
									prioridadSubida.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso6.pop();
								}else{
									prioridadBajada.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso6.pop();
								}
							}			

					}
					break;

					case 7:
					if(!piso7.empty()){
							while((!piso7.empty())&&(cantActual<cantMax)){
					                      d=piso7.front();
								if(d.pisoD>pisoActual){
									prioridadSubida.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso7.pop();
								}else{
									prioridadBajada.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso7.pop();
								}
							}			

					}
					break;

					case 8:
					if(!piso8.empty()){
							while((!piso8.empty())&&(cantActual<cantMax)){
					                      d=piso8.front();
								if(d.pisoD>pisoActual){
									prioridadSubida.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso8.pop();
								}else{
									prioridadBajada.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso8.pop();
								}
							}			

					}
					break;

					case 9:
					if(!piso9.empty()){
							while((!piso9.empty())&&(cantActual<cantMax)){
					                      d=piso9.front();
								if(d.pisoD>pisoActual){
									prioridadSubida.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso9.pop();
								}else{
									prioridadBajada.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso9.pop();
								}
							}			

					}
					break;

					case 10:
					if(!piso10.empty()){
							while((!piso10.empty())&&(cantActual<cantMax)){
					                      d=piso10.front();
								if(d.pisoD>pisoActual){
									prioridadSubida.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso10.pop();
								}else{
									prioridadBajada.push(d);
									cantActual++;
									aceptarPersona(d.id);
									piso10.pop();
								}
							}			

					}
					break;

					default:
					printf("DEFAULT");					
				}
}

void Ascensor::moverAscensor(){//SE ENCARGA DEL MOVIMIENTO DEL ASCENSOR SEGÚN LA PRIORIDAD DE LAS PERSONAS.
	datos d;
	if(mov==true){
		pisoActual++;
		display();
		bool sacar=false;
			while((!prioridadSubida.empty())&&(sacar==false)){
				d=prioridadSubida.top();
					if(d.pisoD==pisoActual){
						aceptarPersona(d.id);
						prioridadSubida.pop();
						cantActual--;
					}else{
						sacar=true;					
					}
			}
		
			if(pisoActual==10){
				mov=false;	
			}
	}else{
		pisoActual--;
		display();
	        bool sacar=false;
			while((!prioridadBajada.empty())&&(sacar==false)){
				d=prioridadBajada.top();
					if(d.pisoD==pisoActual){
						aceptarPersona(d.id);
						prioridadBajada.pop();
						cantActual--;
					}else{
						sacar=true;
					}
			}

			if(pisoActual==1){
				mov=true;
			}
	}
}

void Ascensor::aceptarPersona(int n){//SE ENCARGA DE HACER UN SIGNAL AL HILO PERSONA POR MEDIO DE SU ID.
	s->Signal(n);
}

bool Ascensor::apagarAscensor(){//REVISE SI NO HAY MÁS SOLICITUDES DE PERSONAS.
	bool retorno=false;
		if((prioridadSubida.empty()==true) && (prioridadBajada.empty()==true)){
			if((piso1.empty()==true) && (piso2.empty()==true) && (piso3.empty()==true) && (piso4.empty()==true) && (piso5.empty()==true) && 			(piso6.empty()==true) && (piso7.empty()==true) && (piso8.empty()==true) && (piso9.empty()==true) && (piso10.empty()==true)){
				retorno=true;
			}
		}
	return retorno;
}

void Ascensor::apagar(){//DESTRUYE EL BUZON Y SEMÁFORO.
	b->destruir();
	s->destruir();
}

void Ascensor::display(){//MUESTA EL PISO ACTUAL DEL ASCENSOR.
	printf("Ascensor, piso actual: %i \n", pisoActual);
}
