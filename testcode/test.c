
// #include <stdio.h>
// #include <string.h>
// int main(void) {


//     char * line = "hello, world";
//     char buffer[32]; // ok, this array is big enough for our operation

//     int i;
//     for (i = 0; i < strlen(line) + 1; i++) 
//     {
//         buffer[i] = line[i];
//     }

//     printf("buffer : %s", buffer);

//     return 0;
// //}
// C program to Append a Character to a String

#include <stdio.h>
#include <string.h>



int main()
{//testcomment
	// declare and initialize string
	char str[6] = "Geek";

	// declare and initialize char
	char ch = 's';

	// print string
	printf("Original String: %s\n", str);
	printf("Character to be appended: %c\n", ch);

	// append ch to str
	strncat(str, &ch, 1);

	// print string
	printf("Appended String: %s\n", str);


    char* mystring = "ye";
    char* myseconds = " yup";
	//printf("my message: %s\n", message);
    //printf("my message: %ld\n", strlen(message));


    char* message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 120\n\n"; 
    char* addtoit = "Hello world!";
	      strcat(message, addtoit);

        printf("%s\n",message );

	return 0;
}
