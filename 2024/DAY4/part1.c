#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 100000
#define MAX_ARRAY_LENGTH 1000


int checkXMAS(char* inputString){
    int count = 0;
    for(int i = 0; i < strlen(inputString) - 3; i++){
        if(inputString[i] == 'X' && inputString[i+1] == 'M' && inputString[i+2] == 'A' && inputString[i+3] == 'S'){
            count++;
        }
    }
    return count;
}

int checkReverseXMAS(char* inputString){
    int count = 0;
    for(int i = 0; i < strlen(inputString) - 3; i++){
        if(inputString[i] == 'S' && inputString[i+1] == 'A' && inputString[i+2] == 'M' && inputString[i+3] == 'X'){
            count++;
        }
    }
    return count;
}

int checkVerticalXMAS(char** inputStringArray, int size){
    int count = 0;
    for(int i = 0; i < size - 3; i++){
        for(int j = 0; j < strlen(inputStringArray[0]); j++){
            if(inputStringArray[i][j] == 'X' && 
               inputStringArray[i+1][j] == 'M' && 
               inputStringArray[i+2][j] == 'A' && 
               inputStringArray[i+3][j] == 'S'){
                count++;
            }
        }
    }
    return count;
}
int checkVerticalReverseXMAS(char** inputStringArray, int size){
    int count = 0;
    for(int i = 0; i < size - 3; i++){
        for(int j = 0; j < strlen(inputStringArray[0]); j++){
            if(inputStringArray[i][j] == 'S' && 
               inputStringArray[i+1][j] == 'A' && 
               inputStringArray[i+2][j] == 'M' && 
               inputStringArray[i+3][j] == 'X'){
                count++;
            }
        }
    }
    return count;
}

int checkDiagonalXMAS(char** inputStringArray, int size){
    int count = 0;
    for(int i = 0; i < size - 3; i++){
        for(int j = 0; j < strlen(inputStringArray[0]) - 3; j++){
            // down right
            if(inputStringArray[i][j] == 'X' && 
               inputStringArray[i+1][j+1] == 'M' && 
               inputStringArray[i+2][j+2] == 'A' && 
               inputStringArray[i+3][j+3] == 'S'){
                count++;
            }
            // down right reverse XMAS
            if(inputStringArray[i+3][j+3] == 'X' && 
               inputStringArray[i+2][j+2] == 'M' && 
               inputStringArray[i+1][j+1] == 'A' && 
               inputStringArray[i][j] == 'S'){
                count++;
            }
        }
    }
    return count;
}
int checkDiagonalReverseXMAS(char** inputStringArray, int size){
    int count = 0;
    for(int i = 0; i < size - 3; i++){
        for(int j = 3; j < strlen(inputStringArray[0]); j++){
            // down left
            if(inputStringArray[i][j] == 'S' && 
               inputStringArray[i+1][j-1] == 'A' && 
               inputStringArray[i+2][j-2] == 'M' && 
               inputStringArray[i+3][j-3] == 'X' ){
                count++;
            }
            // down left reverse XMAS
            if(inputStringArray[i+3][j-3] == 'S' && 
               inputStringArray[i+2][j-2] == 'A' && 
               inputStringArray[i+1][j-1] == 'M' && 
               inputStringArray[i][j] == 'X' ){
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

    for(int j = 0; j < index; j++){
        totalCount += checkXMAS(inputStringArray[j]);
        totalCount += checkReverseXMAS(inputStringArray[j]);
    }

    totalCount += checkVerticalXMAS(inputStringArray, index);
    totalCount += checkVerticalReverseXMAS(inputStringArray, index);
    totalCount += checkDiagonalXMAS(inputStringArray, index);
    totalCount += checkDiagonalReverseXMAS(inputStringArray, index);
    
    printf("%d\n", totalCount);


    free(inputStringArray);
    free(inputString);
    return 0;
}