/**
 * This is the Helper class that will aid in doing the servers tasks .. 
 *
 * @author Aaron Bading
 * @date 02/11/22
 * @info Course COP4635
 */

#ifndef Helper_H
#define Helper_H
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

using namespace std;

#define PORT 60049   // defining a  port in range 60001 – 60099
class Helper
{
public:

Helper();
void init();
void start();
void interpretRequest(char* input);
void delay(unsigned long int seconds);
void processrequest(int thecase);

private:
    char* inputRedirect;	/* file name or NULL */
    int server_filedescriptor, created_socket; 
    long readvalue;
    struct sockaddr_in mysocketaddress; //socket address struck defined in in.h
    int addresslength = sizeof(mysocketaddress);


    //temp
    char part1[256];
     char part2[256];
};
#endif



