#include<stdio.h>
#include<string.h>

#ifndef NBIT
#define NBIT 8
#endif



void transmitByte(char,int,int);

int main(int argc, char **argv){
	int i;// to loop over the byte
	char c;//char  is 1 byte only 
	int parity,flagparity=0;//parity and parity check flag

	//checking options
	for (i=0;i<argc;i++){
		if (strcmp(argv[i],"--parity=odd")==0){
			parity=1;
			flagparity=1;
		}else if(strcmp(argv[i],"--parity=even")==0){
			parity=0;
			flagparity=1;
		}
    }
	//looping through input
	while (scanf("%c", &c) != EOF)
	{	
		transmitByte(c,flagparity,parity);
		
	}
	return 0;
}

void transmitByte(char c,int flagparity,int parity){
printf("____");// start of transmission
	int i,bit;
		for (i=0; i<NBIT; i++)
		{
			bit=(c&(1<<i));//getting the ith bit
			
			if (flagparity){
				parity=parity^bit;
			}
			if (bit){
				printf("----");
			}else{
				printf("____");
			}
		}
		if (flagparity){
			if (parity){
				printf("----");
			}else{
				printf("____");
			}
		}
		printf("----");// end of transmission
}
