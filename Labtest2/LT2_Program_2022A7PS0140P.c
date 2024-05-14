#include <stdio.h>
#include <stdlib.h>

// structure definition for a node to store each item in a transaction
typedef struct node NODE;
struct node
{
    int ele;
    NODE *next;
};

// structure definition for a linked list that stores nodes containing transactions
typedef struct linked_list LIST;
struct linked_list
{
    int count;
    NODE *head;
    NODE *tail;
    LIST *next;
};

// structure definition for a upper linked list that is a linked list of linked lists
typedef struct upper_linked_list UPPER_LIST;
struct upper_linked_list
{
    int count;
    LIST *head;
    LIST *tail;
};

//structure definition for storing item id and its frequency
struct freq
{
    int item, freq;
};
typedef struct freq Freq;

//structure definition for heap of Freq structures. Heap was chosen because element with highest freq can be accessed in O(1) in max heap 
struct heap
{
    Freq *data;
    int size;
    int capacity;
    int depth;
};
typedef struct heap Heap;

// Creates a new linked list that stores nodes containing transactions
LIST *createNewList()
{
    LIST *myList;
    myList = (LIST *)malloc(sizeof(struct linked_list));
    myList->count = 0;
    myList->head = NULL;
    myList->tail = NULL;
    myList->next = NULL;
    return myList;
}

// Creates a new upper linked list that stores a linked list of linked lists
UPPER_LIST *createNewUpperList()
{
    UPPER_LIST *myList;
    myList = (UPPER_LIST *)malloc(sizeof(struct upper_linked_list));
    myList->count = 0;
    myList->head = NULL;
    myList->tail = NULL;
    return myList;
}

// Creates a node that stores each item in a transaction
NODE *createNewNode(int value)
{
    NODE *myNode;
    myNode = (NODE *)malloc(sizeof(struct node));
    myNode->ele = value;
    myNode->next = NULL;
    return myNode;
}

// Creates a Heap that stores Freq structures
Heap *createNewHeap()
{
    Heap *h = (Heap *)malloc(sizeof(struct heap));
    h->data = malloc(sizeof(Freq));
    h->size = 0;
    h->capacity = 1;
    h->depth = 0;
    return h;
}

// Inserts linked list to upper linked list at the end and updates count and tail of ulist
void insertListAtEnd(UPPER_LIST *ulist, LIST *list)
{
    if (ulist->count == 0)
    {
        ulist->head = list;
        ulist->tail = list;
    }
    else
    {
        LIST *temp = ulist->tail;
        temp->next = list;
        ulist->tail = list;
    }
    ++(ulist->count);
    return;
}

// Inserts node to linked list at the end and updates count and tail of list
void insertNodeAtEnd(LIST *list, NODE *node)
{
    if (list->count == 0)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        NODE *temp = list->tail;
        temp->next = node;
        list->tail = node;
    }
    ++(list->count);
    return;
}

//Helper function that calculates 2^a
int pow2(int a)
{
    int ans = 1;
    while (a--)
        ans *= 2;
    return ans;
}

//Takes a structure of type freq and inserts it into the heap. Also increases the capacity of heap if required by using realloc()
void insertHeap(Heap *h, Freq f)
{
    if (h->size >= h->capacity)
    {
        h->capacity += pow2(++(h->depth));
        h->data = realloc(h->data, sizeof(Freq) * h->capacity);
    }
    h->data[(h->size)++] = f;
}

//Returns the left child int the heap of the index passed
int left_child(int index) {
    return (2*index + 1);
}

//Returns the right child int the heap of the index passed
int right_child(int index) {
    return (2*index + 2);
}

/*
It takes in as input a heap and an index. Under the pre-condition that the left and right subtrees of the given node are already
satisfying the heap property, the routine makes the heap property satisfies at the given node’s level too by recursively making
the largest node “float down” till the heap property is satisfied by the subtree rooted at the given node’s position.
*/
void max_heapify(Heap* h, int index)
{
    int left = left_child(index);
    int right = right_child(index);
    int largest = index;
    if (left < h->size && h->data[left].freq > h->data[largest].freq)
    {
        largest = left;
    }
    if (right < h->size && h->data[right].freq > h->data[largest].freq)
    {
        largest = right;
    }
    if (largest != index)
    {
        Freq temp = h->data[index];
        h->data[index] = h->data[largest];
        h->data[largest] = temp;
        max_heapify(h, largest);
    }
}

