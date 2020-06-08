/*
LUIS EDUARDO ROJAS CARRILLO - B86875.
FILEREADER.C.
DESARROLLO DE MÉTODOS E IMPLEMENTACIÓN.
*/
#include "fileReader.h"

fileReader::fileReader(const char *fileName, double cant,double act, int stra, int llave){//CONSTRUCTOR FILEREADER.
	workers=cant;
	activos=act;
	strategy=stra;
	continuar=true;
	key=llave;
	empezar=false;
	s=new Semaforo(1,key);
	divisor=0;
	cantLineas=0;
	total=0;
	tam=0;

	chars=0;
	size = 512;
   	line = (char *)calloc( 512, 1 );
	fileId = fopen( fileName, "r" );
	if ( NULL == fileId ) {
      		perror( "El archivo no se pudo abrir");
      		exit( 2 );
   	} 

	do{//CUENTA CANTIDAD DE LINEAS Y CHARS EN EL ARCHIVO.	
		chars = getline( &line, &size, fileId);
		cantLineas++;
		cantChars=cantChars+chars;
	}while(chars>0);
	divisor=(int)ceil(cantChars/workers);

	rewind(fileId);


	switch(strategy){
	case 1://ESTATICO CICLICO:
		cout<<"Estático Ciclico:"<<endl; 
		do{	
		chars = getline( &line, &size, fileId);
		cantLineas++;
		cantChars=cantChars+chars;
		}while(chars>0);
		
		divisor=(int)ceil(cantChars/workers);
		rewind(fileId);

		f=0;
		first=false;
		total=0;
		vectInicio[0]=0;
		vectActual[0]=0;
		for(int i=1; i<activos; i++){
			chars = getline( &line, &size, fileId);
			total+=chars;
			vectInicio[i]=total;
			vectActual[i]=total;
		
		}
		rewind(fileId);
	break;

	case 2://ESTATICO POR BLOQUE:
		cout<<"Estático Bloque:"<<endl;
		for(int i=0;i<=activos; i++){
			vectInicio[i]=i*divisor;
			vectActual[i]=i*divisor;
		}
		
		tam=(int)activos;
		vectInicio[tam]=cantChars;
		vectActual[tam]=cantChars;
	break;

	case 3:
		cout<<"Dinámico:"<<endl;
	break;	
	}	
}


fileReader::~fileReader(){//DESTRUCTOR FILEREADER.
	//free(line);
	//free(siguiente);
}


char* fileReader::getNext(){//RETORNA LINEA.
	return line;
}

bool fileReader::bloque(int worker){//ESTÁTICO POR BLOQUE.
	bool retorno=true;
	int tam=vectActual[worker];
	fseek(fileId, tam, SEEK_SET);

	chars = getline( &line, &size, fileId);	
	int actual=vectActual[worker];
	int ch=chars;
			if((chars==-1) || ((ch+actual)>vectInicio[worker+1])){
				retorno=false;
			}else{
				vectActual[worker]+=chars;
			}
return retorno;
}

bool fileReader::dinamico(int worker){//DINÁMICO.
	chars = getline( &line, &size, fileId);
	if(chars<0){
		continuar=false;
	}
	return continuar;
}

bool fileReader::ciclico(int worker){//ESTÁTICO CICLICO.
	bool retorno=true;
	if(f==activos){
		first=true;
	}
	f++;
	int tam=vectActual[worker];
	if(first==false){
	fseek(fileId, tam, SEEK_SET);
		chars = getline( &line, &size, fileId);	
		if(chars==-1){
			retorno=false;
		}else{
			vectActual[worker]+=chars;
		}
	}else{
		fseek(fileId, tam, SEEK_SET);
		for(int i=0; (i<activos) && (retorno==true); i++){
			chars = getline( &line, &size, fileId);	
			if(chars==-1){
				retorno=false;
			}else{
				vectActual[worker]+=chars;
			}
		}
	
	}
return retorno;
}

bool fileReader::hasNext(int worker){//HASNEXT GLOBAL.
	bool retorno=false;
	switch(strategy){
	case 1:
		retorno=ciclico(worker);
	break;
	case 2:
		retorno=bloque(worker);
	break;
	case 3:
		retorno=dinamico(worker);
	break;
	default:
	break;
	}
return retorno;
}

int fileReader::getKey(){//RETORNA LA LLAVE.
	return key;
}

void fileReader::empiece(){//EMPIEZA LA LINEA.
	empezar=true;
}

bool fileReader::getEmpezar(){//RETORNA EMPEZAR.
	return empezar;
}
