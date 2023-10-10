/* ------------------------------------------------------------ */
/* 		This header file contains fuctions for project 1 		*/
/* ------------------------------------------------------------ */


#include <stdio.h>
#include <stdlib.h>


// Structure for element in array
struct Element {
	int p;
	int v;
};

// 1. MERGE SORT

// Merge function to combine arrays
void merge(struct Element L[], struct Element R[], int lenL, int lenR, struct Element merged[]) {
	int combLen = lenL + lenR;
	int i = 0, j = 0;
	for (int k = 0; k < combLen; k++) {
		if (j > (lenR-1) || (i <= (lenL-1) && (L[i].v <= R[j].v))) {
			merged[k] = L[i];
			i++;
		}
		else {
			merged[k] = R[j];
			j++;
		}
	}
}

// Merge Sort function to recursively divide array into 2 arrays with haft size
struct Element* mergeSort(struct Element array[], int len) {

	if (len == 1) {
		return array;
	}
	
	else {

		struct Element* L = (struct Element*) malloc((len/2)*sizeof(struct Element));
		struct Element* R = (struct Element*) malloc((len - len/2)*sizeof(struct Element));

		for (int i = 0; i < len/2; i++) {
			L[i] = array[i];
		}
		for (int i = 0; i < len-len/2; i++) {
			R[i] = array[len/2 + i];
		}
		

		struct Element* LS = mergeSort(L, len/2);
		struct Element* RS = mergeSort(R, len-len/2);
		struct Element* merged = (struct Element*) malloc(len * sizeof(struct Element));
		merge(LS, RS, len/2, len-len/2, merged);

		free(L);
		free(R);
		return merged;
	}
}

// 2. QUICK SORT

// Concatenate function to combine arrays
struct Element* concat(struct Element a[], int lenA, struct Element b[], int lenB, struct Element c[], int lenC) {
    int len = lenA + lenB + lenC;
    struct Element* conca = (struct Element*) malloc(len * sizeof(struct Element));
    int x = 0; int y = 0; int z = 0;
    for (int i = 0; i < len; i++) {
        if (x < lenA) {
            conca[i] = a[x];
            x++;
        }
        else if (y < lenB) {
            conca[i] = b[y];
            y++;
        }
		else if (z < lenC) {
			conca[i] = c[z];
			z++;
		}
    }
    return conca;

}
 // Quick sort function to secursively divide arrays into partitions
 struct Element* quickSort(struct Element array[], int len) {
    if (len <= 1) {
        return array;
    }
    else {
        int pivotIndex = len /2;
        int pivot = array[pivotIndex].v;
        //printf("Pivot: %d\n", pivot);
        struct Element* less = (struct Element*) malloc(len * sizeof(struct Element));
        struct Element* greater = (struct Element*) malloc(len * sizeof(struct Element));
        struct Element* equal = (struct Element*) malloc(len * sizeof(struct Element));
        int x = 0; int y = 0; int z = 0;

        for (int i = 0; i < len; i++) {
            if (array[i].v < pivot) {
                less[x] = array[i];
                x++;
            }
            else if (array[i].v > pivot) {
                greater[y] = array[i];
                y++;
            }
            else {
                equal[z] = array[i];
                z++;
            }
        }

        struct Element* sortedLeft = quickSort(less, x);
        struct Element* sortedRight = quickSort(greater, y);

        struct Element* result = concat(sortedLeft, x, equal, z, sortedRight, y);

		free(sortedLeft);
		free(sortedRight);

        return result;
    }
}

// 3. SELECTION SORT
struct Element* selectionSort(struct Element array[], int len) {
    // Copy array
    struct Element* sorted = (struct Element*) malloc(len * sizeof(struct Element));
    int minIdx; struct Element temp;
    for (int i = 0; i < len; i++) {
        sorted[i] = array[i];
    }
    // find min
    for (int i = 0; i < len; i++) {
        minIdx = i;
        for (int j = i+1; j < len; j++) {
            if (sorted[j].v < sorted[minIdx].v) {
                minIdx = j;
            }
        }
        // swap min to the front
        temp = sorted[minIdx];
        sorted[minIdx] = sorted[i];
        sorted[i] = temp;
    }
    return sorted;
}

// INVERSION COUNT ALGORITHMS

// 1. MERGE SORT INVERSION COUNT
void mrgInvCnt(struct Element L[], struct Element R[], int lenL, int lenR, struct Element merged[], int* invCount) {
	int combLen = lenL + lenR;
	int i = 0, j = 0;
	for (int k = 0; k < combLen; k++) {
		if (j > (lenR-1) || (i <= (lenL-1) && (L[i].v <= R[j].v))) {
			merged[k] = L[i];
			i++;
		}
		else {
			merged[k] = R[j];
			*invCount += lenL - i;
			j++;
		}
	}
}
struct Element* msInvCnt(struct Element array[], int len, int* invCount) {
	if (len == 1) {
		return array;
	}
	else {
		struct Element* L = (struct Element*) malloc((len/2)*sizeof(struct Element));
		struct Element* R = (struct Element*) malloc((len - len/2)*sizeof(struct Element));

		for (int i = 0; i < len/2; i++) {
			L[i] = array[i];
		}
		for (int i = 0; i < len-len/2; i++) {
			R[i] = array[len/2 + i];
		}
		

		struct Element* LS = msInvCnt(L, len/2, invCount);
		struct Element* RS = msInvCnt(R, len-len/2, invCount);
		struct Element* merged = (struct Element*) malloc(len * sizeof(struct Element));
		mrgInvCnt(LS, RS, len/2, len-len/2, merged, invCount);

		free(L);
		free(R);
		return merged;
	}
}

// QUICK SORT INVERSION COUNT
struct Element* qsInvCnt(struct Element array[], int len, int* invCount) {
    if (len <= 1) {
        return array;
    }
    else {
        int pivotIndex = 0;
        int pivot = array[pivotIndex].v;
        struct Element* less = (struct Element*) malloc(len * sizeof(struct Element));
        struct Element* greater = (struct Element*) malloc(len * sizeof(struct Element));
        struct Element* equal = (struct Element*) malloc(len * sizeof(struct Element));
        int x = 0; int y = 0; int z = 0;

        for (int i = 0; i < len; i++) {
            if (array[i].v < pivot) {
                less[x] = array[i];
                x++;
                *invCount += y + z;
            }
            else if (array[i].v > pivot) {
                greater[y] = array[i];
                y++;
            }
            else {
                equal[z] = array[i];
                z++;
                *invCount += y;
            }
        }

        struct Element* sortedLeft = qsInvCnt(less, x, invCount);
        struct Element* sortedRight = qsInvCnt(greater, y, invCount);

        struct Element* result = concat(sortedLeft, x, equal, z, sortedRight, y);
        free(sortedLeft);
        free(sortedRight);

        return result;
    }
}

// SELECTION SORT INVERSION COUNT
int ssInvCnt(struct Element array[], int len) {
    int i, j, invCount = 0;
    // find min
    for (i = 0; i < len-1; i++) {
        for (j = i+1; j < len; j++) {
            if (array[i].v > array[j].v) {
                invCount++;
            }
        }
    }
    return invCount;
}