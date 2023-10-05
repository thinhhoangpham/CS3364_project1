// This is code to test and debug function before implementing to main project code

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "project1.h"

#define SOURCES 5
#define SOURCE_NUM 10

int sources[SOURCES][SOURCE_NUM];
struct Element sums[SOURCE_NUM];


int main() {

    struct Element arr1[10];
    arr1[0].p = 0; arr1[0].v = 1;
    arr1[1].p = 1; arr1[1].v = 3;
    arr1[2].p = 2; arr1[2].v = 5;
    arr1[3].p = 3; arr1[3].v = 2;
    arr1[4].p = 4; arr1[4].v = 7;
    arr1[5].p = 5; arr1[5].v = 9;
    arr1[6].p = 6; arr1[6].v = 8;
    arr1[7].p = 7; arr1[7].v = 4;
    arr1[8].p = 8; arr1[8].v = 0;
    arr1[9].p = 9; arr1[9].v = 6;

    struct Element arr2[10];
    arr2[0].p = 0; arr2[0].v = 5;
    arr2[1].p = 1; arr2[1].v = 3;
    arr2[2].p = 2; arr2[2].v = 5;
    arr2[3].p = 3; arr2[3].v = 6;
    arr2[4].p = 4; arr2[4].v = 7;
    arr2[5].p = 5; arr2[5].v = 9;
    arr2[6].p = 6; arr2[6].v = 8;
    arr2[7].p = 7; arr2[7].v = 1;
    arr2[8].p = 8; arr2[8].v = 4;
    arr2[9].p = 9; arr2[9].v = 2;

    struct Element arr3[10];
    arr3[0].p = 0; arr3[0].v = 1;
    arr3[1].p = 1; arr3[1].v = 2;
    arr3[2].p = 2; arr3[2].v = 3;
    arr3[3].p = 3; arr3[3].v = 4;
    arr3[4].p = 4; arr3[4].v = 5;
    arr3[5].p = 5; arr3[5].v = 7;
    arr3[6].p = 6; arr3[6].v = 8;
    arr3[7].p = 7; arr3[7].v = 6;
    arr3[8].p = 8; arr3[8].v = 0;
    arr3[9].p = 9; arr3[9].v = 9;

    struct Element sums[10];
    for (int i = 0; i < 10; i++) {
        sums[i].p = i;
        sums[i].v = arr1[i].v + arr2[i].v + arr3[i].v;
    }

    for (int i = 0; i < 10; i++) {
        printf("%d \t%d\n", sums[i].p, sums[i].v);
    }

    printf("-----------\n");

    // Sort sums
    struct Element* sortedSums = mergeSort(sums, 10);
    // print out sorted sums
    for (int i = 0; i < 10; i++) {
        printf("%d \t%d\n", sortedSums[i].p, sortedSums[i].v);
    }
    printf("-----------\n");

    // Adjustment
    struct Element s_arr1[10], s_arr2[10], s_arr3[10];
    for (int i = 0; i < 10; i++) {
        s_arr1[i] = arr1[sortedSums[i].p];
        s_arr2[i] = arr2[sortedSums[i].p];
        s_arr3[i] = arr3[sortedSums[i].p];
    }
    // print out adjusted array1
    for (int i = 0; i < 10; i++) {
        printf("%d \t%d\n", s_arr1[i].p, s_arr1[i].v);
    }
    printf("-----------\n");

    // inversion count for arr1
    int invCount = 0;
    struct Element* c_arr1 = qsInvCnt(s_arr1, 10, &invCount);
    for (int i = 0; i < 10; i++) {
        printf("%d \t%d\n", c_arr1[i].p, c_arr1[i].v);
    }
    printf("-----------\n");
    printf("inversions Array1: %d\n", invCount);

    return 0;
    
}

