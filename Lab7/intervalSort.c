#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node *next;
  struct node *prev;
};
typedef struct node node;
typedef node *NODE;

struct linked_list {
  int count;
  NODE head;
  // NODE tail; // Not required for stack. Required for Queue
};
typedef struct linked_list linked_list;
typedef linked_list *LIST;

LIST createNewList() {
  LIST list = (LIST)malloc(sizeof(linked_list));
  if (list != NULL) {
    list->count = 0;
  }
  return list;
}

NODE createNewNode(int data) {
  NODE n = (NODE)malloc(sizeof(node));
  if (n != NULL) {
    n->next = NULL;
    n->prev = NULL;
    n->data = data;
  }
  return n;
}

void insertFirst(NODE node, LIST list) {
  if (list->count == 0) {
    list->head = node;
    node->next = NULL;
    node->prev = NULL;
  } else {
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
  }
  ++(list->count);
}

void swap(NODE node1, NODE node2) {
  NODE temp;
  temp = node1->next;
  node1->next = node2->next;
  node2->next = temp;
  node1 = node1->next;
  node2 = node2->next;
  temp = node1->next;
  node1->next = node2->next;
  node2->next = temp;
}

// Uses selection sort to sort @{LIST *}list from the 2nd node onwards.
void sortList(LIST list) {
  if (list->count == 1)
    return;
  NODE curr = list->head, min, temp;
  for (int i = 0; i < list->count - 2; i++) {
    min = curr;
    temp = min->next;
    while (temp->next != NULL) {
      if (temp->next->data < min->next->data)
        min = temp;
      temp = temp->next;
    }
    swap(curr, min);
    curr = curr->next;
  }
}

void intervalSort(int arr[], int n) {
  int i, j;
  // Create n empty buckets
  LIST b[10];
  for (i = 0; i < 10; i++) {
    b[i] = createNewList();
  }
  // Put array elements in different buckets
  for (i = 0; i < n; i++) {
    insertFirst(createNewNode(arr[i]), b[arr[i] / 100]);
  }
  // Sort individual buckets
  for (i = 0; i < n; i++) {
    sortList(b[i]);
    //  sortList() function has to be implemented
  }
  // Concatenate all buckets (in sequence) into arr[]
  for (i = 0, j = 0; i < n; i++) {
    NODE temp = b[i]->head;
    while (temp != NULL) {
      arr[j++] = temp->data;
      temp = temp->next;
    }
  }
}

int main() {
  int arr[] = {125, 980, 200, 75, 883, 270, 180, 450, 420, 760};
  intervalSort(arr, 10);
  for (int i = 0; i < 10; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
