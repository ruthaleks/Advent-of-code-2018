#include <stdio.h>
#include <stdlib.h>


int myPow(int base, int power);
unsigned int ascii2Num(unsigned long asciiNumber, unsigned int bytes);

void main(void){
    unsigned int minusLen = 1000;
    unsigned int plusLen  = 200000;
    
    char minus[minusLen];
    char plus[plusLen];

    int j;
    for(j=0;j<minusLen;j++){
        minus[j]=0;
        }
    for(j=0;j<plusLen;j++){
        plus[j]=0;
        }
     

    int stop = 0;
    char content;
    char fileName[] = "input.txt"; 
    unsigned long asciiNumber = 0;
    unsigned int byteCount = 0;
    unsigned int tempNum;    
    char op;
    FILE *filePointer;
    int result = 0;
    
    while(stop!=1){
    byteCount = 0;
    filePointer = fopen(fileName, "r");
    while((content = fgetc(filePointer)) != EOF && stop!=1 ){
        if(byteCount == 0){ 
            op = content;
            printf("%c\n", op);
            byteCount++; 
        }else if(content == 0x0a){
            printf("Before conversion in hex = %lx\n", asciiNumber);
            tempNum = ascii2Num(asciiNumber, (byteCount-1));
            printf("After conversion in dec %d\n", tempNum);
            if (op == '+'){
                result += tempNum;
            }else if (op=='-'){
                result -= tempNum;
            }
            printf("Result = %d\n", result);
            asciiNumber = 0;
            byteCount = 0;
            tempNum = 0;

            if(result >= 0 ){
                if(result > plusLen){
                    printf("STOP! Increase plusLen to at least = %d\n", result);
                    stop = 1;
                }else{
                    if(plus[result]==1){
                        printf("Found a match = %d\n",result);
                        stop = 1;
                    }else{
                        plus[result] = 1;
                    }
                }
            }else{
                if(result*(-1) > minusLen){
                    printf("STOP! Increase minusLen to at least = %d\n", result*(-1));
                    stop = 1;
                }else{
                    if(minus[result*(-1)]==1){
                        printf("Found a match = %d\n",result);
                        stop = 1;
                    }else{
                        minus[result*(-1)] = 1;
                    }
                }
            }
        }else{
            asciiNumber = (asciiNumber << 8);
            asciiNumber |= content;
            byteCount++; 
        }
    }
    fclose(filePointer);
}
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
        printf("i = %d, asciiSign = %x, number = %d\n", i, asciiSign, (asciiSign-'0')*myPow(10,i));
      } 
    return(number);
}
