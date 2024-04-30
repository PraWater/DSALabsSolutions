#include "intMergeAux.h"

void mergeAux(int L1[], int s1, int e1, int L2[], int s2, int e2, int L3[], int s3, int e3)
{
    int i, j, k;
    // Traverse both arrays
    i = s1;
    j = s2;
    k = s3;
    while (i <= e1 && j <= e2)
    {
        // Check if current element of first array is smaller
        // than current element of second array
        // If yes, store first array element and increment first
        // array index. Otherwise do same with second array
        if (L1[i] < L2[j])
            L3[k++] = L1[i++];
        else
            L3[k++] = L2[j++];
    }
    // Store remaining elements of first array
    while (i <= e1)
        L3[k++] = L1[i++];
    // Store remaining elements of second array
    while (j <= e2)
        L3[k++] = L2[j++];
}