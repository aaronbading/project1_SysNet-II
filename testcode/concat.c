#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) 
{
      char str1[36];
      char str2[36];
    
      strcpy(str1, "ssssasdadsdads\n asddadssd");
      strcpy(str2, "kkkk");
      strcat(str1, str2);
      printf("%sasda", str1);
      printf("\n");
       memset(str1,0,strlen(str1));
      printf("%sasda", str1);

char* type;
type ="text/html";
      return 0;
}