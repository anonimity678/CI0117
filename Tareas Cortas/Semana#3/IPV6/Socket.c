#include "Socket.h"
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

Socket::Socket( char tipo, bool ipv6 ){
	if(ipv6){
		if(tipo=='d'){
		id= socket(AF_INET6, SOCK_DGRAM,0);
		}
		if(tipo=='s'){
		id= socket(AF_INET6, SOCK_STREAM,0);
		}
	}else{
		if(tipo=='d'){
		id= socket(AF_INET, SOCK_DGRAM,0);
		}
		if(tipo=='s'){
		id=socket(AF_INET, SOCK_STREAM,0);
		}
	}
	
	if((id)==-1){
	printf("Error constructor");
	exit(0);
	}
}


Socket::~Socket(){
    Close();
}


void Socket::Close(){
	int retorno;
	retorno= close(id);
	if(retorno==-1){
		printf("Error destructor");
		exit(0);
	}
}

int Socket::Connect( char * hostip, int port ) {
	int retorno, largo;
	struct sockaddr_in servidor;
	
	servidor.sin_family= AF_INET;
	inet_aton(hostip, &servidor.sin_addr);
	servidor.sin_port=htons(port);
	largo=sizeof(servidor);
	retorno= connect(id, (struct sockaddr*) &servidor, largo);
	if(retorno==-1){
		printf("Error conectando");
		Close();
		exit(0);
	}	
return retorno;
}


int Socket::Connect( char *host, char *service ) {
    size_t len;
    int st;
    struct addrinfo hints, *result, *rp;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;   
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          

    st = getaddrinfo( host, service, &hints, &result);

    for ( rp = result; rp; rp = rp->ai_next ) {
        st = connect( id, rp->ai_addr, rp->ai_addrlen );
        if ( -1 == st ){
           printf("Error conectando");
	   Close();
	   exit(0);
	}
    }

    freeaddrinfo(result);
    return st;
}


int Socket::Read( char *text, int len ) {
	int retorno;
	retorno=read(id,(void*)text, len);
	if(retorno==-1){
		printf("Error read");
		Close();
		exit(0);
	}
	return retorno;
}


int Socket::Write( char *text, int len) {
	int retorno;
	retorno=write(id,(const void*)text, len);
	if(retorno==-1){
		printf("Error write");
		Close();
		exit(0);
	}
	return retorno;
}
