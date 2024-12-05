#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PAIRS 2000 // how many pairs of pages
#define MAX_UPDATE_LENGTH 50 // length of the update
#define MAX_UPDATES 1000 // how many updates
#define LENGTH_OF_INPUT 2000 // how many lines does input.txt have

typedef struct {
    int left;
    int right;
} Rule;

// Function to find the middle page of an update
int findMiddlePage(int* update, int size) {
    return update[size / 2];
}

bool isCorrectlyOrdered(int* update, int updateLength, Rule* rules, int numRules) {
    for(int i = 0; i < numRules; i++){
        int left = 0, right = 1;

        for(int j = 0; j < updateLength; j++){
            if(update[j] == rules[i].left) left = j;
            if(update[j] == rules[i].right) right = j;

        }
        if(left != 0 && right != 1 && left > right) 
            return false;
    }
    return true;
}

void sortByRules(int* update, int updateLength, Rule* rules, int numRules) {
    for (int i = 0; i < numRules; i++) {
        for (int j = 0; j < updateLength - 1; j++) {
            for (int k = j + 1; k < updateLength; k++) {
                for (int r = 0; r < numRules; r++) {
                    if (update[j] == rules[r].right && update[k] == rules[r].left) {
                        int temp = update[j];
                        update[j] = update[k];
                        update[k] = temp;
                    }
                }
            }
        }
    }
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");

    Rule* rules = (Rule*)malloc(sizeof(Rule) * MAX_PAIRS); // rule pair array
    int** updatesArray = (int**)malloc(sizeof(int*) * MAX_UPDATES); // array containing an array of update pages
    char* inputString = (char*)malloc(sizeof(char) * LENGTH_OF_INPUT); // input.txt into one big string
    int* updateLength = (int*)malloc(sizeof(int) * MAX_UPDATES); // array containing sizes of corresponding updates in the updatesArray
    int numRules = 0, numUpdates = 0; // how many updates and how many rule pairs
    int sumOfMiddlePages = 0;

    // Read from the input file
    while (fgets(inputString, LENGTH_OF_INPUT, inputFile)) {
        inputString[strcspn(inputString, "\n")] = 0;

        if (strchr(inputString, '|')) {
            sscanf(inputString, "%d|%d", &rules[numRules].left, &rules[numRules].right);
            numRules++;
        }
        else if (strchr(inputString, ',')) {
            // Process updates
            int count = 0;
            int* update = (int*)malloc(sizeof(int) * MAX_UPDATE_LENGTH);

            char* token = strtok(inputString, ",");
            while (token != NULL) {
                update[count++] = atoi(token);
                token = strtok(NULL, ",");
            }
            updatesArray[numUpdates] = update;
            updateLength[numUpdates] = count;
            numUpdates++;
        }
    }

    fclose(inputFile);

    for (int i = 0; i < numUpdates; i++) {
        if (!isCorrectlyOrdered(updatesArray[i], updateLength[i], rules, numRules)) {
            sortByRules(updatesArray[i], updateLength[i], rules, numRules);
            sumOfMiddlePages += findMiddlePage(updatesArray[i], updateLength[i]);
        }
    }

    
    printf("Sum of Middle Pages: %d\n", sumOfMiddlePages);
    return 0;
}
