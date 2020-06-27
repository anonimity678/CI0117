programa: primos.o Mutex.o
	g++ primos.o Mutex.o -o programa -lpthread -fopenmp
primos.o: primos.c Mutex.h
	g++ -c primos.c Mutex.h
Mutex.o: Mutex.c Mutex.h
	g++ -c Mutex.c Mutex.h
