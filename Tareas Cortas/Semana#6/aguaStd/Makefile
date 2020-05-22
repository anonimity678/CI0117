programa: aguastd.o Mutex.o
	g++ aguastd.o Mutex.o -o programa -lpthread
aguastd.o: aguastd.c Mutex.h
	g++ -c aguastd.c Mutex.h
Mutex.o: Mutex.c Mutex.h
	g++ -c Mutex.c Mutex.h
