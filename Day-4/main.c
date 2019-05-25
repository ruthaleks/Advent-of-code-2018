#include <stdio.h>
#include <stdlib.h>

void SelectionSort(int A[], int size);
int readNumber(char delimiter, FILE *filePointer, unsigned int size);
int myPow(int base, int power);
int ascii2Num(char asciiArray[]);
void printVector(int A[], int size);
int findMinIndex(int A[], int startI, int size);
void switchI(int A[], int Imin, int i);
void switchS(char S[][40], int Imin, int i);
int getGuardNo(char content[][40], int i);

void main(void){
    FILE *filePointer;
    char filename[] = "input.txt";
    char asciiSign;
   
    /* Count number of rows in the file */
    int rows = 0;
    filePointer = fopen(filename, "r");
    while((asciiSign = fgetc(filePointer)) != EOF){
        if(asciiSign == '\n') rows++;
    }   
    fclose(filePointer);
    printf("Rows in the file = %d\n", rows);

    /* Extract year, month, day, hour, minute and info */
    int years[rows], months[rows], days[rows], hours[rows], minutes[rows];
    char content[rows][40];
    int i, index=0;
    filePointer = fopen(filename, "r");
    while((asciiSign = fgetc(filePointer)) != EOF){
        years[index] = readNumber('-',filePointer, 6);
        months[index] = readNumber('-',filePointer,4);
        days[index] = readNumber(' ',filePointer,4);
        hours[index] = readNumber(':',filePointer,4);
        minutes[index] = readNumber(']',filePointer,4);
               
        asciiSign = fgetc(filePointer); //remove space
        i = 0;
        while(asciiSign != '\n'){    
            content[index][i] = asciiSign;
            asciiSign = fgetc(filePointer); 
            i++;
        }
        content[index][i] = '\0';

    //    printf("%d/%d/%d  %d:%d  %s\n", years[index], months[index], days[index], hours[index], minutes[index], content[index]);
    index++;
    }
    fclose(filePointer);
    /* month*/
    for(int i=0; i<rows-1; i++){
        int Imin = findMinIndex(months, i, rows);
        switchI(months,Imin,i);
        switchI(days,Imin,i);
        switchI(hours,Imin,i);
        switchI(minutes,Imin,i);
        switchS(content, Imin, i);
    }
    /* day */
    int v = months[0]; 
    int sl = 0;
    for(i=0; i<rows+1; i++){
        if(v == months[i] && i!=rows){
        }else{
            for(int j=sl; j<i-1; j++){
                int Imin = findMinIndex(days, j, i);
                switchI(months,Imin,j);
                switchI(days,Imin,j);
                switchI(hours,Imin,j);
                switchI(minutes,Imin,j);
                switchS(content, Imin, j);
            }
            v=months[i];
            sl = i;
        }
    }
    /* hour */ 
    v = days[0]; 
    sl = 0;
    for(i=0; i<rows+1; i++){
        if(v == days[i] && i!=rows){
        }else{
            for(int j=sl; j<i-1; j++){
                int Imin = findMinIndex(hours, j, i);
                switchI(months,Imin,j);
                switchI(days,Imin,j);
                switchI(hours,Imin,j);
                switchI(minutes,Imin,j);
                switchS(content, Imin, j);
            }
            v=days[i];
            sl = i;
        }
    } 
    /* minutes */
    v = hours[0]; 
    int d = days[0];
    sl = 0;
    for(i=0; i<rows+1; i++){
        if(v == hours[i] && d==days[i] && i!=rows){
        }else{
            for(int j=sl; j<i-1; j++){
                int Imin = findMinIndex(minutes, j, i);
                switchI(months,Imin,j);
                switchI(days,Imin,j);
                switchI(hours,Imin,j);
                switchI(minutes,Imin,j);
                switchS(content, Imin, j);
            }
            v=hours[i];
            d=days[i];
            sl = i;
        }
    } 
    /* Input is now sorted! */
    printf("\n Sorted! \n");
    for(i=0;i<rows;i++){
        printf("%d-%d-%d %d:%d %s\n", years[i], months[i], days[i], hours[i], minutes[i], content[i]);
    }
    int maxG = 0;
    int guard = maxG;
    for(i=0;i<rows;i++){
        if(content[i][1] == 'G'){
            guard = getGuardNo(content, i);
            if(guard > maxG) maxG=guard;
            //printf("Guard No. = %d\n", guard);
        }
    }
    printf("No. of guards= %d\n", maxG);
    maxG++;
    int G[maxG];
    for(i=0;i<maxG;i++){
        G[i] = 0;
    }
    int t;        
    for(i=0;i<rows;i++){
        if(content[i][1] == 'G' && content[i+1][1] != 'G'){
            guard = getGuardNo(content, i);
            i++;
            t=0;
            while(content[i][1]!= 'G' && i<rows){
//            printf("time = %d\n", (minutes[i+1]-minutes[i]));
                t += (minutes[i+1] - minutes[i]);
                i = i + 2;
            }
            i--;

            G[guard] += t;
        }   
    }
    int sleepyTime = G[0];
    int sleepyIndex = 0;
    
    for(i=0;i<maxG;i++){
        if(G[i]>sleepyTime){
            sleepyTime = G[i];
            sleepyIndex = i;
        }
    }
    printf("Guard No. that sleeps the most: %d\n", sleepyIndex);
    printf("Total sleep minutes = %d\n", sleepyTime);
    
    /* Find the minute the guard sleeps the most */
    int time[60];

    for(i=0;i<60;i++){
        time[i] = 0;
    }

    for(i=0;i<rows;i++){
        if(content[i][1] == 'G' && content[i+1][1] != 'G'){
            guard = getGuardNo(content, i);
            if(guard==sleepyIndex){
                i++;
                while(content[i][1]!= 'G' && i<rows){
                    for(t=minutes[i]; t<minutes[i+1]; t++){
                        time[t]++;    
                    }
                    i = i + 2;
                }
            i--;
            }
            
        }   
    }
   printVector(time,60); 
   int sleepyMinute = 0;
   int value = time[sleepyMinute];
   for(i=0;i<60;i++){
        if(time[i]>value){
            sleepyMinute=i;
            value = time[i];
        }
   }    
   printf("Minute = %d, GuardID = %d, Minute*GuardID = %d\n", sleepyMinute, sleepyIndex, sleepyMinute*sleepyIndex);
   
   int Gtime[maxG][60];
   int j;

    for(i=0;i<maxG;i++){
        for(j=0;j<60;j++){
            Gtime[i][j] = 0;
        }
    }

    for(i=0;i<rows;i++){
        if(content[i][1] == 'G' && content[i+1][1] != 'G'){
            guard = getGuardNo(content, i);
            i++;
            while(content[i][1]!= 'G' && i<rows){
                for(t=minutes[i]; t<minutes[i+1]; t++){
                    Gtime[guard][t]++;    
                 }
                 i = i + 2;
            }    
            i--;
        }   
    }
    int g = 0;
    int tI = 0;
    int tV = Gtime[g][tI]; 

    for(i=0;i<maxG;i++){
        for(j=0;j<60;j++){
            if(Gtime[i][j]>tV){
                tV=Gtime[i][j];
                tI=j;
                g=i;
            }
        }
    }

   printf("Minute = %d, GuardID = %d, Minute*GuardID = %d\n", tI, g, tI*g);
}  


