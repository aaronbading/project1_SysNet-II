#include "helper.h"
#include <string.h>

Helper::Helper()
{

    strcpy(part1, "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length:");
    strcpy(part2, "120\n<!DOCTYPE html>\n<html>\n<body>\n\n<h1> Hello World!</h1>\n<p>This is a paragraph.</p>\n\n</body>\n</html>\n");
    strcat(part1, part2);

    init();
    start();
}
void Helper::init()
{
    // this is mainly setup code
    // Creating socket file descriptor is really creating a tcp socket

    // For TCP/IP sockets, we want to specify the :  IP address family (AF_INET)
    //     virtual circuit service (SOCK_STREAM).
    //     Since there’s only one form of virtual circuit service,
    //     there are no variations of the protocol, so the last argument, protocol, is zero.

    // virtual circuit service  is sock_stream
    if ((server_filedescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    mysocketaddress.sin_family = AF_INET;         // the IP address family
    mysocketaddress.sin_addr.s_addr = INADDR_ANY; // the address for the socket which is just an ip
    mysocketaddress.sin_port = htons(PORT);       // the transport address which is the port number

    memset(mysocketaddress.sin_zero, '\0', sizeof(mysocketaddress.sin_zero));

    // bind process parameters are the socket , socketaddress and the size of socketaddress
    if (bind(server_filedescriptor, (struct sockaddr *)&mysocketaddress, sizeof(mysocketaddress)) < 0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_filedescriptor, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
}
void Helper::start()
{
    while (1)
    {
        strcpy(part1, "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length:");
        strcpy(part2, "220\n<!DOCTYPE html>\n<html>\n<body>\n\n<h1> Hello World!</h1>\n<p>This is a paragraph.</p>\n\n</body>\n</html>\n");
        strcat(part1, part2);

        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((created_socket = accept(server_filedescriptor, (struct sockaddr *)&mysocketaddress, (socklen_t *)&addresslength)) < 0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        readvalue = read(created_socket, buffer, 30000);
        // printf("%s\n",buffer );
        // TODO : create a process that takes care of one user so the other process doesnt hold and continue to attend to users
        interpretRequest(buffer);

        // we are writing whatever ends up in "part1" string to the client ....
        write(created_socket, part1, strlen(part1));
        printf("------------------message sent-------------------");
        close(created_socket);
        delay(2);
    }
}
void Helper::interpretRequest(char *input)
{
    bool catchit = false;
    char *pch, *ich;
    // printf("%s\n",input );
    pch = strtok(input, "\n");

    int i = 0;
    ich = strtok(pch, " "); // the delimeter is now an empty space
    while (ich != NULL)
    {
        // myarray[j] = ich;
        // printf("%s\n", ich);
        if (i == 1)
        {
            if (!strcmp(ich, "/"))
            {
                processrequest(0);
                catchit = true;
            }
            if (!strcmp(ich, "/index.html"))
            {
                processrequest(1);
                catchit = true;
            }
            if (!strcmp(ich, "/pic.prg"))
            {
                processrequest(2);
                catchit = true;
            }
        }

        ich = strtok(NULL, " ");
        i++;

    }
    if (!catchit)
    { // if catchit remained false that means we attained an unknow file name and therefore we must somehow send the code 404
      // TODO send 404
    }
}
void Helper::delay(unsigned long int seconds)
{
    unsigned long int count = 333333333, i, j;

    for (i = 0; i < seconds; i++)
        for (j = 0; j < count; j++)
            ;
}
void Helper::processrequest(int thecase)
{
    FILE *fp;
    char ch, file_name[25], myfile[150];
    int temp=0;
    char *myptr;  // these two are for the appending of the size of file read
    char buffer[200];

    switch (thecase)
    {
    case 0: // case where its just

        break;
    case 1: // case where its index.html

        strcpy(file_name, "index.html");
        fp = fopen(file_name, "r"); // read mode
        if (fp == NULL)
        {
            perror("Error while opening the file.\n");
            exit(EXIT_FAILURE);
        }
        while ((ch = fgetc(fp)) != EOF)
        {
            // printf("%c", ch);
            myfile[temp] = ch;
            temp++;
        }
        fclose(fp);
        // printf("%s", myfile);
        // printf("%ld", strlen(myfile));
        // printf("%d",temp );

        strcpy(part1, "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length:");
        //***append number
        if (asprintf(&myptr, "%d", temp) == -1) {
        perror("asprintf");
    } else {
        strcat(strcpy(buffer, part1), myptr);
        strcpy(part1,buffer);
        free(myptr);
    } 
        strcpy(part2, myfile);
        strcat(part1, part2);
        printf("%s\n", part1);

        //**
        break;
    case 2: // case where its something else

    default:
        break;
    }

}
