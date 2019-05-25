#include <stdio.h>
#include <stdlib.h>


void main(void){
    FILE *filePointer;
    FILE *filePointer2;
    char filename[] = "input.txt";
    char letter;
    
    unsigned int len = 26; 
    unsigned short alphCount[len];
    unsigned short index;
    
    unsigned short twoCount = 0;
    unsigned short threeCount = 0;

    unsigned short foundTwo=0;
    unsigned short foundThree=0;
    
    int stop = 0;
    char letter2; 
    int err = 0;
    int correctBox = 0;
    int stringLen= 26;
    char box[stringLen];
    char box2[stringLen];
    int j,a, i=0; 
    for(j=0;j<len;j++){
        alphCount[j]=0;
        }

    filePointer = fopen(filename, "r");
    while((letter = fgetc(filePointer)) != EOF){
        if(letter != 0x0a){
                index = (unsigned short)(letter - 'a');
                alphCount[index]++;
                box[i] = letter;
                i++;
             }else{
                box[i] = '\0';
                i = 0;
               // printf("Current string = %s\n",box);
                filePointer2 = fopen(filename, "r");
                letter2 = fgetc(filePointer2);
                while(letter2 != EOF && stop ==0){
                    for(a=0;a<(stringLen+1);a++){         
                        if(letter2!=0x0a){
                            box2[a] = letter2;
                            if(box[a] != letter2){
                                err++;
                            }     
                        }else{
                            box2[a]='\0';
                        }
                        letter2 = fgetc(filePointer2);
                    }
//                    printf("Error = %d\n", err);
                        
                    if(err == 1){
                        printf("FOUND CORRECT BOX IDs!\n");
                        printf("%s\n%s\n", box, box2);
                        stop = 1;
                    }
                        err = 0;
                 }
                 fclose(filePointer2);
                for(j=0;j<len;j++){
                    if (alphCount[j]!=0){
                      //  printf("%c,%d\n",(j+'a'),alphCount[j]);
                        if(alphCount[j]==2 && foundTwo== 0){
                            twoCount++;
                            foundTwo=1;
                        }else if(alphCount[j]==3 && foundThree==0){
                            threeCount++;
                            foundThree=1;
                        }
                        alphCount[j]=0;
                    }
                 }
                foundTwo=0;
                foundThree=0;                 
                //printf("---------\n"); 
             }    
    }
    printf("letter appear twice = %d\n",twoCount);
    printf("letter appear three times = %d\n", threeCount);  
    printf("checksum = %d\n", (twoCount*threeCount));
   fclose(filePointer);
}


