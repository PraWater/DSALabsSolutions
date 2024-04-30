#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int part(int Ls[], int lo, int hi, int pInd);

int min(int a, int b)
{
    return (a>b) ? b : a;
}

void swap(int arr[], int a, int b)
{
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

int pivotSelect(int L[], int n, int k)
{
    if (k == 0)
        return L[0];
    if (n <= 5)
    {
        for (int i = 1; i < n; i++)
            for (int j = i - 1; j >= 0; j--)
                if (L[j] > L[j + 1])
                    swap(L, j, j + 1);
                else
                    break;
        return L[k - 1];
    }
    // partition L into subsets of five elements each
    // (there will be n/5 subsets total).
    int numGroups;
    if (n % 5 == 0)
        numGroups = n / 5;
    else
        numGroups = n / 5 + 1;
    int medians[numGroups];
    for (int i = 0; i < numGroups; i++)
    {
        medians[i] = pivotSelect(L + i * 5, min(5, n - i * 5), min(5, n - i * 5) / 2);
    }
    int M = pivotSelect(medians, numGroups, (numGroups + 1) / 2);
    // Partition array into two halves, L1, {M} and L2, such that
    // L1 contains elements <= M, {M} contains one instance of M and L2 contains all elements > M
    int mInd;
    for (int i = 0; i < n; i++)
    {
        if (L[i] == M)
        {
            mInd = i;
            break;
        }
    }
    int pInd = part(L, 0, n - 1, mInd);
    if (k <= pInd)
        return pivotSelect(L, pInd, k);
    else if (k > pInd + 1)
        return pivotSelect(L + pInd + 1, n - pInd - 1, k - pInd - 1);
    else
        return L[pInd];
}

int randomPivot(int lo, int hi)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec * 1000000 + tv.tv_sec);
    return (rand() % (hi - lo)) + lo;
}

int part(int Ls[], int lo, int hi, int pInd)
{
    swap(Ls, pInd, lo);
    int pivPos, lt, rt, pv;
    lt = lo + 1;
    rt = hi;
    pv = Ls[lo];
    while (lt < rt)
    {
        for (; lt <= hi && Ls[lt] <= pv; lt++)
            ;
        // Ls[j]<=pv for j in lo..lt-1
        for (; Ls[rt] > pv; rt--)
            ;
        // Ls[j]>pv for j in rt+1..hi
        if (lt < rt)
        {
            swap(Ls, lt, rt);
            lt++;
            rt--;
        }
    }
    if (Ls[lt] < pv && lt <= hi)
        pivPos = lt;
    else
        pivPos = lt - 1;
    swap(Ls, lo, pivPos);
    // Postcond.: (Ls[j]<=pv for j in lo..pivPos-1) and (Ls[j]>pv for j in pivPos+1..hi)
    return pivPos;
}

void qs(int Ls[], int lo, int hi)
{
    if (lo < hi)
    {
        int p = randomPivot(lo, hi);
        // Ls[p] is the pivot
        p = part(Ls, lo, hi, p); // Ls[p] is the pivot
        /*
        (Ls[j]<=Ls[p] for j in lo..pPos-1) and
        (Ls[j]>Ls[p] for j in pPos+1..hi)
        */
        qs(Ls, lo, p - 1);
        qs(Ls, p + 1, hi);
    }
}

int main()
{
    FILE *fp = fopen("int0.txt", "r");
    if (!fp)
    {
        printf("Error opening file\n");
        exit(1);
    }
    double time_taken;
    struct timeval t1, t2;
    int *arr = (int *)malloc(1000 * sizeof(int));
    int i = 0;
    while (fscanf(fp, "%d\n", arr + i) != EOF)
        ++i;
    gettimeofday(&t1, NULL);
    qs(arr, 0, 999);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    printf("Total %f seconds to execute\n", time_taken);
    free(arr);
    fclose(fp);
    return 0;
}