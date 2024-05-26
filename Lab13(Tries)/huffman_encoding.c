#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
  char value;
  struct node *left;
  struct node *right;
};
typedef struct node Node;

Node *newNode(char value) {
  Node *node = malloc(sizeof(Node));
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

struct element {
  int freq;
  Node *n;
};
typedef struct element Element;

struct heap {
  Element *data;
  int size;
  int capacity;
  int depth;
};
typedef struct heap Heap;

Heap *heap_create() {
  Heap *h = malloc(sizeof(Heap));
  h->data = malloc(sizeof(int));
  h->size = 0;
  h->capacity = 1;
  h->depth = 0;
  return h;
}

void add_to_heap(Heap *h, Element x) {
  if (h->size == h->capacity) {
    h->capacity += pow(2, ++(h->depth));
    h->data = realloc(h->data, sizeof(Element) * h->capacity);
  }
  h->data[(h->size)++] = x;
}

int left_child(Heap *h, int node) { return node * 2 + 1; }

int right_child(Heap *h, int node) { return (node + 1) * 2; }

void min_heapify(Heap *h, int index) {
  int left = left_child(h, index);
  int right = right_child(h, index);
  int smallest = index;
  if (left < h->size && h->data[left].freq < h->data[smallest].freq) {
    smallest = left;
  }
  if (right < h->size && h->data[right].freq < h->data[smallest].freq) {
    smallest = right;
  }
  if (smallest != index) {
    Element temp = h->data[index];
    h->data[index] = h->data[smallest];
    h->data[smallest] = temp;
    min_heapify(h, smallest);
  }
}

Element get_min(Heap *h) {
  Element x = h->data[0];
  h->data[0] = h->data[--h->size];
  min_heapify(h, 0);
  return x;
}

Node *build_huffman_tree(FILE *fp) {
  Heap *h = heap_create();
  // arr stores frequency of all characters. 0-25 : A-Z, 26-51 : a-z, 52 : ' '
  int *arr = (int *)calloc(53, sizeof(int));

  // Reading through the entire file and counting frequency of all characters
  char ch;
  ch = fgetc(fp);
  while (ch != EOF) {
    if (ch == ' ')
      (arr[52])++;
    else if ((int)ch < 97)
      (arr[(int)ch - 65])++;
    else
      (arr[(int)ch - 71])++;

    ch = fgetc(fp);
  }

  for (int i = 0; i < 26; i++) {
    if (arr[i] > 0) {
      Node *n = newNode('A' + i);
      Element ele;
      ele.freq = arr[i];
      ele.n = n;
      add_to_heap(h, ele);
    }
  }
  for (int i = 0; i < 26; i++) {
    if (arr[i + 26] > 0) {
      Node *n = newNode('a' + i);
      Element ele;
      ele.freq = arr[i + 26];
      ele.n = n;
      add_to_heap(h, ele);
    }
  }
  if (arr[52] > 0) {
    Node *n = newNode(' ');
    Element ele;
    ele.freq = arr[52];
    ele.n = n;
    add_to_heap(h, ele);
  }

  // Making Min Heap
  for (int i = h->size - 1; i >= 0; i--) {
    min_heapify(h, i);
  }

  // Building Huffman Tree
  while (h->size > 1) {
    Element x = get_min(h);
    Element y = get_min(h);
    Node *n = newNode('*');
    n->left = x.n;
    n->right = y.n;
    Element z;
    z.n = n;
    z.freq = x.freq + y.freq;
    add_to_heap(h, z);
  }

  return h->data[0].n;
}

void printCodes(Node *root, int arr[], int top) {
  // Assign 0 to left edge and recur
  if (root->left) {

    arr[top] = 0;
    printCodes(root->left, arr, top + 1);
  }

  // Assign 1 to right edge and recur
  if (root->right) {

    arr[top] = 1;
    printCodes(root->right, arr, top + 1);
  }

  // If this is a leaf node, then
  // it contains one of the input
  // characters, print the character
  // and its code from arr[]
  if (root->value != '*') {

    printf("%c: ", root->value);
    for (int i = 0; i < top; ++i)
      printf("%d", arr[i]);
    printf("\n");
  }
}

void traverse_in_order(Node *node) {
  if (node == NULL) {
    printf("null ");
    return;
  }
  traverse_in_order(node->left);
  printf("%c ", node->value);
  traverse_in_order(node->right);
}

int main() {
  FILE *fp = fopen("test.txt", "r");
  if (!fp) {
    printf("Error opening file\n");
    exit(1);
  }
  Node *n = build_huffman_tree(fp);
  fclose(fp);
  int arr[100];
  printCodes(n, arr, 0);
  return 0;
}
