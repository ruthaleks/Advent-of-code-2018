#include <stdio.h>
#include <stdlib.h>

FILE *filePointer;

int myPow(int base, int power);
unsigned int ascii2Num(unsigned long asciiNumber, unsigned int bytes);
int readNumber(char delimiter);


void main(void){
    char filename[] = "input.txt";
    char asciiSign;
    unsigned int leEd;
    unsigned int toEd;
    unsigned int recWi;
    unsigned int recHi;

    unsigned int fabricLen = 998;
    unsigned int fabricHig = 997;

    unsigned char fab[fabricLen][fabricHig];
    unsigned int result = 0;
    int a; 
    
    unsigned int err;
    char id[10];
    char correctID[10];

    int i,j;
    for(i=0;i<fabricLen;i++){
        for(j=0;j<fabricHig;j++){
        fab[i][j] = 0;
        }
    }
    for (a=0;a<2;a++){
    int index = 0;
    filePointer = fopen(filename, "r");
    while((asciiSign = fgetc(filePointer)) != EOF){
        if(asciiSign == '@'){
            id[index] = '\0';
            index = 0;
            asciiSign = fgetc(filePointer); // remove the space 
            leEd = readNumber(',');            
            toEd = readNumber(':');
            
            asciiSign = fgetc(filePointer); // remove the space
            recWi = readNumber('x');
            recHi = readNumber('\n');
            
            if(fabricLen < (leEd + recWi)) fabricLen = (leEd + recWi);
            if(fabricHig < (toEd + recHi)) fabricHig = (toEd + recHi);

            //printf("Inches from left edge = %d\n", leEd);
            //printf("Inches from top edge = %d\n", toEd);
            //printf("Rectable width = %d\n", recWi);
            //printf("Rectable hight = %d\n", recHi);
            //printf("\n----------------\n");
            err = 0;
            for(i=(leEd);i<(leEd+recWi);i++){
                for(j=(toEd);j<(toEd+recHi);j++){
                    if(fab[i][j] == 0){
                        if (a==0) fab[i][j] = 1; // claim
                    }else if(fab[i][j] == 1){
                        if(a==0) fab[i][j] = 2; //clamed by two or more
                    }else if(a==1 && fab[i][j]==2){
                        err++;
                    }
                }
            }
            
         if(err==0 && a==1){
            for(i=0;i<10;i++) {
            correctID[i] = id[i];} 
            printf("%s\n",id);
         }
         }else{
            id[index] = asciiSign;
            index++;

         }
        
     }   
   fclose(filePointer);
   }
   printf("Fabric size = %dx%d\n", fabricLen, fabricHig);
   

    for(i=0;i<fabricLen;i++){
        for(j=0;j<fabricHig;j++){
            if (fab[i][j] == 2){ 
            result++;
            //printf("res = %d, i = %d, j = %d\n", result, i, j);
            }
        }
    }
    printf("Result = %d\n", result);
    printf("Correct ID = %s\n", correctID);
 

}

int readNumber(char delimiter){
    int byteCount = 0;
    unsigned long asciiNumber;
    char asciiSign = fgetc(filePointer);

    byteCount = 0; asciiNumber = 0;
    while(asciiSign != delimiter){
        byteCount++;
        asciiNumber = (asciiNumber << 8);
        asciiNumber |= asciiSign;
        asciiSign = fgetc(filePointer);
    }
    return(ascii2Num(asciiNumber, byteCount));
}
int myPow(int base, int power){
    int result = base;
    int i;
    if (power==0){
        return(1);
    }else if(power>0){
        for(i=1; i<power; i++){
            result *= base;
        }
        return(result);
    }else if(power<0){
        for(i=1; i<power; i++){
            result *= 1/base;
        }
        return(result);
     }else{
        return(0);
    }
}

unsigned int ascii2Num(unsigned long asciiNumber, unsigned int bytes){
    unsigned int number = 0;
    int i;
    unsigned char asciiSign; 
    for(i=0; i<bytes; i++){
        asciiSign = (unsigned char)(asciiNumber & 0xFF); 
        number += (asciiSign - '0') * myPow(10,i);
        asciiNumber = (asciiNumber >> 8);        
//        printf("i = %d, asciiSign = %x, number = %d\n", i, asciiSign, (asciiSign-'0')*myPow(10,i));
      } 
    return(number);
}

