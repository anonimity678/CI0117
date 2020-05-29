/* 
LUIS EDUARDO ROJAS CARRILLO - B86875.
CLASE PROCESSHTML.C.
MAIN Y MÉTODO.
UTILIZADO PARA LEE Y CONTAR ETIQUETAS DE UN HTML.
UTILIZA STRTOK_R() PARA LA EJECUCIÓM CON HILOS.
*/
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "mapa.h"
using namespace std;

mapa datos;//VARIABLE GLOBAL PARA CONTAR TODAS LAS ETIQUETAS.

void processLine( const char * line, int cont) {//LEE EL ARCHIVO POR LINEAS, UTILIZA STRTOK_R().
   char * token;
   char *saveptr1;
   mapa datos2;
   cout<<line<<endl;
   token = strtok_r( (char * ) line, "< >\t\n", &saveptr1 );
   while ( NULL != token ) {
	cout<<token<<endl;
      	datos.insertar(token);
	datos2.insertar(token);
      	token = strtok_r( NULL, "< >\t\n", &saveptr1 );
   }
   cout<<"Etiquetas de la linea "<<cont<<": "<<endl;
   datos2.muestre();
   printf( "\n" );
}


int main( int argc, char ** argv ) {//MAIN.
   FILE * fileId;
   int chars;
   size_t size;
   char * line;
   int cont=0;
	
   if ( argc < 2 ) {
      printf( "No indico el archivo a utilizar, salimos\n" );
      exit( 1 );
   }

   size = 512;
   line = (char *)calloc( 512, 1 );

   fileId = fopen( argv[ 1 ], "r" );
   if ( NULL == fileId ) {
      perror( "El archivo no se pudo abrir");
      exit( 2 );
   }

  do {	
      chars = getline( & line, & size, fileId );//LEE LINEA POR LINEA DE TAMAÑO 512.
      processLine( line, cont);
      cont++;
   }while(chars>0);

   datos.muestre();

   free( line );
   fclose( fileId );						 	 		
}
