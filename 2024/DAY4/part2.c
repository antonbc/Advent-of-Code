#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 100000
#define MAX_ARRAY_LENGTH 1000


int checkX_MAS(char** inputStringArray, int size){
    int count = 0;
    for(int i = 0; i < size - 2; i++){
        for(int j = 0; j < strlen(inputStringArray[0]) - 2; j++){
            /*
            M M
             A
            S S
            */
            if(inputStringArray[i][j] == 'M' && 
               inputStringArray[i+1][j+1] == 'A' &&
               inputStringArray[i+2][j+2] == 'S' &&
               inputStringArray[i+2][j] == 'S' &&
               inputStringArray[i][j+2] == 'M'){
                count++;
            }
            /*
            S M
             A
            S M
            */
            if(inputStringArray[i][j] == 'S' && 
               inputStringArray[i+1][j+1] == 'A' &&
               inputStringArray[i+2][j+2] == 'M' &&
               inputStringArray[i+2][j] == 'S' &&
               inputStringArray[i][j+2] == 'M'){
                count++;
            }
            /*
            S S
             A
            M M
            */
            if(inputStringArray[i][j] == 'S' && 
               inputStringArray[i+1][j+1] == 'A' &&
               inputStringArray[i+2][j+2] == 'M' &&
               inputStringArray[i+2][j] == 'M' &&
               inputStringArray[i][j+2] == 'S'){
                count++;
            }
            /*
            M S
             A
            M S
            */
            if(inputStringArray[i][j] == 'M' && 
               inputStringArray[i+1][j+1] == 'A' &&
               inputStringArray[i+2][j+2] == 'S' &&
               inputStringArray[i+2][j] == 'M' &&
               inputStringArray[i][j+2] == 'S'){
                count++;
            }
        }
    }
    return count;
}
int main(){
    FILE* inputFile = fopen("input.txt", "r");
    char** inputStringArray = (char**)malloc(sizeof(char*) * MAX_ARRAY_LENGTH);
    char* inputString = (char*)malloc(sizeof(char) * MAX_STRING_LENGTH);
    int index = 0, totalCount = 0;
    
    fread(inputString, sizeof(char), MAX_STRING_LENGTH, inputFile);
    fclose(inputFile);

    char* token = strtok(inputString, "\n");
    while(token != NULL){
        inputStringArray[index++] = token;
        token = strtok(NULL, "\n");
    }


    totalCount += checkX_MAS(inputStringArray, index);
    
    printf("%d\n", totalCount);


    free(inputStringArray);
    free(inputString);
    return 0;
}