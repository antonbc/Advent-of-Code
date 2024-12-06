#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define STRING_COUNT 10000
#define MAX_STRING_LENGTH 100000

typedef struct {
    int guardIndex;
    int guardArray;
} Guard;

// Function to find the initial position of the guard
void findInitialPositionOfGuard(char** inputStringArray, int inputStringArraySize, int inputStringSize, Guard* guard) {
    for (int i = 0; i < inputStringArraySize; i++) {
        for (int j = 0; j < inputStringSize; j++) {
            if (inputStringArray[i][j] == '^' || inputStringArray[i][j] == 'v' || 
                inputStringArray[i][j] == '<' || inputStringArray[i][j] == '>') {
                guard->guardIndex = j;
                guard->guardArray = i;
                return;
            }
        }
    }
    guard->guardIndex = -1; 
    guard->guardArray = -1;
}

// Function to find the patrol path and count distinct visited positions
int findPatrolPath(char** inputStringArray, int inputStringArraySize, int inputStringSize, Guard* guard) {
    if (guard->guardIndex == -1 || guard->guardArray == -1) {
        printf("Error: Guard not found in the grid.\n");
        return 0;
    }

    // Directions: Up, Right, Down, Left
    int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int direction = 0;
    char initialChar = inputStringArray[guard->guardArray][guard->guardIndex];

    // Determine initial direction based on starting character
    switch (initialChar) {
        case '^': direction = 0; break;
        case '>': direction = 1; break;
        case 'v': direction = 2; break;
        case '<': direction = 3; break;
        default: break;
    }

    int distinctCount = 1;
    int guardCurrentIndex = guard->guardIndex;
    int guardCurrentArray = guard->guardArray;
    inputStringArray[guardCurrentArray][guardCurrentIndex] = 'X'; // Mark as visited

    while (true) {
        int nextArray = guardCurrentArray + directions[direction][0];
        int nextIndex = guardCurrentIndex + directions[direction][1];

        // Check if out of bounds
        if (nextArray < 0 || nextArray >= inputStringArraySize ||
            nextIndex < 0 || nextIndex >= inputStringSize) {
            break;
        }

        // Check for wall
        if (inputStringArray[nextArray][nextIndex] == '#') {
            direction = (direction + 1) % 4; // Turn clockwise
            continue;
        }

        // Move to the next cell
        guardCurrentArray = nextArray;
        guardCurrentIndex = nextIndex;

        // Mark the cell if not already visited
        if (inputStringArray[guardCurrentArray][guardCurrentIndex] != 'X') {
            inputStringArray[guardCurrentArray][guardCurrentIndex] = 'X';
            distinctCount++;
        }

        // Stop if returning to start
        if (guardCurrentArray == guard->guardArray && 
            guardCurrentIndex == guard->guardIndex && direction == 0) {
            break;
        }
    }

    return distinctCount;
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    if (!inputFile) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    char** inputStringArray = (char**)malloc(sizeof(char*) * STRING_COUNT);
    char line[MAX_STRING_LENGTH];
    int inputStringSize = 0;

    while (fgets(line, sizeof(line), inputFile)) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        inputStringArray[inputStringSize] = strdup(line);
        inputStringSize++;
    }
    fclose(inputFile);

    Guard guard = {0, 0};
    findInitialPositionOfGuard(inputStringArray, inputStringSize, (int)strlen(inputStringArray[0]), &guard);

    if (guard.guardIndex == -1) {
        printf("Error: Guard not found in the grid.\n");
        return EXIT_FAILURE;
    }

    printf("Guard found at: Array Index = %d, String Index = %d\n", guard.guardArray, guard.guardIndex);

    int visitedPositionsCount = findPatrolPath(inputStringArray, inputStringSize, (int)strlen(inputStringArray[0]), &guard);
    printf("Distinct positions visited: %d\n", visitedPositionsCount);


    return 0;
}
