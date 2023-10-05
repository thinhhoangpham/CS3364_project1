#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "project1.h"

#define SOURCES 5
#define SOURCE_NUM 10000

struct Element sources[SOURCES][SOURCE_NUM];
struct Element sums[SOURCE_NUM];
int invCount = 0;

int main() {
    
	// Read sources
    FILE *myFile;

	// Loop to load 5 source files
    for (int i = 0; i < SOURCES; i++) {
		// build file name string
    	char name[60] = "";						// String for file name
		char sNum[10] = "";						// string for nsource number
        strcat(name, "source");					// start name string with "source"
		sprintf(sNum, "%d", i+1);				//  put value into source number string
		strcat(name, sNum);						// add source number to name string
        strcat(name, ".txt");					// add ".txt" to name string

        //read file
		myFile = fopen(name, "r");				// open file with file name matches name string
		for (int j = 0; j < SOURCE_NUM; j++) {		// loop to read file line by line to array
			fscanf(myFile, "%d", &sources[i][j].v);
			sources[i][j].p = j;
		}
    }

	// print first 20 entries of sources
	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < SOURCES; i++) {
			printf("%d \t", sources[i][j].p);
			printf("%d \t", sources[i][j].v);
		}
		printf("\n");
	}

    // Step 1: Sum of sources
    for (int i = 0; i < SOURCE_NUM; i++) {
        struct Element sum;
        sum.p = 0;
        sum.v = 0;
        for (int j = 0; j < SOURCES; j++) {
            sum.p = i;
            sum.v += sources[j][i].v;
        }
        sums[i] = sum;
    }
    // print out first 20 entries of sums
    for (int i = 0; i < 20; i++) {
        printf("%d, %d\n", sums[i].p, sums[i].v);
    }

    printf("----------\n");

    // Step 2: sort sums
    struct Element* sortedSums = mergeSort(sums, SOURCE_NUM);
    // print out first 20 entries of sorted sums
    for (int i = 0; i < 20; i++) {
        printf("%d, %d\n", sortedSums[i].p, sortedSums[i].v);
    }

	// Step 3: Adjustment
    struct Element adj_sources[SOURCES][SOURCE_NUM];
    for (int i = 0; i < SOURCES; i++) {
        for (int j = 0; j < SOURCE_NUM; j++) {
            adj_sources[i][j] = sources[i][sortedSums[j].p];
        }
    }
    // print first 20 entries of adjusted sources
	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < SOURCES; i++) {
			printf("%d \t", adj_sources[i][j].p);
			printf("%d \t", adj_sources[i][j].v);
		}
		printf("\n");
	}

}
