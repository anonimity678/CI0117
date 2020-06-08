#AL EJECUTAR EL PROGRAMA AGREAGAR "ECCI.HTML"
programa: main.o fileReader.o processHTML.o semaforo.o mapa.o
	g++ main.o fileReader.o processHTML.o semaforo.o mapa.o -o programa -lpthread
main.o: main.c fileReader.h processHTML.h semaforo.h mapa.h
	g++ -c main.c fileReader.h processHTML.h semaforo.h mapa.h
fileReader.o: fileReader.c semaforo.h processHTML.h mapa.h
	g++ -c fileReader.c semaforo.h processHTML.h mapa.h
processHTML.o: processHTML.c mapa.h semaforo.h
	g++ -c processHTML.c mapa.h semaforo.h
semaforo.o: semaforo.c semaforo.h
	g++ -c semaforo.c semaforo.h
mapa.o: mapa.c mapa.h
	g++ -c mapa.c mapa.h
