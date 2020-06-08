/*
LUIS EDUARDO ROJAS CARRILLO - B86875.
PROCESSHTML.C.
DESARROLLO DE MÉTODOS E IMPLEMENTACIÓN.
*/
#include "processHTML.h"

processHTML::processHTML(int llave, int i){//CONSTRUCTOR.
	key=llave;
	s=new Semaforo(1,key);
	id=i;
}

processHTML::~processHTML(){//DESTRUCTOR.
	//free(lineaActual);
}

void processHTML::signal(){//SIGNAL.
 	s->Signal();
}

void processHTML::wait(){//WAIT.
	s->Wait();
}

void processHTML::processLine(char* linea){//PROCESA LINEA Y CUENTA ETIQUETAS.
	token = strtok_r( linea, "< >\t\n", &saveptr1 );
  	while ( NULL != token ) {
      		map.insertar(token);
      		token = strtok_r( NULL, "< >\t\n", &saveptr1 );
   	}
}



void processHTML::muestre(){//MUESTRA EL MAPA.
	map.muestre();
}

int processHTML::getId(){//RETORNO EL ID.
	return id;
}	

