all: cliente servidor
cliente: MirrorClientTest.o Socket.o servidor
	g++ -o cliente MirrorClientTest.o Socket.o
servidor: MirrorServerTest.o Socket.o
	g++ -o servidor MirrorServerTest.o Socket.o
MirrorClientTest.o: MirrorClientTest.c Socket.h
	g++ -c MirrorClientTest.c Socket.h
MirrorServerTest.o: MirrorServerTest.c Socket.h
	g++ -c MirrorServerTest.c Socket.h

Socket.o: Socket.c Socket.h
	g++ -c Socket.c Socket.h


