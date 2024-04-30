#include <stdio.h>

int powe(int n, int a) {
  int m = 1;
  while (a--)
    m *= n;
  return m;
}

// Function to take input an array A and return an array B after performing
// counting sort on it with array C
int *counting_sort(int *A, int *B, int k, int n) {
  // Initialize array C with all 0s
  int C[k];
  for (int i = 0; i < k; i++) {
    C[i] = 0;
  }

  // Count the number of times each element occurs in A and store it in C
  for (int j = 0; j < n; j++) {
    C[A[j]]++;
  }

  // Place the elements of A in B in the correct position
  for (int i = 1; i < k; i++) {
    C[i] = C[i] + C[i - 1];
  }
  for (int j = n - 1; j >= 0; j--) {
    B[C[A[j]] - 1] = A[j];
    C[A[j]]--;
  }
  return B;
}

// Driver code to test the above function
int main() {
  int n;
  printf("Enter the number of elements in the array: ");
  scanf("%d", &n);
  int A[n];
  printf("Enter the elements of the array: ");
  for (int i = 0; i < n; i++) {
    scanf("%d", &A[i]);
  }
  int k = A[0];
  for (int i = 1; i < n; i++) {
    if (A[i] > k) {
      k = A[i];
    }
  }
  int B[n];
  int *sorted_array = counting_sort(A, B, n, 2);
  printf("The sorted array is: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", sorted_array[i]);
  }
  printf("\n");
  return 0;
}
