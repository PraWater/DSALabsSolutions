#include<stdio.h>

void swap(int arr[], int a, int b)
{
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

int main() {
    int arr[] = {0,1,1,0,1,1,0,0,0,1,1,1,0};
    int lo = 0, hi = 12;
	swap(arr, hi, 0);
	int i = lo;
	for (int j = lo; j < hi; ++j) {
		if (arr[j] == 0) {
			swap(arr, i, j);
			++i;
		}
	}
	swap(arr, hi, i);
    for(int i = 0; i < 13; ++i) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}