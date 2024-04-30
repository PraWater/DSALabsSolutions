#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


typedef struct node * NODE;
struct node{
    int ele;
    NODE next;
};


typedef struct linked_list * LIST;
struct linked_list{
    int count;
    NODE head;
};


LIST createNewList()
{
    LIST myList;
    myList = (LIST) malloc(sizeof(struct linked_list));
    myList->count=0;
    myList->head=NULL;
    return myList;
}


NODE createNewNode(int value)
{
    NODE myNode;
    myNode = (NODE) malloc(sizeof(struct node));
    myNode->ele=value;
    myNode->next=NULL;
    return myNode;
}

// Recursive function to compute sum of integers in a linked list
int llSumNTR(NODE head)
{
    if (head == NULL)
        return 0;
    return head->ele + llSumNTR(head->next); // Pay close attention here
}

// This is just a wrapper function to take LIST as input, but run the recursive sum function on its NODEs starting from the head
int llSumNTRWrapper(LIST list)
{
    return llSumNTR(list->head);
}

// Recursive function to compute sum of integers in a linked list
int llSumTR(NODE head, int acc)
{
    if (head == NULL)
        return acc;
    return llSumTR(head->next, acc+head->ele); // Pay close attention here
}

// This is just a wrapper function to take LIST as input, but run the recursive sum function on its NODEs starting from the head
int llSumTRWrapper(LIST list)
{
    return llSumTR(list->head, 0);
}

int llSumIter (LIST list) {
    NODE n = list->head;
    int acc = 0;
    while (n != NULL) {
        acc += n->ele;
        n = n->next;
    }
    return acc;
}

// Driver code
int main()
{
    // Reads the file numbers1000.txt and creates a linked list with those integers
    FILE *fp;
    fp = fopen("numbers1000.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    int num;
    LIST myList = createNewList();
    while (fscanf(fp, "%d", &num) != EOF)
    {
        NODE myNode = createNewNode(num);
        myNode->next = myList->head;
        myList->head = myNode;
        myList->count++;
    }
    fclose(fp);

    // Perform some operations on the linked list
    // ...

    // Example operation: Print the elements of the linked list
    struct timeval t1, t2;
    double time_taken;
    int ans;
    gettimeofday(&t1, NULL);
    ans = llSumNTRWrapper(myList);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    printf("NTR took %f seconds to execute\nOutput: %d\n", time_taken, ans);
    gettimeofday(&t1, NULL);
    ans = llSumTRWrapper(myList);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    printf("TR took %f seconds to execute\nOutput: %d\n", time_taken, ans);
    gettimeofday(&t1, NULL);
    ans = llSumIter(myList);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    printf("Iterative took %f seconds to execute\nOutput : %d\n", time_taken, ans);
    return 0;
}