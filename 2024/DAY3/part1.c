#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_LENGTH 100000

int mul(int x, int y){
    return x*y;
}

int main(){
    FILE* inputFile = fopen("input.txt", "r");
    char* inputString = (char*)malloc(sizeof(char) * MAX_CHAR_LENGTH);
    int sumOfMultiplications = 0;

    /*
    Read the file and get the string inside and add into the inputString array
    */
    fread(inputString, sizeof(char), MAX_CHAR_LENGTH, inputFile); 
    fclose(inputFile);

    // check one by one 
    for(int i = 0; i < strlen(inputString) - 5; i++){
        int x = 0, y = 0;
        if(strncmp(inputString + i, "mul(", 4) == 0){
            i += 4;
            for(i; inputString[i] >= '0' && inputString[i] <= '9'; i++){
                x *= 10; // shift digit to the left then insert on its right the next digit
                x += inputString[i] - '0'; //char to int
            }
            if(inputString[i] == ','){
                i++;
                for(i; inputString[i] >= '0' && inputString[i] <= '9'; i++){
                    y *= 10; // shift digit to the left then insert on its right the next digit
                    y += inputString[i] - '0';
                }
            }
        }
        if(inputString[i] != ')'){
            x = 0;
            y = 0;
        }
        sumOfMultiplications += mul(x, y);
    }

    printf("Total sum of valid multiplications: %d\n", sumOfMultiplications);
    free(inputString);
    return 0;
}