#include <stdio.h>

int powe(int n, int a) {
  int m = 1;
  while (a--)
    m *= n;
  return m;
}

void place_sort(int *arr, int place, int n) {
  int div = powe(10, place);
  for (int i = 1; i < n; ++i) {
    for (int j = i; j > 0; --j) {
      int x = arr[j];
      x /= powe(10, place);
      x %= 10;
      int y = arr[j - 1];
      y /= powe(10, place);
      y %= 10;
      if (x >= y)
        break;
      else {
        x = arr[j];
        arr[j] = arr[j - 1];
        arr[j - 1] = x;
      }
    }
  }
}

void radix_sort(int *arr, int k, int n) {
  for (int i = 0; i < k; ++i)
    place_sort(arr, i, n);
}

int main() {
  int arr[] = {210, 120, 310, 450, 500};
  radix_sort(arr, 3, 5);
  for (int i = 0; i < 5; ++i)
    printf("%d ", arr[i]);
  printf("\n");
  return 0;
}
