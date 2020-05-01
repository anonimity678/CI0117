programa: ipv6-test.o Socket.o
	g++ -o programa ipv6-test.o Socket.o
ipv6-test.o: ipv6-test.c Socket.h
	g++ -c ipv6-test.c Socket.h
Socket.o: Socket.c Socket.h
	g++ -c Socket.c Socket.h
