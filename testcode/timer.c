#include <stdio.h>
#include <time.h>

//time related//////////
time_t rawtime;
struct tm * timeinfo;
////////////////////////
	
void delay(int seconds){
	unsigned long int count=333333333,i,j;
	
	for(i=0;i<seconds;i++)
	    for(j=0;j<count;j++);
}

void printTime(void){	
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf ( "Current local time and date: %s\n", asctime (timeinfo) );		
}

int main()
{    
	printf("Text1\n");
	printTime();    
	delay(1);	//delay for 1 second

	printf("Text2\n");
	printTime();    
	delay(10);	//delay for 2 seconds

	printTime();
	printf("Text3\n");
	return 0;
}