#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void findTriplets(int arr[], int n)
{
    qsort(arr, n, sizeof(int), compare);

    for (int i = 0; i < n - 1; i++)
    {
        int left = i + 1;
        int right = n - 1;
        while (left < right)
        {
            if (arr[i] + arr[left] + arr[right] == 0)
            {
                printf("%d %d %d\n", arr[i], arr[left], arr[right]);
                left++;
                right--;
            }
            else if (arr[i] + arr[left] + arr[right] < 0)
                left++;
            else
                right--;
        }
    }
}

int main()
{
    int arr[] = {0, -1, 2, -3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    findTriplets(arr, n);
    return 0;
}