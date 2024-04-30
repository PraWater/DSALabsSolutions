#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct person
{
	int id;
	char *name;
	int age;
	int height;
	int weight;
} Person;

typedef struct node
{
	Person val;
	struct node *left;
	struct node *right;
} Node;

typedef struct bst
{
	Node *root;
} BST;

BST *new_bst()
{
	BST *bst = malloc(sizeof(BST));
	bst->root = NULL;
	return bst;
}

Node *new_node(Person person)
{
	Node *node = malloc(sizeof(Node));
	node->val = person;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void traverse_in_order(Node *node)
{
	if (node == NULL)
	{
		printf("null ");
		return;
	}
	traverse_in_order(node->left);
	printf("%d ", node->val.height);
	traverse_in_order(node->right);
}

void insert(BST *bst, Person person)
{
	Node *node = new_node(person);
	if (bst->root == NULL)
	{
		bst->root = node;
		return;
	}
	Node *current = bst->root;
	while (current != NULL)
	{
		if (person.height < current->val.height)
		{
			if (current->left == NULL)
			{
				current->left = node;
				return;
			}
			current = current->left;
		}
		else
		{
			if (current->right == NULL)
			{
				current->right = node;
				return;
			}
			current = current->right;
		}
	}
}

int search(BST *bst, int key)
{
	Node *current = bst->root;
	while (current != NULL)
	{
		if (key == current->val.height)
		{
			return 1;
		}
		else if (key < current->val.height)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}
	return 0;
}

int find_min(BST *bst)
{
	Node *current = bst->root;
	while (current->left != NULL)
	{
		current = current->left;
	}
	return current->val.height;
}

int find_max(BST *bst)
{
	Node *current = bst->root;
	while (current->right != NULL)
	{
		current = current->right;
	}
	return current->val.height;
}

BST *constructBST(Person *arr, int size)
{
	BST *bst = new_bst();
	for (int i = 0; i < size; ++i)
	{
		insert(bst, arr[i]);
	}
	return bst;
}

int height(Node *node)
{
	if (node == NULL)
		return 0;
	int l = height(node->left);
	int r = height(node->right);
	return (l > r) ? ++l : ++r;
}

void removeHalfAux(Node *current, Node *parent, bool direction)
{
	if (current->left == NULL && current->right == NULL)
		return;
	if (current->left == NULL)
	{
		if (direction)
		{
			parent->left = current->right;
			free(current);
			removeHalfAux(parent->left, parent, direction);
		}
		else
		{
			parent->right = current->right;
			free(current);
			removeHalfAux(parent->right, parent, direction);
		}
		return;
	}
	if (current->right == NULL)
	{
		if (direction)
		{
			parent->left = current->left;
			free(current);
			removeHalfAux(parent->left, parent, direction);
		}
		else
		{
			parent->right = current->left;
			free(current);
			removeHalfAux(parent->right, parent, direction);
		}
		return;
	}
	removeHalfAux(current->left, current, true);
	removeHalfAux(current->right, current, false);
}

void removeHalfNodes(BST *bst)
{
	Node *current = bst->root;
	if (current->left == NULL && current->right == NULL)
		return;
	while ((current->right == NULL) ^ (current->left == NULL))
	{
		if (current->left == NULL)
		{
			// Only right node exists
			bst->root = current->right;
			free(current);
		}
		else if (current->right == NULL)
		{
			// Only left node exists
			bst->root = current->left;
			free(current);
		}
		current = bst->root;
	}
	removeHalfAux(current->left, current, true);
	removeHalfAux(current->right, current, false);
}

// Driver program to test the above functions (feel free to play around with this)
int main()
{
	FILE *fptr = fopen("dat10000.csv", "r");
	if (fptr == NULL)
	{
		printf("Error opening file");
		exit(1);
	}
	int n = 10000;
	Person *arr = (Person *)malloc(n * sizeof(Person));
	for (int i = 0; i < n; ++i)
	{
		char *line = malloc(50);
		fscanf(fptr, "%d,%[^,],%d,%d,%d\n", &arr[i].id, line, &arr[i].age, &arr[i].height, &arr[i].weight);
		arr[i].name = line;
	}

	// int arr[] = {2, 1, 3, 4, 5, 6, 7, 8};
	BST *bst = constructBST(arr, n);
	// traverse_in_order(bst->root);
	// printf("\n");
	printf("Height = %d\n", height(bst->root));
	printf("Max = %d\n", find_max(bst));
	printf("Min = %d\n", find_min(bst));
	return 0;
}