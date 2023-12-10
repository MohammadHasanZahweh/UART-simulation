#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#ifndef NBIT
#define NBIT 8
#endif

int toBit(char *);
char processByte(int, int);
void processError();
void detectStart();
int main(int argc, char **argv)
{
    int i;
    int parity, flagparity = 0;
    // checking options
    for (i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--parity=odd") == 0)
        {
            parity = 1;
            flagparity = 1;
        }
        else if (strcmp(argv[i], "--parity=even") == 0)
        {
            parity = 0;
            flagparity = 1;
        }
    }
    while (1)
    {
        detectStart();
        printf("%c", processByte(flagparity, parity));
    }
    return 0;
}

void detectStart(){
    // wait for a 0 (low) bit to start the transmission, acts as a synchronizer according to UART
    char bit[4];
    do
        {
            do
            {
                if ((scanf("%c", bit) == EOF)){ 
                    exit(0);
                    }
            } while (bit[0] != '_');//ignoring all starting high(-) margin anf waiting for low (_) to start transmission
            scanf("%c%c%c", bit + 1, bit + 2,bit+3);
        } while (toBit(bit) != 0);
}

int toBit(char *a)
{
    //This function takes 4 characters considering they are either - or _ and makes consider return the majority (acts as an error detector)
    int low;
    low = (a[0] == '_') + (a[1] == '_') + (a[2] == '_') + (a[3] == '_');
    if (low >= 2)
    {
        return 0;
    }
    return 1;
}

char processByte(int flagparity, int parity)
{   
    //takes: 
    //flagparity -> 1 for considering the parity and 0 to ignore
    //parity bit -> 1 for odd parity and 0 for even parity 
    char out = 0;
    int i;
    char bit[4];
    // since the start of transimission is covered in the detectStart function, we start by processing directly
    for (i = 0; i < NBIT; i++)
    {
        scanf("%c%c%c%c", bit, bit + 1, bit + 2,bit + 3); 
        out |= toBit(bit) << i;//setting the ith bit from LSB
        if (flagparity)
        {
            parity ^= toBit(bit);
        }
    }
    if (flagparity)
    {
        scanf("%c%c%c%c", bit, bit + 1, bit + 2,bit + 3);// processing the parity bit
        parity ^= toBit(bit);
        if (parity != 0)
        {
            processError();// function to process the error in transimision detected by the parity bit
        }
    }
    return out;
}

void processError(){
    printf("\n\nError\n\n");
    // exit(1);
}