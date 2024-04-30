#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "intMerge.h"

// Precondition: A is an array indexed from st to en
void mergeSort(int A[], int st, int en)
{
    if (en - st < 1)
        return;
    int mid = (st + en) / 2;   // mid is the floor of (st+en)/2
    mergeSort(A, st, mid);     // sort the first half
    mergeSort(A, mid + 1, en); // sort the second half
    merge(A, st, mid, en);     // merge the two halves
}
// Postcondition: forall j: st<=j<en-1 --> A[j]<=A[j+1]

int main()
{
    FILE *fp = fopen("marks.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    int *a = (int *)malloc(sizeof(int) * 1000);
    int i;
    for (i = 0; i < 1000; ++i)
        fscanf(fp, "%d\n", a + i);
    struct timeval t1, t2;
    double time_taken;
    gettimeofday(&t1, NULL);
    mergeSort(a, 0, i);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    printf("Total %f seconds to execute\n", time_taken);
    free(a);
    fclose(fp);
}