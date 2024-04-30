#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

struct person
{
	int id;
	char *name;
	int age;
	int height;
	int weight;
};

typedef struct person PERSON;

void insertInOrder(PERSON v, PERSON A[], int last)
{
	int j = last - 1;
	while (j >= 0 && strcmp(v.name, A[j].name))
	{
		A[j + 1] = A[j];
		j--;
	}
	A[j + 1] = v;
}

void insertionSort(PERSON A[], int n)
{
	for (int j = 1; j < n; j++)
	{
		insertInOrder(A[j], A, j);
	}
}

int main(int argc, char *argv[])
{
	FILE *fp;
	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		printf("Error opening file");
		exit(1);
	}

	struct timeval t1, t2;
	double time_taken;
	int n = atoi(argv[2]);
	PERSON *arr = (PERSON *)malloc(n * sizeof(PERSON));

	for (int i = 0; i < n; ++i)
	{
		char *line = malloc(100);
		fscanf(fp, "%d,%[^,],%d,%d,%d\n", &arr[i].id, line, &arr[i].age, &arr[i].height, &arr[i].weight);
		arr[i].name = line;
	}

	gettimeofday(&t1, NULL);
	insertionSort(arr, n);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Total %f seconds to execute\n", time_taken);
	free(arr);
	fclose(fp);
	return 0;
}