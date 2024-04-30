#include <stdio.h>
#include <stdlib.h>
#include "intMerge.h"

void mergeSort(int A[], int st, int en)
{
    if (en - st < 1)
        return;
    int mid = (st + en) / 2;   // mid is the floor of (st+en)/2
    mergeSort(A, st, mid);     // sort the first half
    mergeSort(A, mid + 1, en); // sort the second half
    merge(A, st, mid, en);     // merge the two halves
}

int main()
{
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
        scanf("%d", a + i);
    mergeSort(a, 0, n - 1);
    for (int i = 0; i < n; ++i)
    {
        while (i < n - 1 && a[i] == a[i + 1])
            ++i;
        if (n - i - 1 == a[i])
            printf("%d\n", a[i]);
    }
    free(a);
    return 0;
}