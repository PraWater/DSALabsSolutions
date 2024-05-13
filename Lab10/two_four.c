#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int keys[3];
  struct node *children[4];
  struct node *parent;
  int num_keys;
  bool isLeaf;
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
  temp->parent = NULL;
  temp->isLeaf = false;
  temp->num_keys = false;
  return temp;
}

void insert_24(Tree *tree, int val) {
  Node *temp = tree->root;
  if (temp == NULL) {
    Node *myNode = new_node();
    myNode->isLeaf = true;
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
      newNode->parent = temp->parent;
      newNode->keys[0] = temp->keys[2];
      newNode->num_keys = 1;
      temp->children[2] = NULL;
      temp->children[3] = NULL;
      temp->num_keys = 1;
      // insert new node into parent
      if (parent == NULL) {
        parent = new_node();
        parent->isLeaf = false;
        parent->children[0] = temp;
        parent->children[1] = newNode;
        temp->parent = parent;
        newNode->parent = temp->parent;
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
        newNode->parent = parent;
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
  if (node->isLeaf == true) {
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

void delete(int key, Node *node, Tree *tree) {
  int found = -1;
  for (int i = 0; i < node->num_keys; ++i) {
    if (node->keys[i] == key) {
      found = i;
      break;
    } else if (key < node->keys[i]) {
      // implement "merge on the way down" rule
      Node *child = node->children[i];
      if (child->num_keys == 1) {
        int lCnt = 0, rCnt = 0;
        Node *temp;
        if (i != 0) {
          temp = node->children[i - 1];
          lCnt = temp->num_keys;
        }
        if (i != node->num_keys) {
          temp = node->children[i + 1];
          rCnt = temp->num_keys;
        }
        if (lCnt >= 2) {
          temp = node->children[i - 1];
          child->keys[1] = child->keys[0];
          child->keys[0] = node->keys[i - 1];
          child->children[1] = child->children[0];
          child->children[2] = child->children[1];
          child->children[0] = temp->children[temp->num_keys];
          --(temp->num_keys);
          node->keys[i - 1] = temp->keys[temp->num_keys];
          child->num_keys = 2;
        } else if (rCnt >= 2) {
          temp = node->children[i + 1];
          child->keys[(child->num_keys)++] = node->keys[i];
          child->children[child->num_keys] = temp->children[0];
          node->keys[i] = temp->keys[0];
          for (int j = 0; j < temp->num_keys - 1; ++j) {
            temp->children[j] = temp->children[j + 1];
            temp->keys[j] = temp->keys[j + 1];
          }
          temp->children[temp->num_keys - 1] = temp->children[temp->num_keys];
          --(temp->num_keys);
        } else {
          if (rCnt != 0) {
            Node *rChild = node->children[i + 1];
            child->keys[1] = node->keys[i];
            child->keys[2] = rChild->keys[0];
            child->children[2] = rChild->children[0];
            child->children[3] = rChild->children[1];
            child->num_keys = 3;
            --(node->num_keys);
            for (int j = i; j < node->num_keys; ++j) {
              node->keys[j] = node->keys[j + 1];
              node->children[j + 1] = node->children[j + 2];
            }
            free(rChild);
          } else {
            Node *lChild = node->children[i - 1];
            lChild->keys[1] = node->keys[i - 1];
            lChild->keys[2] = child->keys[0];
            lChild->children[2] = child->children[0];
            lChild->children[3] = child->children[1];
            --(node->num_keys);
            for (int j = i - 1; j < node->num_keys; ++j) {
              node->keys[j] = node->keys[j + 1];
              node->children[j + 1] = node->children[j + 2];
            }
            free(child);
            child = lChild;
            child->num_keys = 3;
          }
          if (node->num_keys == 0) {
            if (tree->root == node) {
              tree->root = child;
            } else {
              Node *parent = node->parent;
              for (int j = 0; j < parent->num_keys + 1; ++j) {
                if (parent->children[j] == node) {
                  parent->children[j] = child;
                  break;
                }
              }
            }
            free(node);
          }
        }
      }
      delete (key, child, tree);
      return;
    }
  }

  if (found == -1) {
    delete (key, node->children[node->num_keys], tree);
    return;
  }

  if (node->isLeaf) {
    if (node->num_keys >= 2) {
      // Case 1 - Leaf with 2 or more keys
      --node->num_keys;
      for (int i = found; i < node->num_keys; ++i) {
        node->keys[i] = node->keys[i + 1];
      }
    } else {
      // Case 3
      Node *parent = node->parent;
      int nodeNo = parent->num_keys;
      for (int i = 0; i < parent->num_keys; i++) {
        if (key < parent->keys[i]) {
          nodeNo = i;
          break;
        }
      }
      int lCnt = 0, rCnt = 0;
      Node *temp;
      if (nodeNo != 0) {
        temp = parent->children[nodeNo - 1];
        lCnt = temp->num_keys;
      }
      if (nodeNo != node->num_keys) {
        temp = parent->children[nodeNo + 1];
        rCnt = temp->num_keys;
      }
      // Case 3.1 - Leaf with 1 key having atleast 1 sibling with 2 or more
      // keys
      if (lCnt >= 2) {
        temp = parent->children[nodeNo - 1];
        node->keys[0] = parent->keys[nodeNo - 1];
        parent->keys[nodeNo - 1] = temp->keys[temp->num_keys - 1];
        --(temp->num_keys);
      } else if (rCnt >= 2) {
        temp = parent->children[nodeNo + 1];
        node->keys[0] = parent->keys[nodeNo];
        parent->keys[nodeNo] = temp->keys[0];
        --(temp->num_keys);
        for (int i = 0; i < temp->num_keys; ++i)
          temp->keys[i] = temp->keys[i + 1];
      } else {
        // Case 3.2 - Leaf with 1 key having siblings with 1 key each
        if (rCnt != 0) {
          --(parent->num_keys);
          node->keys[0] = parent->keys[nodeNo];
          Node *rChild = parent->children[nodeNo + 1];
          for (int i = nodeNo; i < parent->num_keys; ++i) {
            parent->keys[i] = parent->keys[i + 1];
          }
          for (int i = nodeNo + 1; i < parent->num_keys + 1; ++i) {
            parent->children[i] = parent->children[i + 1];
          }
          node->keys[1] = rChild->keys[0];
          node->num_keys = 2;
          free(rChild);
        } else {
          --(parent->num_keys);
          Node *lChild = parent->children[nodeNo - 1];
          lChild->keys[1] = parent->keys[nodeNo - 1];
          for (int i = nodeNo - 1; i < parent->num_keys; ++i) {
            parent->keys[i] = parent->keys[i + 1];
          }
          for (int i = nodeNo; i < parent->num_keys + 1; ++i) {
            parent->children[i] = parent->children[i + 1];
          }
          lChild->num_keys = 2;
          free(node);
        }
      }
    }
  } else {
    // Case 2
    Node *temp;
    temp = node->children[found];
    if (temp->num_keys >= 2) {
      // Case 2.1 - Internal node with left child having 2 or more keys
      node->keys[found] = temp->keys[temp->num_keys - 1];
      delete (node->keys[found], temp, tree);
      return;
    }
    temp = node->children[found + 1];
    if (temp->num_keys >= 2) {
      // Case 2.2 - Internal node with right child having 2 or more keys
      node->keys[found] = temp->keys[0];
      delete (node->keys[found], temp, tree);
      return;
    }
    // Case 2.3 - Internal node with both children having 1 key each
    --(node->num_keys);
    for (int i = found; i < node->num_keys; ++i) {
      node->keys[i] = node->keys[i + 1];
    }
    for (int i = found + 1; i < node->num_keys + 1; ++i) {
      node->children[i] = node->children[i + 1];
    }
    Node *lChild = node->children[found], *rChild = temp;
    lChild->keys[1] = key;
    lChild->children[2] = rChild->children[0];
    lChild->children[3] = rChild->children[1];
    lChild->keys[2] = rChild->keys[0];
    lChild->num_keys = 3;
    free(rChild);
    delete (key, node, tree);
  }
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
  // Case 1 test
  delete (5, tree->root, tree);
  print_tree(tree->root, 0);
  // Case 2.1 test
  delete (6, tree->root, tree);
  print_tree(tree->root, 0);
  // Case 2.2 test
  delete (4, tree->root, tree);
  print_tree(tree->root, 0);
  // Case 3.1 test
  delete (2, tree->root, tree);
  print_tree(tree->root, 0);
  // Case 3.2 test
  // delete (8, tree->root);
  // print_tree(tree->root, 0);
  // Case 2.3 test
  delete (10, tree->root, tree);
  print_tree(tree->root, 0);
}
