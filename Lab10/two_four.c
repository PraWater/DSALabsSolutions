#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int keys[3];
  struct node *children[4];
  int num_keys;
  int isLeaf;
} Node;

typedef struct tree {
  Node *root;
} Tree;

Node *new_node() {
  Node *temp = malloc(sizeof(Node));
  for (int i = 0; i < 3; i++) {
    temp->keys[i] = 0;
    temp->children[i] = NULL;
  }
  temp->children[3] = NULL;
  temp->isLeaf = 0;
  temp->num_keys = 0;
  return temp;
}

void insert_24(Tree *tree, int val) {
  Node *temp = tree->root;
  if (temp == NULL) {
    Node *myNode = new_node();
    myNode->isLeaf = 1;
    myNode->keys[0] = val;
    myNode->num_keys = 1;
    tree->root = myNode;
    return;
  }

  // traverse to leaf, splitting 4-nodes as we go
  // A 4-node is a node with 3 keys and 4 children
  Node *parent = NULL;
  while (temp) {
    if (temp->num_keys == 3) {
      // split 4-node
      Node *newNode = new_node();
      newNode->isLeaf = temp->isLeaf;
      newNode->children[0] = temp->children[2];
      newNode->children[1] = temp->children[3];
      newNode->keys[0] = temp->keys[2];
      newNode->num_keys = 1;
      temp->children[2] = NULL;
      temp->children[3] = NULL;
      temp->num_keys = 1;
      // insert new node into parent
      if (parent == NULL) {
        parent = new_node();
        parent->isLeaf = 0;
        parent->children[0] = temp;
        parent->children[1] = newNode;
        parent->keys[0] = temp->keys[1];
        parent->num_keys = 1;
        tree->root = parent;
        printf("Created new root node\n");
      } else
      // The parent must have 1 or 2 keys since all 3 nodes have been split
      {
        if (parent->num_keys == 1) {
          if (parent->keys[0] > temp->keys[1]) {
            parent->children[2] = parent->children[1];
            parent->children[1] = newNode;
            parent->keys[1] = parent->keys[0];
            parent->keys[0] = temp->keys[1];
          } else {
            parent->children[2] = newNode;
            parent->keys[1] = temp->keys[1];
          }
          parent->num_keys = 2;
        }
        // ...
        // 2 keys in parent
        else
        // ...
        {
          if (parent->keys[0] > temp->keys[1]) {
            parent->children[3] = parent->children[2];
            parent->children[2] = parent->children[1];
            parent->children[1] = newNode;
            parent->keys[2] = parent->keys[1];
            parent->keys[1] = parent->keys[0];
            parent->keys[0] = temp->keys[1];
          } else if (parent->keys[1] > temp->keys[1]) {
            parent->children[3] = parent->children[2];
            parent->children[2] = newNode;
            parent->keys[2] = parent->keys[1];
            parent->keys[1] = temp->keys[1];
          } else {
            parent->children[3] = newNode;
            parent->keys[2] = temp->keys[1];
          }
          parent->num_keys = 3;
        }
      }
      // Find the correct parent and child for the next iteration
      for (int i = 0; i <= parent->num_keys; i++) {
        if (val < parent->keys[i]) {
          parent = parent->children[i];
          break;
        } else if (i == parent->num_keys) {
          parent = parent->children[i];
          break;
        }
      }
      // Find the correct child for the next iteration
      for (int i = 0; i <= parent->num_keys; i++) {
        if (val < parent->keys[i]) {
          temp = parent->children[i];
          break;
        } else if (i == parent->num_keys) {
          temp = parent->children[i];
          break;
        }
      }
    }
    // If the node is not a 4-node, just traverse to the correct child
    else {
      parent = temp;
      // Find the correct child for the next iteration
      for (int i = 0; i < parent->num_keys; i++) {
        if (val < parent->keys[i]) {
          temp = parent->children[i];
          break;
        }
      }
      if (parent == temp) {
        temp = parent->children[parent->num_keys];
      }
    }
  }
  // Insert the value into the leaf
  for (int i = parent->num_keys - 1; i >= 0; i--) {
    if (val < parent->keys[i]) {
      parent->keys[i + 1] = parent->keys[i];
    } else {
      parent->keys[i + 1] = val;
      break;
    }
    if (i == 0) {
      parent->keys[i] = val;
    }
  }
  parent->num_keys++;
}

void print_tree(Node *node, int level) {
  printf("%*s", level * 2, "");
  if (node == NULL) {
    return;
  }
  if (node->isLeaf == 1) {
    for (int i = 0; i < node->num_keys; i++) {
      printf("%d ", node->keys[i]);
    }
    printf("\n");
  } else {
    for (int i = 0; i < node->num_keys; i++) {
      printf("%d ", node->keys[i]);
    }
    printf("\n");
    for (int i = 0; i <= node->num_keys; i++) {
      print_tree(node->children[i], level + 1);
    }
  }
}

Node *search(int key, Tree *tree) {
  Node *parent, *temp = tree->root;
  while (temp) {
    parent = temp;
    // Find the correct child for the next iteration
    for (int i = 0; i < parent->num_keys; i++) {
      if (key == parent->keys[i]) {
        return parent;
      } else if (key < parent->keys[i]) {
        temp = parent->children[i];
        break;
      }
    }
    if (parent == temp) {
      temp = parent->children[parent->num_keys];
    }
  }
  return temp;
}

int main() {
  Tree *tree = malloc(sizeof(Tree));
  tree->root = NULL;
  int keys[] = {4, 6, 14, 20, 2, 5, 10, 8, 15, 12, 18, 25, 16};
  for (int i = 0; i <= 12; i++) {
    insert_24(tree, keys[i]);
    printf("Tree after inserting %d\n", keys[i]);
    print_tree(tree->root, 0);
  }
  Node *sres = search(10, tree);
  if (sres)
    printf("Key found\n");
  else
    printf("Not found");
  sres = search(13, tree);
  if (sres)
    printf("Key found\n");
  else
    printf("Not found\n");
}
