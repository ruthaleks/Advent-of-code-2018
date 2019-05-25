#include <stdio.h>
#include <stdlib.h>


int readNumber(char delimiter, FILE *filePointer, unsigned int size);
int myPow(int base, int power);
int ascii2Num(char asciiArray[]);


void main(void){
    FILE *filePointer;
    char filename[] = "input.txt";
    char asciiSign = ' ';
    /* Count the number of cordinates */ 
    int len=0;
    filePointer = fopen(filename, "r");
    while((asciiSign = fgetc(filePointer)) != EOF) if (asciiSign=='\n')len++;
    fclose(filePointer);
    printf("Number of coordinates: %d\n", len);
    
    int coord[len][2]; 
    int i;
    int xmax=0, ymax=0;
    filePointer = fopen(filename, "r");
    for(i=0;i<len;i++){
       coord[i][0] = readNumber(',', filePointer, 6);
       if(coord[i][0]>xmax) xmax = coord[i][0];
       fgetc(filePointer); // remove the space
       coord[i][1] = readNumber('\n', filePointer, 6);
       if(coord[i][1]>ymax) ymax = coord[i][1];
       //printf("i = %d, x=%d, y=%d\n",i, coord[i][0], coord[i][1]);
       }   
    fclose(filePointer);
    xmax++; ymax++;
    xmax++; ymax++;
    char grid[xmax][ymax];
    int x,y;
    for(x=0;x<xmax;x++){
        for(y=0;y<ymax;y++){
            grid[x][y] = '#';
        }    
    }
    
    int num=0;
    printf("\n");
    for(y=0;y<ymax;y++){
        for(x=0;x<xmax;x++){
                int dist=xmax+ymax;
                int dist_i;
                num=0;
            for(i=0;i<len;i++){
                int temp = abs(coord[i][0]-x)+abs(coord[i][1]-y);
                //printf("%c, x=%d, y=%d, temp=%d\n",'A'+i, x,y,temp);
                if(temp<dist){
                    dist=temp;
                    dist_i=i;
                    num=0;
                }else if (temp==dist){
                    num++;
                }
            }
            //printf("dist_i=%d, dist= %d\n", dist_i, dist);
            if(grid[x][y]=='#'){
                grid[x][y] ='A'+dist_i;
            }
            if(num>0){
                grid[x][y]='.';
            }
            printf("%c", grid[x][y]);
        }    
        printf("\n");
    }

    int area[len];

    for(i=0;i<len;i++) area[i] = 0;

    int index;
    for(y=0;y<ymax;y++){
        for(x=0;x<xmax;x++){
            if(grid[x][y]!='.'){
                index = (int) (grid[x][y]-'A');
                //printf("x=%d, y=%d, index = %d\n",x,y, index);
                if(x==0 || x==(xmax-1) || y==0 || y==(ymax-1)){
                    area[index] = -1;
                    //printf("area[index]=%d\n", area[index]);
                }else{
                    if(area[index]!=-1) area[index]++;
                }
            }            
        }    
    }
    int maxA=0;  
    printf("\n");
    for(i=0;i<len;i++){
        printf("%d ", area[i]);
        if(area[i]>maxA) maxA=area[i];
        }
    printf("\n");
    printf("Largest finite area = %d\n", maxA);
    
    printf("\n");
    maxA=0;
    int size = 10000;
    for(y=0;y<ymax;y++){
        for(x=0;x<xmax;x++){
                int temp=0;
            for(i=0;i<len;i++){
                temp += abs(coord[i][0]-x)+abs(coord[i][1]-y);
            }
            //printf("dist_i=%d, dist= %d\n", dist_i, dist);
            if(temp<size){
                grid[x][y] ='#';
                maxA++;
            }else{
                grid[x][y] = '.';
            }
            printf("%c", grid[x][y]);
        }    
        printf("\n");
    }
    printf("Size of the region containing all locations which have a total distance to all given coordinates of less than %d? = %d\n",size, maxA);
        

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


