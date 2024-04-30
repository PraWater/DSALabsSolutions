#include<stdio.h>
#include<sys/time.h>

int fibb_recursive(int n) {
	if (n == 1 || n == 2) return 1;
	return fibb_recursive(n-1) + fibb_recursive(n-2);
}

int fibb_memoization(int n, int arr[]) {
	if (n == 0 || n == 1) return 1;
	if (arr[n] != 0) return arr[n];
	else arr[n] = fibb_recursive(n-1) + fibb_recursive(n-2);
	return arr[n];
}

int fibb_iterative(int n) {
	int a = 1, b = 1, c = 1;
	for (int i = 1; i < n;++i) {
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}

int main() {
	struct timeval t1, t2;
	double time_taken;
	gettimeofday(&t1, NULL);
	fibb_recursive(50);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Recursive took %f seconds to execute\n", time_taken);
	int arr[50] = {0};
	gettimeofday(&t1, NULL);
	fibb_memoization(50, arr);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Recursive with memoization took %f seconds to execute\n", time_taken);
	gettimeofday(&t1, NULL);
	fibb_iterative(50);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Iterative took %f seconds to execute\n", time_taken);
}