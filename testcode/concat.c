#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) 
{
      char str1[16];
      char str2[16];
    
      strcpy(str1, "sssss");
      strcpy(str2, "kkkk");
      strcat(str1, str2);
      printf("%s", str1);
      return 0;
}