#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
   char ch, file_name[25] , myfile[100];
   FILE *fp;
      strcpy(file_name, "index.html");
   fp = fopen(file_name, "r"); // read mode

   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }


int i =0;
   while((ch = fgetc(fp)) != EOF)
      {
         // printf("%c", ch);
          myfile[i] = ch;
          i++;
      }
   fclose(fp);
       printf("%s",myfile);

   return 0;
}