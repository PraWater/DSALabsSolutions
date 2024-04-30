#include "intMerge.h"
#include "intMergeAux.h"

void merge(int A[], int s, int mid, int e)
{
    int *C = (int *)malloc(sizeof(int) * (e - s + 1));
    mergeAux(A, s, mid, A, mid + 1, e, C, 0, e - s);
    for (int i = 0; i < e - s + 1; i++)
    {
        A[s + i] = C[i];
    }
    free(C);
}