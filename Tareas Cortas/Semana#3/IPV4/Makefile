programa: ipv4-test.o Socket.o
	g++ -o programa ipv4-test.o Socket.o
ipv4-test.o: ipv4-test.c Socket.h
	g++ -c ipv4-test.c Socket.h
Socket.o: Socket.c Socket.h
	g++ -c Socket.c Socket.h
