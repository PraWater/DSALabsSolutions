#include <stdio.h>

// Function to take input an array A and return an array B after performing counting sort on it with array C
char* counting_sort(char* A, char* B, char k, int n) 
{
    // Initialize array C with all 0s
    int C[k];
    for (int i = 0; i < k; i++) 
    {
        C[i] = 0;
    }

    // Count the number of times each element occurs in A and store it in C
    for (int j = 0; j < n; j++) 
    {
        C[(int) A[j]-97]++;
    }

    // Place the elements of A in B in the correct position
    for (int i = 1; i < k; i++) 
    {
        C[i] = C[i] + C[i - 1];
    }
    for (int j = n - 1; j >= 0; j--) 
    {
        B[C[A[j]] - 1] = A[j];
        C[A[j]]--;
    }
    return B;
}

// Driver code to test the above function
int main() 
{
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    char A[n];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) 
    {
        scanf("%c", &A[i]);
    }
    int k = A[0];
    for (int i = 1; i < n; i++) 
    {
        if (A[i] > k) 
        {
            k = A[i];
        }
    }
    k -= 97;
    char B[n];
    char* sorted_array = counting_sort(A, B, k + 1, n);
    printf("The sorted array is: ");
    for (int i = 0; i < n; i++) 
    {
        printf("%c ", sorted_array[i]);
    }
    printf("\n");
    return 0;
}