// helper function that adds the elements in arr to a linked list and then attaches linked list to ulist
void createDataHelper(UPPER_LIST *ulist, int *arr, int n)
{
    LIST *list = createNewList();
    for (int i = 0; i < n; ++i)
        insertNodeAtEnd(list, createNewNode(arr[i]));
    insertListAtEnd(ulist, list);
}

// populates the given data into ulist as per the question a)
UPPER_LIST *createData()
{
    UPPER_LIST *ulist = createNewUpperList();

    // Bill 1
    int arr1[] = {1, 5, 7, 100};
    createDataHelper(ulist, arr1, 4);

    // Bill 2
    int arr2[] = {74, 65, 62};
    createDataHelper(ulist, arr2, 3);

    // Bill 3
    int arr3[] = {64, 94, 100, 35, 1};
    createDataHelper(ulist, arr3, 5);

    // Bill 4
    int arr4[] = {67, 87, 94, 100, 45, 68, 23};
    createDataHelper(ulist, arr4, 7);

    // Bill 5
    int arr5[] = {89, 46, 73, 85, 90};
    createDataHelper(ulist, arr5, 5);

    // Bill 6
    int arr6[] = {83, 74, 82, 2, 5, 94, 10, 32, 25};
    createDataHelper(ulist, arr6, 9);

    // Bill 7
    int arr7[] = {67};
    createDataHelper(ulist, arr7, 1);

    // Bill 8
    int arr8[] = {68, 56, 93, 92};
    createDataHelper(ulist, arr8, 4);

    // Bill 9
    int arr9[] = {94, 89, 72, 40};
    createDataHelper(ulist, arr9, 4);

    // Bill 10
    int arr10[] = {98, 94, 68, 95, 100, 57, 48};
    createDataHelper(ulist, arr10, 7);

    // Bill 11
    int arr11[] = {97, 89, 94, 56, 72};
    createDataHelper(ulist, arr11, 5);

    // Bill 12
    int arr12[] = {100, 99, 98, 97, 6, 5, 94, 76};
    createDataHelper(ulist, arr12, 8);

    // Bill 13
    int arr13[] = {87, 94, 92, 98, 90, 99};
    createDataHelper(ulist, arr13, 6);

    // Bill 14
    int arr14[] = {64, 28, 47, 95, 10, 75, 38, 36, 100};
    createDataHelper(ulist, arr14, 9);

    // Bill 15
    int arr15[] = {73, 49, 48, 20, 19, 17};
    createDataHelper(ulist, arr15, 6);

    // Bill 16
    int arr16[] = {18, 17, 16, 15, 19, 94};
    createDataHelper(ulist, arr16, 6);

    // Bill 17
    int arr17[] = {86, 84, 83, 82, 81, 80, 89, 98, 96, 95, 94};
    createDataHelper(ulist, arr17, 11);

    // Bill 18
    int arr18[] = {66, 76};
    createDataHelper(ulist, arr18, 2);

    // Bill 19
    int arr19[] = {94};
    createDataHelper(ulist, arr19, 1);

    // Bill 20
    int arr20[] = {98, 64, 27};
    createDataHelper(ulist, arr20, 3);
    return ulist;
}

//takes the linked list of linked lists as input and creates a heap. Also converts it to a max_heap by calling the heapify() as per question b)
Heap *representData(UPPER_LIST *ulist)
{
    int *freqArr = (int *)calloc(101, sizeof(int));
    LIST *list = ulist->head;
    while (list)
    {
        NODE *node = list->head;
        while (node)
        {
            ++(freqArr[node->ele]);
            node = node->next;
        }
        list = list->next;
    }
    Heap *heap = createNewHeap();
    for (int i = 1; i < 101; ++i)
    {
        if (freqArr[i] > 0) {
            Freq f;
            f.item = i;
            f.freq = freqArr[i];
            insertHeap(heap, f);
        }
    }
    for (int i = heap->size-1; i >= 0; --i) {
        max_heapify(heap, i);
    }
    return heap;
}

// Prints the item sold most in O(1) as per the question c)
void getMax(Heap *heap)
{
    printf("Item sold most: %d\n", heap->data[0].item);
    // printf("No of times sold: %d\n", heap->data[0].freq);
}

//Main function according to question d)
int main()
{
    UPPER_LIST *ulist = createData();
    Heap *heap = representData(ulist);
    getMax(heap);
    return 0;
}