#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "task5.h"

typedef struct person
{
	int id;
	char *name;
	int age;
	int height;
	int weight;
} PERSON;

void mergeAux(PERSON L1[], int s1, int e1, PERSON L2[], int s2, int e2, PERSON L3[], int s3, int e3)
{
	int i, j, k;
	// Traverse both arrays
	i = s1;
	j = s2;
	k = s3;
	while (i <= e1 && j <= e2)
	{
		// Check if current element of first array is smaller
		// than current element of second array
		// If yes, store first array element and increment first
		// array index. Otherwise do same with second array
		if (L1[i].height < L2[j].height)
			L3[k++] = L1[i++];
		else
			L3[k++] = L2[j++];
	}
	// Store remaining elements of first array
	while (i <= e1)
		L3[k++] = L1[i++];
	// Store remaining elements of second array
	while (j <= e2)
		L3[k++] = L2[j++];
}

void merge(PERSON A[], int s, int mid, int e)
{
	PERSON *C = (PERSON *)malloc(sizeof(PERSON) * (e - s + 1));
	mergeAux(A, s, mid, A, mid + 1, e, C, 0, e - s);
	for (int i = 0; i < e - s + 1; i++)
	{
		A[s + i] = C[i];
	}
	free(C);
}

void mergeSort(PERSON A[], int st, int en)
{
	if (en - st < 1)
		return;
	int mid = (st + en) / 2;   // mid is the floor of (st+en)/2
	mergeSort(A, st, mid);	   // sort the first half
	mergeSort(A, mid + 1, en); // sort the second half
	merge(A, st, mid, en);	   // merge the two halves
}

// Merges contents of fp1 and fp2 in fp3
void externalMerge(FILE *fp1, int len1, FILE *fp2, int len2, FILE *fp3)
{
	PERSON x, y;
	char *line = malloc(50);
	fscanf(fp1, "%d,%[^,],%d,%d,%d\n", &x.id, line, &x.age, &x.height, &x.weight);
	x.name = line;
	line = malloc(50);
	fscanf(fp2, "%d,%[^,],%d,%d,%d\n", &y.id, line, &y.age, &y.height, &y.weight);
	y.name = line;
	while (len1 > 0 && len2 > 0)
	{
		if (x.height > y.height)
		{
			fprintf(fp3, "%d,%s,%d,%d,%d\n", y.id, y.name, y.age, y.height, y.weight);
			free(y.name);
			len2--;
			line = malloc(50);
			fscanf(fp2, "%d,%[^,],%d,%d,%d\n", &y.id, line, &y.age, &y.height, &y.weight);
			y.name = line;
		}
		else
		{
			fprintf(fp3, "%d,%s,%d,%d,%d\n", x.id, x.name, x.age, x.height, x.weight);
			free(x.name);
			len1--;
			line = malloc(50);
			fscanf(fp1, "%d,%[^,],%d,%d,%d\n", &x.id, line, &x.age, &x.height, &x.weight);
			x.name = line;
		}
	}
	while (len1 > 0)
	{
		fprintf(fp3, "%d,%s,%d,%d,%d\n", x.id, x.name, x.age, x.height, x.weight);
		free(x.name);
		len1--;
		line = malloc(50);
		fscanf(fp1, "%d,%[^,],%d,%d,%d\n", &x.id, line, &x.age, &x.height, &x.weight);
		x.name = line;
	}
	while (len2 > 0)
	{
		fprintf(fp3, "%d,%s,%d,%d,%d\n", y.id, y.name, y.age, y.height, y.weight);
		free(y.name);
		len2--;
		line = malloc(50);
		fscanf(fp2, "%d,%[^,],%d,%d,%d\n", &y.id, line, &y.age, &y.height, &y.weight);
		y.name = line;
	}
	fclose(fp1);
	fclose(fp2);
}

int main()
{
	FILE *fp = fopen("dat1000000.csv", "r");
	if (fp == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}
	int n = 100000;
	PERSON *a = (PERSON *)malloc(sizeof(PERSON) * n);
	char filename[] = {"sorted1.csv"};
	for (int t = 0; t < 10; ++t)
	{
		for (int i = 0; i < n; ++i)
		{
			char *line = malloc(50);
			fscanf(fp, "%d,%[^,],%d,%d,%d\n", &a[i].id, line, &a[i].age, &a[i].height, &a[i].weight);
			a[i].name = line;
		}
		mergeSort(a, 0, n - 1);
		filename[6] = (char)48 + t;
		FILE *fptr = fopen(filename, "w");
		for (int i = 0; i < n; ++i)
		{
			fprintf(fptr, "%d,%s,%d,%d,%d\n", a[i].id, a[i].name, a[i].age, a[i].height, a[i].weight);
		}
		fclose(fptr);
	}
	free(a);
	fclose(fp);
	for (int i = 0; i < 5; i++)
	{
		filename[6] = (char)48 + (2 * i);
		FILE *fp1 = fopen(filename, "r");
		filename[6] = (char)48 + (2 * i + 1);
		FILE *fp2 = fopen(filename, "r");
		filename[6] = (char)97 + i;
		FILE *fp3 = fopen(filename, "w");
		externalMerge(fp1, n, fp2, n, fp3);
		fclose(fp3);
	}
	for (int i = 0; i < 2; ++i)
	{
		filename[6] = (char)97 + (2 * i);
		FILE *fp1 = fopen(filename, "r");
		filename[6] = (char)97 + (2 * i + 1);
		FILE *fp2 = fopen(filename, "r");
		filename[6] = (char)102 + i;
		FILE *fp3 = fopen(filename, "w");
		externalMerge(fp1, 2 * n, fp2, 2 * n, fp3);
		fclose(fp3);
	}
	filename[6] = 'e';
	FILE *fp1 = fopen(filename, "r");
	filename[6] = 'f';
	FILE *fp2 = fopen(filename, "r");
	filename[6] = 'h';
	FILE *fp3 = fopen(filename, "w");
	externalMerge(fp1, 2 * n, fp2, 4 * n, fp3);
	fclose(fp3);
	filename[6] = 'g';
	fp1 = fopen(filename, "r");
	filename[6] = 'h';
	fp2 = fopen(filename, "r");
	fp3 = fopen("sorted.csv", "w");
	externalMerge(fp1, 4 * n, fp2, 6 * n, fp3);
	fclose(fp3);
	for (int i = 0; i < 10; ++i)
	{
		filename[6] = (char)48 + i;
		remove(filename);
	}
	for (int i = 0; i < 8; ++i)
	{
		filename[6] = (char)97 + i;
		remove(filename);
	}
	return 0;
}