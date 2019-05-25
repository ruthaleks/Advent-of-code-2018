#include <stdio.h>
#include <stdlib.h>

/*NOTES: A=65..Z=90, a=97..z=122 
 * diff between capital and lower case letters = 32*/

_Bool Cap(char a);
_Bool Low(char a);
char getUnit(char a);
int react(char units[], int len);

void main(void){
    FILE *filePointer;
    char filename[] = "input.txt";
    char asciiSign;
    int len=0;

    filePointer = fopen(filename, "r");
    while((asciiSign = fgetc(filePointer)) != EOF) len++;
    fclose(filePointer);
    /* Put all letters in an array */
    char units[len];
    char units2[len];
    int i=0; 
    filePointer = fopen(filename, "r");
    while((asciiSign = fgetc(filePointer)) != EOF){
        units[i] = asciiSign;
        i++;
    }
    fclose(filePointer);
    for(i=0;i<len;i++)units2[i]=units[i];
    printf("No. of units remaining: %d\n", react(units, len));
    
    char l;
    char a[len];
    int best=len-2;
    int temp, j;
    for(i=0;i<26;i++){
        l='A'+i;
        int z=0;
        for(j=0;j<len-2;j++){
            if(units2[j]!=l && units2[j]!=getUnit(l)){
                a[z]=units2[j];
                z++;
            }
        a[z] = '\0';
        }
        //printf("%s\n", a);
        temp = react(a,z+2);
        printf("temp = %d\n", temp);
        if(temp<best)best=temp;
    }
    printf("Lenght of shortest polymerer: %d\n", best);
}

int react(char units[], int len){
    int i;
    char l1, l2;
    int counter=len-2; 
    for(i=1;i<len-2;i++){
        l1 = units[i-1]; l2=units[i];
        //printf("i = %d, l1 = %c, l2 = %c\n", i, l1, l2);
        /*Check for polarity*/
        if(Cap(l1)!=Cap(l2)){
            int j=i-1;
            int y=i;
            while(getUnit(l1)==l2){
                counter=counter-2;
                units[j] = '#';
                units[y] = '#';
          //      printf("j = %d, y = %d, l1 = %c, l2 = %c, c = %d\n", j,y,l1, l2, counter);
                while(units[j]=='#' && j>0){
                    j--;
                    l1 = units[j];
                }
                while(units[y]=='#' && y<len-2){
                    y++;
                    l2 = units[y];
                }
                
            }
            i=y;
        }
    }
    return(counter);
}

_Bool Cap(char a){
    if(a>='A' && a<='Z'){
        return(1);
    }else{
        return(0);
    }
}

_Bool Low(char a){
    if(a>='a' && a<='z'){
        return(1);
    }else{
        return(0);
    }
}

char getUnit(char a){
    if(a>='A' && a<='Z'){
        return(a+32);
    }else if (a>='a' && a<='z'){
        return(a-32);
    }else{
        return('0');
    }
}

