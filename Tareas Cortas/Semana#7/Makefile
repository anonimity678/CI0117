#AL EJECUTAR EL PROGRAMA AGREAGAR "ECCI.HTML"
programa: processHTML.o mapa.o
	g++ -o programa processHTML.o mapa.o
processHTML.o: processHTML.c mapa.h
	g++ -c processHTML.c mapa.h
mapa.o: mapa.c mapa.h
	g++ -c mapa.c mapa.h
