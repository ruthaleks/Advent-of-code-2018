#include <stdio.h>
#include <stdlib.h>


void main(void){
    FILE *filePointer;
    char filename[] = "input.txt";
    char asciiSign=' ';

    // 26 letters in the alphabet
    int size = 26;
    char alp[size][size+1];
    char alp2[size][size+1];
    char stepLetter, reqLetter;
    int stepIndex, reqIndex;

    for(int x=0; x<size;x++){
        for(int y=0; y<size+1; y++){
            alp[x][y] = '.';
            alp2[x][y] = '.';
        }
    }

    filePointer = fopen(filename, "r");
    while(asciiSign != EOF){
        while((asciiSign=fgetc(filePointer))!=' ');
        reqLetter = fgetc(filePointer);
        reqIndex = (reqLetter - 'A');
        alp[reqIndex][0] = reqLetter;
        alp2[reqIndex][0] = reqLetter;
        while((asciiSign=fgetc(filePointer))!= 'p');
        fgetc(filePointer); //remove space
        stepLetter = fgetc(filePointer);
        stepIndex = (stepLetter - 'A');
        alp[stepIndex][0]=stepLetter;
        alp[stepIndex][0]=stepLetter;
        alp2[stepIndex][0]=stepLetter;
        while((asciiSign=fgetc(filePointer))!= '\n');
        asciiSign = fgetc(filePointer);
        /********************************************/
        alp[stepIndex][reqIndex+1] = reqLetter;
        alp2[stepIndex][reqIndex+1] = reqLetter;
    }
    fclose(filePointer);
    char result[size+1]; 
    int i=0;
    for(int z=0; z<size; z++){
        printf("\n");
        for(int x=0; x<size;x++){
            for(int y=0; y<size+1; y++){
                printf("%c", alp[x][y]);
            }
        printf("\n");
        }
        if(alp[z][0]!='.'){
            _Bool ok=0;
            for(int v=1; v<size+1; v++){
                if(alp[z][v] != '.') {
                ok=0; 
                break;
                }else{
                ok=1;
                }
            }
            if(ok){
                result[i] = alp[z][0];
                alp[z][0] = '.';
                for(int r=0; r<size; r++) alp[r][z+1] = '.';
                z=-1; i++;
            }
       }
    }
    result[size] = '\0';
    printf("\nResult = %s\n", result);
    printf("\n");
    for(int x=0; x<size;x++){
        for(int y=0; y<size+1; y++){
            printf("%c", alp2[x][y]);
        }
    printf("\n");
    }
    int time=0;
    int nW=5;
    int worker[nW];
    char assign[nW];
    for(i=0; i<nW; i++){
        worker[i] = 0;
        assign[i] = '.';
    } 
    
    for(int z=0; z<size; z++){
        printf("----- Time = %d\n", time);
        printf("z = %d\n", z);
        if(alp2[z][0]!='.'){
            _Bool ok=0;
            for(int v=1; v<size+1; v++){
                if(alp2[z][v] != '.') {
                    ok=0; 
                    break;
                }else{
                    ok=1;
                    for(i=0;i<nW;i++){
                        printf("assign[i] = %c\n",assign[i]);
                        if(assign[i]==alp2[z][0]){
                        ok=0; 
                        break;
                        }
                    }
                }
            }
            printf("ok = %d\n", ok);
            if(ok){
                for(i=0; i<nW; i++){
                    if(worker[i]==0 && assign[i]=='.') {
                            worker[i] = (alp2[z][0]-'A'+61);
                            assign[i] = alp2[z][0];
                            break;
                    }

                }
                for(i=0;i<nW;i++)printf("worker = %d, worker[i] = %d, assign[i] = %c\n", i, worker[i], assign[i]);
            }
            }
            printf("HEJ\n");
            if(z==(size-1)){
               for(i=0; i<nW; i++){
                    printf("Worker = %d, worker[i] = %d, assign[i] = %c\n", i, worker[i], assign[i]);
                     if(worker[i] > 0){
                        worker[i]--;
                     }
                     if(worker[i]==0 && assign[i]!='.'){
                            int index = assign[i]-'A';
                            assign[i]='.';
                            alp2[index][0] = '.';
                            for(int r=0; r<size; r++) alp2[r][index+1] = '.';
                         
                     }
                    printf("Worker = %d, worker[i] = %d, assign[i] = %c\n", i, worker[i], assign[i]);
                }
                _Bool cl=0;
                    printf("\n");
                for(int a=0; a<size; a++){
                    printf("%c", alp2[a][0]);
                    if(alp2[a][0]!='.'){ 
                        cl=1; 
                        break;
                    }
                }
                    printf("\n");
                printf("----CL = %d\n", cl);
                if(cl) z=-1;
                time++;
                for(int x=0; x<size;x++){
                    for(int y=0; y<size+1; y++){
                    printf("%c", alp2[x][y]);
                }
                printf("\n");
                }
            }
       
    }
    printf("\n");
    for(int x=0; x<size;x++){
        for(int y=0; y<size+1; y++){
            printf("%c", alp2[x][y]);
        }
    printf("\n");
    }
    printf("Total time = %d\n", time);
}
