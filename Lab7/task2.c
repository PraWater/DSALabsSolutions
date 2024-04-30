#include <stdio.h>

int main() 
{
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int A[n];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &A[i]);
    }
    int k = A[0];
    for (int i = 1; i < n; i++) 
    {
        if (A[i] > k) 
        {
            k = A[i];
        }
    }
    ++k;
    // Initialize array C with all 0s
    int C[k];
    for (int i = 0; i < k; i++) 
    {
        C[i] = 0;
    }

    // Count the number of times each element occurs in A and store it in C
    for (int j = 0; j < n; j++) 
    {
        C[A[j]]++;
    }
    // Place the elements of A in B in the correct position
    for (int i = 1; i < k; i++) 
    {
        C[i] = C[i] + C[i - 1];
    }
    for (int i = 0; i < n; ++i) printf("%d ", C[i]);
    printf("\n");
    printf("Enter query: \n");
    int q, a, b;
    scanf("%d %d %d", &q, &a, &b);
    if (C[q] < b && C[q] > a) printf("True\n");
    else printf("False\n");
    return 0;
}
