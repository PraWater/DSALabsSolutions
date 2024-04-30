#ifndef BST_H
#define BST_H

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
} Node;

typedef struct bst
{
    Node *root;
} BST;

#endif