/*******************************************************************/
int getGuardNo(char content[][40], int i){
    int j = 2;
    int k;
    char temp[10];
    while(content[i][j] != '#')j++;
    j++; k=0;
    while( content[i][j]!= ' '){
        temp[k] = content[i][j];
        j++;k++;
    }
    temp[k] = '\0';
    return(ascii2Num(temp));
}

void switchS(char S[][40], int Imin, int i){
    char temp[40];
    int j=0;
    while(S[Imin][j] != '\0'){ //save the min value
        temp[j] = S[Imin][j];
        j++;
    }
    temp[j] = '\0';
    j=0;
    while(S[i][j] != '\0'){ //move value at index i to index Imin
        S[Imin][j] = S[i][j];
        j++;
    }
    S[Imin][j] = '\0';
    j=0; 
    while(temp[j] != '\0'){
        S[i][j] = temp[j];
        j++;
    }
    S[i][j] = '\0';
}

void switchI(int A[], int Imin, int i){
    int temp = A[Imin]; // save min value
    A[Imin] = A[i];     // move value att index i to intex Imin
    A[i] = temp;
}

void printVector(int A[], int size){
    int i;
    for(i=0;i<size;i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}

int findMinIndex(int A[], int startI, int size){
    int Imin = startI;
    for(int i = startI+1; i<size; i++){
       
        if(A[i] < A[Imin]){
            Imin = i;
        }
    }
    return(Imin);

}

	
void SelectionSort(int A[], int size){
	for(int i=0; i<size-1; i++){
		int Imin = i;
		for(int j=i+1; j<size; j++)
		{
			if( A[j] < A[Imin] )
			{
				Imin = j;
			}
		}
		int temp = A[Imin];
		A[Imin] = A[i];
		A[i] = temp;
	}
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

