#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct person {
  int id;
  char *name;
  int age;
  int height;
  int weight;
};
typedef struct person PERSON;

void swap(PERSON arr[], int a, int b) {
  PERSON temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

int part(PERSON Ls[], int lo, int hi, int pInd) {
  swap(Ls, pInd, lo);
  int pivPos, lt, rt, pv;
  lt = lo + 1;
  rt = hi;
  pv = Ls[lo].height;
  while (lt < rt) {
    while (lt <= hi && Ls[lt].height <= pv)
      lt++;
    // Ls[j]<=pv for j in lo..lt-1
    while (Ls[rt].height > pv)
      rt--;
    // Ls[j]>pv for j in rt+1..hi
    if (lt < rt) {
      swap(Ls, lt, rt);
      lt++;
      rt--;
    }
  }
  if (Ls[lt].height < pv && lt <= hi)
    pivPos = lt;
  else
    pivPos = lt - 1;
  swap(Ls, lo, pivPos);
  // Postcond.: (Ls[j]<=pv for j in lo..pivPos-1) and (Ls[j]>pv for j in
  // pivPos+1..hi)
  return pivPos;
}

int threePart(PERSON Ls[], int lo, int hi, int pInd) {
  swap(Ls, pInd, hi - 1);
  int pivPos, lt, rt, mid, pv;
  lt = lo;
  rt = hi - 2;
  mid = lo;
  pv = Ls[hi - 1].height;
  while (mid <= rt) {
    if (Ls[mid].height < pv) {
      swap(Ls, lt, mid);
      lt++;
      mid++;
    } else if (Ls[mid].height > pv) {
      swap(Ls, mid, rt);
      rt--;
    } else {
      mid++;
    }
  }
  swap(Ls, mid, hi - 1);
  return mid;
}

int lomutoPart(PERSON Ls[], int lo, int hi, int pInd) {
  swap(Ls, hi, pInd);
  int i = lo;
  int pv = Ls[hi].height;
  for (int j = lo; j < hi; ++j) {
    if (Ls[j].height <= pv) {
      swap(Ls, i, j);
      ++i;
    }
  }
  swap(Ls, hi, i);
  return i;
}

int main() {
  FILE *fp = fopen("dat1000.csv", "r");
  if (!fp) {
    printf("Error opening file\n");
    exit(1);
  }
  double time_taken;
  struct timeval t1, t2;
  PERSON *arr = (PERSON *)malloc(1000 * sizeof(PERSON));
  for (int i = 0; i < 1000; ++i) {
    char *line = malloc(100);
    fscanf(fp, "%d,%[^,],%d,%d,%d\n", &arr[i].id, line, &arr[i].age,
           &arr[i].height, &arr[i].weight);
    arr[i].name = line;
  }

  gettimeofday(&t1, NULL);
  lomutoPart(arr, 0, 999, 500);
  // part(arr, 0, 999, 500);
  // threePart(arr, 0, 999, 500);
  gettimeofday(&t2, NULL);
  time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
  time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
  printf("Total %f seconds to execute\n", time_taken);
  printf("%s\n", arr[42].name);
  free(arr);
  fclose(fp);
  return 0;
}
