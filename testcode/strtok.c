#include <stdio.h>
#include <string.h>
void process(char* input)
{
          printf("%s", input);

}
int main(int argc, char** argv) 
{
      
      //char str2[16];
    char inputChar[50];
    char *pch;
      strcpy(inputChar, "firstss aa \nnext\nlast");
    
    pch = strtok(inputChar, "\n");
int i = 0;
    while(pch != NULL)
    {
        if(i==0)
        {process(pch);}
        pch = strtok(NULL, " ");
        i++;
    }
      //strcpy(str2, "kkkk");
      //strcat(inputchar, str2);
    printf("%ld",strlen(inputChar));


      return 0;
}
