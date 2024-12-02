#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_ROW_LENGTH 100


bool isSafe(int columnCount, int* rowData){
    bool isIncreasing = false;
    bool isDecreasing = false;

    // iterate through the rowData 
    for(int i = 0; i < columnCount - 1; i++){
        int difference = rowData[i] - rowData[i+1];

        if( difference > 0){
            isIncreasing = true;
        } else if(difference < 0){
            isDecreasing = true;
        }

        if(abs(difference) < 1 || abs(difference) > 3)
            return false;
    }

    // return true if one of them are increasing or decreasing 
    return !(isIncreasing && isDecreasing); 
}

bool isSafeWhenRemovingOne(int columnCount, int* rowData){
    for(int i = 0; i < columnCount; i++){
        int tempRow[MAX_ROW_LENGTH];
        int tempColumnCount = 0;

        // create a temporary row array containing all combinations of removing 1 value from the rowDataArray
        // Example: removing tempRow[0] or removing tempRow[1]
        for(int j = 0; j < columnCount; j++){
            if(i != j){
                tempRow[tempColumnCount++] = rowData[j];
            }
        }

        // check if the temporary row array will be true
        if(isSafe(tempColumnCount, tempRow)) return true;
    }
    return false;
}

int main(){
    FILE* inputFile = fopen("input.txt", "r");
    int safeReports = 0;
    int* rowData = (int*)malloc(sizeof(int) * MAX_ROW_LENGTH); 
    char line[MAX_ROW_LENGTH];

    // gets 1 entire row in the inputFile then puts it in the line char array
    while(fgets(line, sizeof(line), inputFile)){ 
        //printf("Line: %s", line);
        int columnCount = 0;

        // slices the string line with the delimitter space or newline or both
        char* token = strtok(line, " \n");
        while(token != NULL){ // if token still has a value continue looping
            //printf("Token: %s\n", token); 
            rowData[columnCount++] = atoi(token); // convert the token to an int then add to row data
            token = strtok(NULL, " \n");
        }

        // check if it satisfies the first conditions
        if(isSafe(columnCount, rowData)) safeReports++;
        // else check if it satisfies the second condition
        else if(isSafeWhenRemovingOne(columnCount, rowData)) safeReports++;
        
    }
    fclose(inputFile);

    printf("Number of Safe Reports: %d\n", safeReports);


     
    return 0;
}