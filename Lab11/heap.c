#include <stdio.h>
#include <stdlib.h>

struct heap {
  int *data;
  int size;
  int capacity;
  int depth;
};
typedef struct heap *Heap;

int powe(int a, int n) {
  int r = 1;

  while (n > 0) {
    if (n & 1)
      r *= a;
    a *= a;
    n >>= 1;
  }
  return r;
}

Heap heap_create() {
  Heap h = malloc(sizeof(struct heap));
  h->data = malloc(sizeof(int));
  h->size = 0;
  h->capacity = 1;
  h->depth = 0;
  return h;
}

void add_to_tree(Heap h, int x) {
  if (h->size == h->capacity) {
    h->capacity += powe(2, ++(h->depth));
    h->data = realloc(h->data, sizeof(int) * h->capacity);
  }
  h->data[(h->size)++] = x;
}

int parent(Heap h, int node) { return (node - 1) / 2; }

int left_child(Heap h, int node) { return node * 2 + 1; }

int right_child(Heap h, int node) { return (node + 1) * 2; }

void max_heapify(Heap h, int index) {
  int left = left_child(h, index);
  int right = right_child(h, index);
  int largest = index;
  if (left < h->size && h->data[left] > h->data[largest]) {
    largest = left;
  }
  if (right < h->size && h->data[right] > h->data[largest]) {
    largest = right;
  }
  if (largest != index) {
    int temp = h->data[index];
    h->data[index] = h->data[largest];
    h->data[largest] = temp;
    max_heapify(h, largest);
  }
}

void min_heapify(Heap h, int index) {
  int left = left_child(h, index);
  int right = right_child(h, index);
  int smallest = index;
  if (left < h->size && h->data[left] < h->data[smallest]) {
    smallest = left;
  }
  if (right < h->size && h->data[right] < h->data[smallest]) {
    smallest = right;
  }
  if (smallest != index) {
    int temp = h->data[index];
    h->data[index] = h->data[smallest];
    h->data[smallest] = temp;
    min_heapify(h, smallest);
  }
}

Heap build_max_heap(int *arr, int n) {
  int x = 0, y;
  for (int i = 0; 1; ++i) {
    y = powe(2, i);
    x += y;
    if (x > n) {
      x -= y;
      y = i - 1;
      break;
    }
  }
  int *ans = (int *)malloc(sizeof(int) * n);
  Heap h = malloc(sizeof(struct heap));
  h->data = ans;
  h->capacity = x;
  h->size = n;
  h->depth = y;
  for (int i = 0; i < n; ++i)
    ans[i] = arr[i];
  for (int i = n - 1; i >= 0; --i)
    max_heapify(h, i);
  return h;
}

int nodes_at_depth(Heap h, int d) {
  if (h->depth > d) {
    return powe(2, d);
  }
  return powe(2, d) - h->capacity + h->size;
}

void heap_sort(Heap h) {
  int *arr = h->data;
  int n = h->size;
  free(h);
  h = build_max_heap(arr, n);
  free(arr);
  for (int i = h->size - 1; i >= 1; i--) {
    int temp = h->data[0];
    h->data[0] = h->data[i];
    h->data[i] = temp;
    h->size = h->size - 1;
    max_heapify(h, 0);
  }
}

int main() {
  int *arr = (int *)malloc(sizeof(int) * 10);
  for (int i = 0; i < 10; ++i) {
    arr[i] = i;
  }
  Heap ans = build_max_heap(arr, 10);
  for (int i = 0; i < 10; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  for (int i = 0; i < 10; i++) {
    printf("%d ", ans->data[i]);
  }
  printf("\n");
  printf("no at height: %d\n", nodes_at_depth(ans, 1));
  free(arr);
  free(ans);
  return 0;
}
