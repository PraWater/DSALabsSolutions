#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
structure for nodes in the linked list
	value: stores the integer
	next: points to the next node in the linked list
*/
typedef struct listNode ListNode;
struct listNode {
	int value;
	ListNode *next;
};

/*
structure for the linked list
	count: stores the number of nodes in the linked list
	head: points to the first node in the linked list
	tail: points to the last node in the linked list
*/
typedef struct linkedList List;
struct linkedList {
	int count;
	ListNode *head;
	ListNode *tail;
};

/*
structure for nodes of the binary search tree
	list: points to the linked list that is stored in this bstNode
	left: points to the left side child of the bstNode
	right: points to the right side child of the bstNode
	parent: points to the parent of the bstNode
*/
typedef struct bstNode BstNode;
struct bstNode {
	List *list;
	BstNode *left;
	BstNode *right;
	BstNode *parent;
};

/*
structure for the binary search tree
	root: points to the root node of the binary search tree
*/
typedef struct bst BST;
struct bst {
	BstNode *root;
};

/*
Creates a new linked list and returns a pointer to it.
Default values:
	count-0
	head-NULL
	tail-NULL
*/
List *newList() {
	List *list = (List*) malloc(sizeof(List));
	if (list) {
		list->count = 0;
		list->head = NULL;
		list->tail = NULL;
	}
	return list;
}

/*
Creates a new linked list node containing @{int}value and returns a pointer to it.
Default values:
	value-value
	next-NULL
*/
ListNode *newListNode(int value) {
	ListNode *node = (ListNode*) malloc(sizeof(ListNode));
	if (node) {
		node->value = value;
		node->next = NULL;
	}
	return node;
}

//Inserts the @{ListNode *}node at the end of the linked list @{List *}list.
void insertListNodeAtEnd(List *list, ListNode *node) {
	if (list->count == 0) {
		list->head = node;
		list->tail = node;
	}
	else {
		list->tail->next = node;
		list->tail = node;
	}
	++(list->count);
}

/*
Creates a new binary search tree and returns a pointer to it.
Default values:
	root-NULL
*/
BST *newBst() {
	BST *bst = (BST*) malloc(sizeof(BST));
	if (bst) bst->root = NULL;
	return bst;
}

/*
Creates a new binary search tree node containing @{List*}list and returns a pointer to it.
Default values:
	list-list
	left-NULL
	right-NULL
	parent-NULL
*/
BstNode *newBstNode(List* list) {
	BstNode *node = (BstNode*) malloc(sizeof(BstNode));
	if (node) {
		node->list = list;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
	}
	return node;
}

//inserts @{BstNode*}node into @{BST}bst
void insertBst(BST *bst, BstNode* node) {
	if (bst->root == NULL) {
		bst->root = node;
		return;
	}
	BstNode *current = bst->root;
	while (current != NULL) {
		if (node->list->head->value < current->list->head->value) {
			if (current->left == NULL) {
				current->left = node;
				node->parent = current;
				return;
			}
			current = current->left;
		}
		else {
			if (current->right == NULL) {
				current->right = node;
				node->parent = current;
				return;
			}
			current = current->right;
		}
	}
}

/*
Creates a new BST and inserts nodes containing linkedlists from @{FILE *}fp as per part(a) of the question.
Assumption: Each line in the file has a max limit of 10000 characters.
*/
BST *readData(FILE *fp) {
	int MAX_LENGTH = 10000;
	BST* bst = newBst();
	int n;
	fscanf(fp, "%d\n", &n);
	for (int i = 0; i < n; ++i) {
		List *list = newList();
		BstNode *bNode = newBstNode(list);
		char line[MAX_LENGTH];
		fgets(line, MAX_LENGTH, fp);
		int j = 0;
		char *token = strtok(line, " ");
		while (token != NULL) {
			if (isdigit(token[0])) {
				int x = atoi(token);
				ListNode *node = newListNode(x);
				insertListNodeAtEnd(list, node);
			}
			token = strtok (NULL, " ");
		}
		insertBst(bst, bNode);
	}
	return bst;
}

/*
Swaps 2 nodes in a linked list.
@{ListNode *}node1 and @{ListNode *}node2 are the nodes whose next nodes are supposed to be swapped. i.e, node1->next and node2->next will be swapped.
*/
void swap(ListNode *node1, ListNode *node2) {
	ListNode *temp;
	temp = node1->next;
	node1->next = node2->next;
	node2->next = temp;
	node1 = node1->next;
	node2 = node2->next;
	temp = node1->next;
	node1->next = node2->next;
	node2->next = temp;
}

// Uses selection sort to sort @{List *}list from the 2nd node onwards.
void sort(List *list) {
	if (list->count == 1) return;
	ListNode *curr = list->head, *min, *temp, *temp1;
	for (int i = 0; i < list->count - 2; i++) {
		min = curr;
		temp = min->next;
		while (temp->next != NULL) {
			if (temp->next->value < min->next->value) min = temp;
			temp = temp->next;
		}
		swap(curr, min);
		curr = curr->next;
	}
}

//Recursive helper function for sortLists(bst) to traverse the whole tree.
void sortListsHelper(BstNode *node) {
	if (node == NULL) return;
	sort(node->list);
	sortListsHelper(node->left);
	sortListsHelper(node->right);
}

//Sorts all the linked lists stored in @{BST *}bst as per part(b) of the question.
void sortLists(BST *bst) {
	sortListsHelper(bst->root);
}

//Prints all the integers stored in @{List *}list to @{FILE *}fp.
void printList(List *list, FILE *fp) {
	ListNode *temp = list->head;
	while(temp != NULL) {
		fprintf(fp, "%d ", temp->value);
		temp = temp->next;
	}
	fprintf(fp, "\n");
}

//Recursive helper function for traverse(bst, fp).
void traverseHelper(BstNode *node, FILE *fp) {
	if (node == NULL) return;
	traverseHelper(node->left, fp);
	printList(node->list, fp);
	traverseHelper(node->right, fp);
}

//Prints the contents of @{BST *}bst in-order to @{FILE *}fp as per part (c) of the question.
void traverse(BST *bst, FILE *fp) {
	traverseHelper(bst->root, fp);
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Please enter filename as command line argument\n");
		exit(1);
	}
	//Opening file passed through as command line argument.
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	//Calling readData(fp) to insert values from the file into the BST.
	BST *bst = readData(fp);

	//Calling sortLists(bst) to sort all the linked lists in the BST from the 2nd node onwards.
	sortLists(bst);

	//Opening a new file to store the output from traverse(bst, fp1). (In-order traversal)
	FILE *fp1 = fopen("file2.txt", "w");
	traverse(bst, fp1);

	//Closing the files.
	fclose(fp);
	fclose(fp1);
	return 0;
}