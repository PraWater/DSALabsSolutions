#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "bst.h"
#include "stack.h"

BST *new_bst()
{
    BST *bst = malloc(sizeof(BST));
    bst->root = NULL;
    return bst;
}

Node *new_node(int value)
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

void traverse_pre_order(Node *node)
{
    if (node == NULL)
    {
        printf("null ");
        return;
    }
    printf("%d ", node->value);
    traverse_pre_order(node->left);
    traverse_pre_order(node->right);
}

void traverse_post_order(Node *node)
{
    if (node == NULL)
    {
        printf("null ");
        return;
    }
    traverse_post_order(node->left);
    traverse_post_order(node->right);
    printf("%d ", node->value);
}

void insert(BST *bst, int value)
{
    Node *node = new_node(value);
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

int find_min(BST *bst)
{
    Node *current = bst->root;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current->value;
}

int find_max(BST *bst)
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
        Node *current = bst->root;
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
        Node *current = bst->root;
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
        Node *current = bst->root;
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
    delete (bst, temp);
    return;
}

BST *constructBST(int arr[], int size)
{
    BST *bst = new_bst();
    for (int i = 0; i < size; ++i)
    {
        insert(bst, arr[i]);
    }
    return bst;
}

bool satisfyBST(Node *node)
{
    if (node == NULL)
        return true;
    if (node->left != NULL && node->left->value >= node->value)
        return false;
    if (node->right != NULL && node->right->value < node->value)
        return false;
    return satisfyBST(node->left) ? satisfyBST(node->right) : false;
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

Element ntoe(Node *n)
{
    Element e;
    e.n = n;
    return e;
}

void levelOrder(BST *bst)
{
    Queue *q = createQueue();
    Node *n = bst->root;
    enqueue(q, ntoe(n));
    while (!isEmpty(q))
    {
        Element *e = front(q);
        dequeue(q);
        if (e->n == NULL)
            continue;
        enqueue(q, ntoe(e->n->left));
        enqueue(q, ntoe(e->n->right));
        printf("%d ", e->n->value);
    }
    destroyQueue(q);
    printf("\n");
}

void reverseLevelOrder(BST *bst)
{
    Queue *q = createQueue();
    Stack *s = newStack();
    Node *n = bst->root;
    enqueue(q, ntoe(n));
    while (!isEmpty(q))
    {
        Element *e = front(q);
        dequeue(q);
        if (e->n == NULL)
            continue;
        enqueue(q, ntoe(e->n->left));
        enqueue(q, ntoe(e->n->right));
        push(s, *e);
    }
    destroyQueue(q);
    while (!isempty(s))
    {
        printf("%d ", top(s)->n->value);
        pop(s);
    }
    freeStack(s);
    printf("\n");
}

// Driver program to test the above functions (feel free to play around with this)
int main()
{
    // FILE *fptr = fopen("n_integers.txt", "r");
    // if (fptr == NULL)
    // {
    // printf("Error opening file");
    // exit(1);
    // }
    // int n;
    // fscanf(fptr, "%d,[", &n);
    // int *arr = (int *)malloc(n * sizeof(int));
    // for (int i = 0; i < n; ++i)
    // {
    //     fscanf(fptr, "%d ", &arr[i]);
    // }
    int arr[] = {6, 5, 2, 5, 7, 8};
    int n = 6;
    BST *bst = constructBST(arr, n);
    traverse_in_order(bst->root);
    printf("\n");
    levelOrder(bst);
    reverseLevelOrder(bst);
    satisfyBST(bst->root) ? printf("BST is valid\n") : printf("BST is not valid\n");
    // printf("Height = %d\n", height(bst->root));
    // printf("Max = %d\n", find_max(bst));
    // printf("Min = %d\n", find_min(bst));
    // removeHalfNodes(bst);
    // satisfyBST(bst->root) ? printf("BST is valid\n") : printf("BST is not valid\n");
    // printf("Height = %d\n", height(bst->root));
    // traverse_post_order(bst->root);
    return 0;
}
