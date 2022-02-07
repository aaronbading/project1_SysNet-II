// Server side Program 
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 60049   // defining a  port in range 60001 – 60099

int main(int argc, char const *argv[])
{
    int server_filedescriptor, created_socket; 
    long readvalue;
    struct sockaddr_in mysocketaddress; //socket address struck defined in in.h
    int addresslength = sizeof(mysocketaddress);

    // this is the message that will be sent ..

    char* message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!"; 


 // Creating socket file descriptor 
 // really creating a tcp socket 
 //For TCP/IP sockets, we want to specify the IP address family (AF_INET)
 //virtual circuit service (SOCK_STREAM).
 // Since there’s only one form of virtual circuit service,
 // there are no variations of the protocol, so the last argument, protocol, is zero.

 // virtual circuit service  is sock_stream
    if ((server_filedescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    mysocketaddress.sin_family = AF_INET; //the IP address family
    mysocketaddress.sin_addr.s_addr = INADDR_ANY; // the address for the socket which is just an ip  
    mysocketaddress.sin_port = htons( PORT ); // the transport address which is the port number
    
    memset(mysocketaddress.sin_zero, '\0', sizeof(mysocketaddress.sin_zero) );
    
    // bind process parameters are the socket , socketaddress and the size of socketaddress
    if( bind(server_filedescriptor, (struct sockaddr*)&mysocketaddress, sizeof(mysocketaddress))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_filedescriptor, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nHello world!!";
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((created_socket = accept(server_filedescriptor, (struct sockaddr *)&mysocketaddress, (socklen_t*)&addresslength))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        readvalue = read( created_socket , buffer, 30000);
        printf("%s\n",buffer );

        write(created_socket , message , strlen(message));
        printf("------------------message sent-------------------");
        close(created_socket);
    }
    return 0;

}