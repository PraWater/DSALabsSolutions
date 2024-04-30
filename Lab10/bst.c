#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} Node;

typedef struct bst {
    Node *root;
} BST;

BST *newBST() 
{
    BST *bst = malloc(sizeof(BST));
    bst->root = NULL;
    return bst;
}

Node *newNode(int value) 
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
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
    printf("%d ", node->value);
    traverse_in_order(node->right);
}

void traverse_pre_order (Node *node)
{
    if (node == NULL) {
        printf("null ");
        return;
    }
    printf("%d ", node->value);
    traverse_pre_order(node->left);
    traverse_pre_order(node->right);
}

void traverse_post_order (Node *node)
{
    if (node == NULL) {
        printf("null ");
        return;
    }
    traverse_post_order(node->left);
    traverse_post_order(node->right);
    printf("%d ", node->value);
}

void insert(BST *bst, int value)
{
    Node *node = newNode(value);
    if (bst->root == NULL) 
    {
        bst->root = node;
        return;
    }
    Node *current = bst->root;
    while (current != NULL) 
    {
        if (value < current->value) 
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
        if (key == current->value) 
        {
            return 1;
        } 
        else if (key < current->value) 
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

int findMin(BST *bst)
{
    Node *current = bst->root;
    while (current->left != NULL) 
    {
        current = current->left;
    }
    return current->value;
}

int findMax(BST *bst)
{
    Node *current = bst->root;
    while (current->right != NULL) 
    {
        current = current->right;
    }
    return current->value;
}

Node *predecessor(Node *node)
{
    if (node->left == NULL)
    {
        return NULL;
    }
    Node *current = node->left;
    while (current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

Node *successor(Node *node)
{
    if (node->right == NULL)
    {
        return NULL;
    }
    Node *current = node->right;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

void delete(BST *bst, Node *node)
{
    if (node == NULL)
        return;
    if (node->left == NULL && node->right == NULL)
    {
        // Node is a leaf
        Node* current = bst->root;
        while (current != NULL)
        {
            if (current->left == node)
            {
                current->left = NULL;
                break;
            }
            if (current->right == node)
            {
                current->right = NULL;
                break;
            }
            if (node->value < current->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        free(node);
        return;
    }
    
    if (node->left == NULL)
    {
        // Node only has right child
        Node* current = bst->root;
        if (current == node)
        {
            bst->root = node->right;
            free(node);
            return;
        }
        while (current != NULL)
        {
            if (current->left == node)
            {
                current->left = node->right;
                break;
            }
            if (current->right == node)
            {
                current->right = node->right;
                break;
            }
            if (node->value < current->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        free(node);
        return;
    }

    if (node->right == NULL)
    {
        // Node only has left child
        Node* current = bst->root;
        if (current == node)
        {
            bst->root = node->left;
            free(node);
            return;
        }
        while (current != NULL)
        {
            if (current->left == node)
            {
                current->left = node->left;
                break;
            }
            if (current->right == node)
            {
                current->right = node->left;
                break;
            }
            if (node->value < current->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        free(node);
        return;
    }

    // Node has both children
    Node *temp = successor(node);
    node->value = temp->value;
    delete(bst, temp);
    return;
}

BST *constructBST(int arr[], int size)
{
    BST *bst = newBST();
    for (int i = 0; i < size; ++i) {
        insert(bst, arr[i]);
    }
    return bst;
}

bool satisfyBST(Node *node) {
    if (node == NULL) return true;
    if (node->left != NULL && node->left->value >= node->value) return false;
    if (node->right != NULL && node->right->value < node->value) return false;
    return satisfyBST(node->left) ? satisfyBST(node->right) : false;
}

int height(Node *node) {
    if (node == NULL) return 0;
    int l = height(node->left);
    int r = height(node->right);
    return (l>r) ? ++l : ++r;
}

void removeHalfAux(Node *current, Node *parent, bool direction) {
	if (current->left == NULL && current->right == NULL) return;
	if (current->left == NULL) {
		if (direction) {
			parent->left = current->right;
			free(current);
			removeHalfAux(parent->left, parent, direction);
		}
		else {
			parent->right = current->right;
			free(current);
			removeHalfAux(parent->right, parent, direction);
		}
		return;
	}
	if (current->right == NULL) {
		if (direction) {
			parent->left = current->left;
			free(current);
			removeHalfAux(parent->left, parent, direction);
		}
		else {
			parent->right = current->left;
			free(current);
			removeHalfAux(parent->right, parent, direction);
		}
		return;
	}
	removeHalfAux(current->left, current, true);
	removeHalfAux(current->right, current, false);
}

void removeHalfNodes(BST *bst) {
	Node *current = bst->root;
	if (current->left == NULL && current->right == NULL) return;
	while ((current->right == NULL)^(current->left == NULL)){
	if (current->left == NULL) {
		//Only right node exists
		bst->root = current->right;
		free(current);
	}
	else if (current->right == NULL) {
		//Only left node exists
		bst->root = current->left;
		free(current);
	}
	current = bst->root;
	}
	removeHalfAux(current->left, current, true);
	removeHalfAux(current->right, current, false);
}

bool isHeightBalanced(Node *node) {
    int ans = height(node->left) - height(node->right);
    return (ans>=-1 && ans <=1);
}

Node *rotateLeft(Node* x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node *rotateRight(Node* x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node *insertAVL(Node* node, int value) {
    if (node == NULL)
    {
        node = newNode(value);
    }
    else if (value < node->value)
    {
        node->left = insertAVL(node->left, value);
    }
    else
    {
        node->right = insertAVL(node->right, value);
    }
    if (isHeightBalanced(node))
    {
        if (value < node->value)
        {
            if (value < node->left->value)
            {
                // LL imbalance
                node = rotateRight(node);
            }
            else
            {
                // LR imbalance
                node->left = rotateLeft(node->left);
                node = rotateRight(node);
            }
        }
        else
        {
            if (value > node->right->value)
            {
                // RR imbalance
                node = rotateLeft(node);
            }
            else
            {
                // RL imbalance
                node->right = rotateRight(node->right);
                node = rotateLeft(node);
            }
        }
    }
    return node;
}

void traverse_bfs(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    Node *queue[100];
    int front = 0;
    int back = 0;
    queue[back++] = node;
    while (front != back)
    {
        Node *current = queue[front++];
        printf("%d ", current->value);
        if (current->left != NULL)
        {
            queue[back++] = current->left;
        }
        if (current->right != NULL)
        {
            queue[back++] = current->right;
        }
    }
}

int main()
{
    // FILE *fptr = fopen("n_integers.txt", "r");
    // if (fptr == NULL) {
    //     printf("Error opening file");
    //     exit(1);
    // }
    // int n;
    // fscanf(fptr, "%d,[", &n);
    // int* arr = (int *) malloc(n*sizeof(int));
    // for (int i = 0; i < n; ++i) {
    //     fscanf(fptr, "%d ", &arr[i]);
    // }

    // int arr[] = {2, 1, 3, 4, 5, 6, 7, 8};
    // BST *bst = constructBST(arr, n);
    printf("start");
    BST *bst = newBST();
    printf("bst made");
    bst->root = newNode(1);
    printf("node 1 inserted");
    for (int i = 2; i <= 9; ++i) {
        insertAVL(bst->root, i);
        printf("node %d inserted", i);
    }
    printf("Height of tree is %d", height(bst->root));
    traverse_bfs(bst->root);
    return 0;
}