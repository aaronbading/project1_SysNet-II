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
#include <ctype.h>

using namespace std;

#define PORT 60049   // defining a  port in range 60001 – 60099
class Helper
{
public:

Helper();
void init();
void start();
char* interpretRequest(char* input);
void delay(unsigned long int seconds);
char* processrequest(int thecase);
void doFile(char* filename,char* fillthis);
void readfiles();
void createMessage(char* myfile);

private:
    int server_filedescriptor, created_socket; 
    long readvalue;
    struct sockaddr_in mysocketaddress; //socket address struck defined in in.h
    int addresslength = sizeof(mysocketaddress);
     
     char returnstring[2];

     //html files
char indexfile[490], notfoundfile[490], picturefile[490], defaultfile[490];
};
#endif



