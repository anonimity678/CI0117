/*
LUIS EDUARDO ROJAS CARRILLO - B86875.
FILEREADER.C.
DESARROLLO DE MÉTODOS E IMPLEMENTACIÓN.
*/
#include "fileReader.h"

fileReader::fileReader(const char *fileName,double act, int stra, int llave){//CONSTRUCTOR FILEREADER.
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

	switch(strategy){
	case 1://ESTATICO CICLICO:
		cout<<"Estático Ciclico:"<<endl; 
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
		
		do{//CUENTA CANTIDAD DE LINEAS Y CHARS EN EL ARCHIVO.	///TRABAJARLO
			chars = getline( &line, &size, fileId);
			cantLineas++;
			cantChars=cantChars+chars;
		}while(chars>0);
		
		divisor=(int)ceil(cantChars/activos);
		rewind(fileId);

		cout<<"Estático Bloque:"<<endl;
		for(int i=0;i<activos; i++){
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

	case 4://ESTRATEGIA PERSONAL PARES, ENTREGA DOS LINEAS CONSECUTIVAMENTE A CADA TRABAJADOR.
		cout<<"Estratégia Pares:"<<endl;
		total=0;
		vectInicio[0]=0;
		vectActual[0]=0;
		vectCant[0]=0;
		for(int i=1; i<activos;i++){
			for(int j=0; j<2;j++){
			chars=getline(&line,&size,fileId);
			total+=chars;		
			}
			vectInicio[i]=total;
			vectActual[i]=total;
			vectCant[i]=0;
		}
		rewind(fileId);
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

bool fileReader::personal(int worker){//MÉTODO DE DISTRIBUCIÓN DE TAREAS PERSONAL.
bool retorno=true;
int tam=vectActual[worker];
fseek(fileId, tam, SEEK_SET);

	if(vectCant[worker]<2){
		chars=getline(&line,&size,fileId);
		if(chars==-1){
			retorno=false;
		}else{
			vectActual[worker]+=chars;
			vectCant[worker]++;			
		}
	}else{
		for(int i=0;((i<activos-1)&&(retorno==true));i++){
			for(int j=0; j<2;j++){
				chars=getline(&line,&size,fileId);
				if(chars==-1){
					retorno=false;
				}else{
					vectActual[worker]+=chars;
					vectCant[worker]=0;
				}
			}
		}
		chars=getline(&line,&size,fileId);
		vectActual[worker]+=chars;
		vectCant[worker]++;
	}
return retorno;
}

bool fileReader::bloque(int worker){//ESTÁTICO POR BLOQUE.
	bool retorno=true;
	int tam=vectActual[worker];
	fseek(fileId, tam, SEEK_SET);

	chars = getline( &line, &size, fileId);	
	int actual=vectActual[worker];
	int ch=chars;
			if((chars==-1) || ((ch+actual)>=vectInicio[worker+1])){
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
	if(worker<activos){
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

		case 4:
			retorno=personal(worker);
		break;
		default:
		break;
		}
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
