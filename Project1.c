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
    printf("\n");

	// print first 20 entries of sources
    // int i, j = 0;
    // printf("First 20 entries of sources:\n");
    // printf("INDEX \tVALUE\tINDEX \tVALUE\tINDEX \tVALUE\tINDEX \tVALUE\tINDEX \tVALUE\n");
	// for (j = 0; j < 20; j++) {
	// 	for (i = 0; i < SOURCES; i++) {
	// 		printf("%d \t", sources[i][j].p);
	// 		printf("%d \t", sources[i][j].v);
	// 	}
	// 	printf("\n");
	// }
    // printf("----------\n");

    // Step 1: Sum of sources
    for (int i = 0; i < SOURCE_NUM; i++) {      // for each entry of sources
        struct Element sum;
        sum.p = 0;
        sum.v = 0;
        for (int j = 0; j < SOURCES; j++) {
            sum.p = i;
            sum.v += sources[j][i].v;           // sum up the value of all sources
        }
        sums[i] = sum;                          // add the sum to sums list
    }
    // print out first 20 entries of sums
    // printf("Sums of sources (first 20 entries):\n");
    // printf("INDEX \tVALUE\n");
    // for (int i = 0; i < 20; i++) {
    //     printf("%d \t%d\n", sums[i].p, sums[i].v);
    // }
    // printf("----------\n");

    // Step 2: sort sums
    struct Element* sortedSums = mergeSort(sums, SOURCE_NUM);   //sort the list of sums using merge sort
    // print out first 20 entries of sorted sums
    // printf("Sorted sums (first 20 entries):\n");
    // printf("INDEX \tVALUE\n");
    // for (int i = 0; i < 20; i++) {
    //     printf("%d \t%d\n", sortedSums[i].p, sortedSums[i].v);
    // }

	// Step 3: Adjustment
    // for each source, rearange list order to match index order of sorted sums
    struct Element adj_sources[SOURCES][SOURCE_NUM];
    for (int i = 0; i < SOURCES; i++) {
        for (int j = 0; j < SOURCE_NUM; j++) {
            adj_sources[i][j] = sources[i][sortedSums[j].p];
        }
    }
    // print first 20 entries of adjusted sources
    // printf("Adjusted sorces (first 20 entries):");
    // printf("INDEX \tVALUE\tINDEX \tVALUE\tINDEX \tVALUE\tINDEX \tVALUE\tINDEX \tVALUE\n");
	// for (int j = 0; j < 20; j++) {
	// 	for (int i = 0; i < SOURCES; i++) {
	// 		printf("%d \t", adj_sources[i][j].p);
	// 		printf("%d \t", adj_sources[i][j].v);
	// 	}
	// 	printf("\n");
	// }

    // Step 4: Inversion counts
    int ic_ms[SOURCES], ic_qs[SOURCES], ic_ss[SOURCES]; // initialize inversions count variables for each method
    struct Element* ic_sort;
    for (int i = 0; i < SOURCES; i++) {
        ic_sort = msInvCnt(adj_sources[i], SOURCE_NUM, &ic_ms[i]);
        ic_sort = qsInvCnt(adj_sources[i], SOURCE_NUM, &ic_qs[i]);
        ic_ss[i] = ssInvCnt(adj_sources[i], SOURCE_NUM);
    }
    // Print out inversions counts
    printf("Inversions count Merge Sort:\n");
    printf("Source 1\tSource 2\tSource 3\tSource 4\tSource 5\n");
    for (int i = 0; i < SOURCES; i++) {
        printf("%d \t", ic_ms[i]);
    }
    printf("\n------------------------------------------------------------------------\n");
    printf("Inversions count Quick Sort:\n");
    printf("Source 1\tSource 2\tSource 3\tSource 4\tSource 5\n");
    for (int i = 0; i < SOURCES; i++) {
        printf("%d \t", ic_ms[i]);
    }
    printf("\n------------------------------------------------------------------------\n");
    printf("Inversions count Selection Sort:\n");
    printf("Source 1\tSource 2\tSource 3\tSource 4\tSource 5\n");
    for (int i = 0; i < SOURCES; i++) {
        printf("%d \t", ic_ms[i]);
    }
    printf("\n");

    // Find best and worse sources by sorting the list
    // The best source is on top and the worst source is bottom
    struct Element source_rank[SOURCES];
    for (int i = 0; i < SOURCES; i++) {
        source_rank[i].p = i;
        source_rank[i].v = ic_qs[i];
    }
    struct Element* sorted_ranks = quickSort(source_rank, SOURCES);

    printf("Source %d is most reliable with %d inversions.\n", sorted_ranks[0].p+1, sorted_ranks[0].v);
    printf("Source %d is least reliable with %d inversions.\n", sorted_ranks[SOURCES-1].p+1, sorted_ranks[SOURCES-1].v);

}
