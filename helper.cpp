#include "helper.h"
#include <string.h>
//branch commit change
Helper::Helper()
{
    strcpy(returnstring, "\0");
    readfiles();

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
        perror("Error occured in socket");
        exit(EXIT_FAILURE);
    }

    mysocketaddress.sin_family = AF_INET;         // the IP address family
    mysocketaddress.sin_addr.s_addr = INADDR_ANY; // the address for the socket which is just an ip
    mysocketaddress.sin_port = htons(PORT);       // the transport address which is the port number

    memset(mysocketaddress.sin_zero, '\0', sizeof(mysocketaddress.sin_zero));

    // bind process parameters are the socket , socketaddress and the size of socketaddress
    if (bind(server_filedescriptor, (struct sockaddr *)&mysocketaddress, sizeof(mysocketaddress)) < 0)
    {
        perror("Error occured in bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_filedescriptor, 10) < 0)
    {
        perror("Error occured in listen");
        exit(EXIT_FAILURE);
    }
}
void Helper::start()
{
    while (1)
    {

        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((created_socket = accept(server_filedescriptor, (struct sockaddr *)&mysocketaddress, (socklen_t *)&addresslength)) < 0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        char buffer[30000];
        char message[2000];

        readvalue = read(created_socket, buffer, 30000);
        // printf("%s\n",buffer );

        // TODO : create a process that takes care of one user so the other process doesnt hold and continue to attend to users
        strcpy(message, interpretRequest(buffer));

        // we are writing whatever ends up in "part1" string to the client ....
        write(created_socket, message, strlen(message));
        

        printf("------------------message sent-------------------");
        close(created_socket);

        // delay(2);
    }
}

char *Helper::interpretRequest(char *input)
{

    bool catchit = false;
    char *pch, *ich;
    // printf("%s\n",input );
    pch = strtok(input, "\n");

    int i = 0;
    ich = strtok(pch, " "); // the delimeter is now an empty space
    while (ich != NULL)
    {
        if (i == 1)
        {
            if (!strcmp(ich, "/"))
            {
                return processrequest(0);
                catchit = true;
            }
            if (!strcmp(ich, "/index.html"))
            {
                return processrequest(1);
                catchit = true;
            }
            if (!strcmp(ich, "/testpresence.html"))
            {
                return processrequest(2);
                catchit = true;
            }
            if (!catchit)
            { // if catchit remained false that means we attained an unknow file name and therefore we must somehow send the code 404
              // TODO send 404
                return processrequest(3);
            }
        }

        ich = strtok(NULL, " ");
        i++;
    }

    return returnstring;
}
void Helper::delay(unsigned long int seconds)
{
    unsigned long int count = 333333333, i, j;

    for (i = 0; i < seconds; i++)
        for (j = 0; j < count; j++)
            ;
}

char *Helper::processrequest(int thecase)
{

    switch (thecase)
    {
    case 0: // case where its just
        return defaultfile;
        printf("defaultpage called");

        break;
    case 1: // case where its index.html
        return indexfile;
        printf("index called");

        break;
    case 2: // case where its something else
        return picturefile;
        printf("test called");

        break;

    case 3: // case where its just
        return notfoundfile;
        printf("notfound called");

        break;
    default:
        // return "\0";
        break;
    }
    // return "\0";

    return returnstring;
}

void Helper::doFile(char *filename, char *fillthis)
{
    char part1[500];
    FILE *fp;
    char ch, myfile[490];
    int temp = 0;
    char *myptr; // these two are for the appending of the size of file read
    char buffer[500];

    fp = fopen(filename, "r"); // read mode
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        myfile[temp] = ch;
        temp++;
    }
    fclose(fp);
    memset(part1, 0, strlen(part1));

    strcpy(part1, "HTTP/1.1 200 OK\nContent-Type: text/html  \nContent-Length: ");
    //***append number
    if (asprintf(&myptr, "%d", temp) == -1)
    {
        perror("error occured in asprintf");
    }
    else
    {
        strcat(strcpy(buffer, part1), myptr);
        strcpy(part1, buffer);
        free(myptr);
    }
    printf("inside dofile : what we read \n");
    printf("%s", myfile);
    printf("\n*********************END\n");
    strcat(part1, myfile);
    // printf("inside dofile ... printing contents of part1 at the very end");
    // printf("%s\n", part1);

    strcpy(fillthis, part1);

    //**
}
void Helper::readfiles()
{

    char file1name[25], file2name[25], file3name[25], file4name[25];
    char *files[4];
    strcpy(file1name, "defaultpage.html");
    strcpy(file2name, "index.html");
    strcpy(file3name, "notfound.html");
    strcpy(file4name, "testpresence.html");
    files[0] = file1name;
    files[1] = file2name;
    files[2] = file3name;
    files[3] = file4name;

    int filesize = 500;
    char myfile[filesize];
    char line[80] = {0};
    FILE *inputfp1;
    for (int i = 0; i < 4; i++)
    {
        inputfp1 = fopen(files[i], "r"); // Open file for read.
        if (inputfp1 == NULL)
        {
            printf("Error opening file");
            exit(0);
        }

        char lastline[8];
        strcpy(lastline, "</html>");
        int totalcount = 0;
        while (fgets(line, 80, inputfp1) != NULL)
        {
            if (strcmp(line, "</html>"))
            {
                
                for (size_t i = 0; i < strlen(line); i++)
                {
                    myfile[totalcount] = line[i];
                    totalcount++;
                }
            }
            else
            {
                for (size_t i = 0; i < strlen(lastline); i++)
                {
                    myfile[totalcount] = lastline[i];
                    totalcount++;
                }
                break;
            }
        }
        fclose(inputfp1); // close file

        // copy content of myfile ... into the correct file
        for (size_t j = 0; j < strlen(myfile); j++)
        {
            if (i == 0)
                defaultfile[j] = myfile[j];
            if (i == 1)
                indexfile[j] = myfile[j];
            if (i == 2)
                notfoundfile[j] = myfile[j];
            if (i == 3)
                picturefile[j] = myfile[j];
        }
        for (int j = 0; j < filesize; j++)
        {
            myfile[j] = '\0';
        }
    }
    // printf("%s\n", defaultfile);
    // printf("%s\n", indexfile);
    // printf("%s\n", notfoundfile);
    // printf("%s\n", picturefile);
    // after successfully reading all the files

    createMessage(defaultfile);
    createMessage(indexfile);
    createMessage(notfoundfile);
    createMessage(picturefile);

    printf("%s\n", defaultfile);
    printf("%s\n", indexfile);
    printf("%s\n", notfoundfile);
    // printf("%s\n", picturefile);

    //***************************
}

void Helper::createMessage(char *myfile)
{
    char part1[500];
    char *myptr; // these two are for the appending of the size of file read
    char buffer[500];
    //************************
    strcpy(part1, "HTTP/1.1 200 OK\nContent-Type: text/html  \nContent-Length: ");
    if (asprintf(&myptr, "%ld", strlen(myfile)) == -1)
    {
        perror("error occured in asprintf");
    }
    else
    {
        strcat(strcpy(buffer, part1), myptr);
        strcpy(part1, buffer);
        free(myptr);
    }
    // now part one contains our header for the default file

    strcat(part1, myfile); // put the inital headerpart and file together
    // printf("%s\n" , part1);

    // copy contents of part1 back into defaultfile .. so now default file has our full message
    for (size_t i = 0; i < strlen(part1); i++)
    {
        myfile[i] = part1[i];
    }
    // clear part1
    for (int i = 0; i < 500; i++)
    {
        part1[i] = '\0';
    }
}
