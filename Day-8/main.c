#include <stdio.h>
#include <stdlib.h>

int readNumber(char delimiter, FILE *filePointer, unsigned int size);
int myPow(int base, int power);
int ascii2Num(char asciiArray[]);
struct Status part(int a[], struct Status s);
struct Status part2(int a[], struct Status s);

struct Status{
    int index; 
    unsigned int sum;

};


void main(void){
    FILE *filePointer;
    char filename[] = "input.txt";
    char asciiSign;

    int len=0;
    filePointer = fopen(filename, "r");
    while((asciiSign = fgetc(filePointer)) != EOF) if (asciiSign==' ')len++;
    fclose(filePointer);

    filePointer = fopen(filename, "r");
    int tree[len];
    for(int j=0; j<len; j++){
        tree[j] = readNumber(' ', filePointer, 5);
        }   
   printf("\n");
   fclose(filePointer);
   
   struct Status status;
   status.index = 0;
   status.sum = 0;
    
   status = part(tree, status);
   printf("Sum = %d\n", status.sum);
   
   struct Status status2;
   status2.index = 0;
   status2.sum = 0;
   status2 = part2(tree, status2);
   printf("Value of the root node = %d\n", status2.sum);


}
struct Status part2(int a[], struct Status s){
    int children = a[s.index];
    int metaData = a[s.index+1];
    int score[children];
    s.index+=2;
    
    for(int j=0;j<children; j++){
        s = part2(a, s);
        score[j]=s.sum;
        s.sum=0;
    }
   
    if(children==0){
        for(int j=0; j<metaData; j++){
            s.sum+= a[s.index];
            s.index++;
        }
    }else{
        for(int j=0; j<metaData; j++){
            if(a[s.index]>0 && a[s.index]<=children){
                s.sum+= score[a[s.index]-1];
            }
            s.index++;
        }
    }
    

    return(s);

}

struct Status part(int a[], struct Status s){
    int children = a[s.index];
    int metaData = a[s.index+1];
    s.index+=2;

    for(int j=0;j<children; j++){
        s = part(a, s);
    }
    
    for(int j=0; j<metaData; j++){
        s.sum+= a[s.index];
        s.index++;
    }
    return(s);

}

int readNumber(char delimiter, FILE *filePointer, unsigned int size){
    int i = 0;
    char asciiArray[size];
    char asciiSign = fgetc(filePointer);

    while(asciiSign != delimiter){
        asciiArray[i] = asciiSign;
        asciiSign = fgetc(filePointer);
        i++;
    }
    asciiArray[i] = '\0';
    return(ascii2Num(asciiArray));
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

int ascii2Num(char asciiArray[]){
    int i = 0;
    int number = 0;
    while(asciiArray[i] != '\0'){
        i++;
    }
    i--;
    int pow = 0;
    while(i >= 0){
        number += ((asciiArray[i] - '0') * myPow(10,pow));
        i--; pow++;
    }
    return(number);
}

