programa: main.o Ascensor.o Persona.o Buzon.o semaforo.o
	g++ main.o Ascensor.o Persona.o Buzon.o semaforo.o -o programa -lpthread
main.o: main.c Ascensor.h Persona.h Buzon.h semaforo.h
	g++ -c main.c Ascensor.h Persona.h Buzon.h semaforo.h
Ascensor.o: Ascensor.c Ascensor.h Buzon.h semaforo.h
	g++ -c Ascensor.c Ascensor.h Buzon.h semaforo.h
Persona.o: Persona.c Persona.h Buzon.h semaforo.h
	g++ -c Persona.c Persona.h Buzon.h semaforo.h
Buzon.o: Buzon.c Buzon.h
	g++ -c Buzon.c Buzon.h
semaforo.o: semaforo.c semaforo.h
	g++ -c semaforo.c semaforo.h




