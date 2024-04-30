#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>

typedef struct student* STUD;
struct student{
	char ID[13];
	float CGPA;
};

typedef struct node* NODE;
struct node{
	STUD ele;
	NODE next;
};

typedef struct linked_list* LIST;
struct linked_list{
	int count;
	NODE head;
};

LIST createNewList() {
	LIST myList;
	myList = (LIST) malloc(sizeof(struct linked_list));
	myList->count=0;
	myList->head=NULL;
	return myList;
}

NODE createNewNode(STUD s1) {
	NODE myNode;
	myNode = (NODE) malloc(sizeof(struct node));
	myNode->ele=s1;
	myNode->next=NULL;
	return myNode;
}

int main() {
	FILE *fp = fopen("data.txt", "r");
	if(fp == NULL) {
		printf("Error opening file!");
		exit(1);
	}
	struct timeval t1, t2;
	double time_taken;

	// Populating data in array
	gettimeofday(&t1, NULL);
	STUD arr = malloc(10000 * (sizeof(float) + 16*sizeof(char)));
	for (int i = 0; i < 10000; ++i) {
		fscanf(fp, "%[^,],%f\n", arr[i].ID, &(arr[i].CGPA));
	}
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Populating in array took %f seconds to execute\n", time_taken);
	fclose(fp);	

	// Populating in LinkedList
	fp = fopen("data.txt", "r");
	gettimeofday(&t1, NULL);
	LIST l1 = createNewList();
	STUD s1;
	fscanf(fp, "%[^,],%f\n", s1->ID, &(s1->CGPA));
	NODE n1 = createNewNode(s1);
	l1->head = n1;
	for (int i = 1; i < 10000; ++i) {
		fscanf(fp, "%[^,],%f\n", s1->ID, &(s1->CGPA));
		NODE n2 = createNewNode(s1);
		n1->next = n2;
		n1 = n2;
	}
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Populating in Linked List took %f seconds to execute\n", time_taken);
	fclose(fp);

	int x;
	printf("Enter location to get data: ");
	scanf("%d", &x);
	// Retrieving data from array
	gettimeofday(&t1, NULL);
	s1 = &arr[x];
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Retrieving data from array took %f seconds to execute\n", time_taken);

	// Retrieving data from linked list
	gettimeofday(&t1, NULL);
	n1 = l1->head;
	for (int i = 0; i < x; ++i) {
		n1 = n1->next;
	}
	s1 = n1->ele;
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Retrieving data from linked list took %f seconds to execute\n", time_taken);

	// Deleting data from array
	gettimeofday(&t1, NULL);
	free(arr);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Deleting from array took %f seconds to execute\n", time_taken);

	// Deleting data from linked list
	gettimeofday(&t1, NULL);
	n1 = l1->head;
	while (n1->next != NULL) {
		NODE n2 = n1->next;
		free(n1);
		n1 = n2;
	}
	free(n1);
	free(l1);
	gettimeofday(&t2, NULL);
	time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
	time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	printf("Deleting linked list took %f seconds to execute\n", time_taken);
}