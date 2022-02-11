#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) 
{
      char str1[80];
      char str2[20];
    
      strcpy(str1, "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length:");
      strcpy(str2, "12\n\nHello world!\n");
      strcat(str1, str2);

      printf("%s", str1);


     char mystr1[180];
     char mystr2[120];
    
      strcpy(mystr1, "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length:");
      strcpy(mystr2, "12\n<!DOCTYPE html>\n<html>\n<body>\n\n<h1> Hello World!</h1>\n<p>This is a paragraph.</p>\n\n</body>\n</html>\n");
      strcat(mystr1, mystr2);

      printf("%s", mystr1);

      return 0;
}