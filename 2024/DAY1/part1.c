#include <stdio.h>
#include <stdlib.h>


int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main(){
    FILE *input; // ptr to the input file
    int* leftList = NULL, *rightList = NULL;
    int index = 0, listSize = 100;
    long long totalDistance = 0;

    // assume list size = 100
    leftList = (int*)malloc(sizeof(int) * listSize);
    rightList = (int*)malloc(sizeof(int) * listSize);

    // open input file
    input = fopen("input.txt", "r");

    // The fscanf function returns an integer value representing 
    // the number of input items successfully matched and assigned.
     while (fscanf(input, "%d %d", &leftList[index], &rightList[index]) == 2) {
        index++;

        if(index >= listSize){
            listSize *= 2;
            leftList = (int*)realloc(leftList, sizeof(int) * listSize);
            rightList = (int*)realloc(rightList, sizeof(int) * listSize);
        }
    }

    fclose(input);

    // sort both list in ascending order
    qsort(leftList, index, sizeof(int), compare);
    qsort(rightList, index, sizeof(int), compare);

    // get the difference of the smallest in each of the lists to get the total distance
    for(int i = 0; i < index; i++){
        totalDistance += abs(leftList[i] - rightList[i]); 
    }
    printf("Total Distance: %lld\n", totalDistance);

    free(leftList);
    free(rightList);
    return 0;

}