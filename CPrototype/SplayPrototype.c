#include <stdio.h>
#include <stdlib.h>
#include "Enums.h"
#include "Node.h"
#include "NodeStack.h"
#include "BoolStack.h"

struct node* initTree() {
  struct node* node = malloc(sizeof(struct node));
  node->payload = NULL;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void clearTree(struct node* node) {
  if (node->left != NULL) clearTree(node->left);
  if (node->right != NULL) clearTree(node->right);
  free(node);
}

// internal function that does not print a newline
void showTreeRec(struct node* node, void (*show)(void*)) {
  if (node == NULL || node->payload == NULL)
    printf("NULL");
  else {
    printf("(");
    (*show)(node->payload);
    printf(", ");
    showTreeRec(node->left, show);
    printf(", ");
    showTreeRec(node->right, show);
    printf(")");
  }
}

void showTree(struct node* node, void (*show)(void*)) {
  showTreeRec(node, show);
  printf("\n");
}

void splay(struct node* node, struct nodeStack* parentStack, struct boolStack* directionStack) {
  while (isEmptyNode(parentStack) == FALSE) {
    struct node* parent = popNode(parentStack);
    enum boolean isLeftChild = popBool(directionStack);
    if (isEmptyNode(parentStack) == TRUE) {
      // zig
      if (isLeftChild == TRUE) {
        /* left zig: / */
        parent->left = node->right;
        node->right = parent;
      } else {
        /* right zig: \ */
        parent->right = node->left;
        node->left = parent;
      }
    } else {
      // zig-zig or zig-zag
      struct node* grandparent = popNode(parentStack);
      enum boolean isLeftGrandchild = popBool(directionStack);
      if (isLeftChild == TRUE && isLeftGrandchild == TRUE) {
        /* left zig-zig:  /
         *               /  */
        grandparent->left = parent->right;
        parent->left = node->right;
        parent->right = grandparent;
        node->right = parent;
      } else if (isLeftChild == FALSE && isLeftGrandchild == TRUE) {
        /* left-right zig-zag: /
         *                     \ */
        parent->right = node->left;
        grandparent->left = node->right;
        node->left = parent;
        node->right = grandparent;
      } else if (isLeftChild == FALSE && isLeftGrandchild == FALSE) {
        /* right zig-zig: \
         *                 \ */
        grandparent->right = parent->left;
        parent->left = grandparent;
        parent->right = node->left;
        node->left = parent;
      } else {
        /* right-left zig-zag: \
         *                     / */
        grandparent->right = node->left;
        parent->left = node->right;
        node->left = grandparent;
        node->right = parent;
      }
    }
  }
  free(parentStack);
  free(directionStack);
}

struct node* insert(struct node* node, void* payload, enum order (*order)(void*, void*)) {
  struct nodeStack* parentStack = initNodeStack();
  struct boolStack* directionStack = initBoolStack();
  while (1) {
    // break using return when inserted
    if (node->payload == NULL) {
      // empty tree
      node->payload = payload;
      return node;
    } else if ((*order)(payload, node->payload) == LESS) {
      if (node->left == NULL) {
        struct node* leaf = malloc(sizeof(struct node));
        leaf->payload = payload;
        leaf->left = NULL;
        leaf->right = NULL;
        node->left = leaf;
        /* splay new child up, appending self to the parent stack,
         * the child being a left child of self */
        pushNode(parentStack, node);
        pushBool(directionStack, TRUE);
        splay(leaf, parentStack, directionStack);
        // newly inserted node is new root after splay
        return leaf;
      } else {
        // insert to the left recursively, child is left child
        pushNode(parentStack, node);
        pushBool(directionStack, TRUE);
        node = node->left;
      }
    } else if ((*order)(payload, node->payload) == EQUALS) {
      // element is present (no double elements in sets), just splay up
      splay(node, parentStack, directionStack);
      // node is root after splay
      return node;
    } else {
      if (node->right == NULL) {
        struct node* leaf = malloc(sizeof(struct node));
        leaf->payload = payload;
        leaf->left = NULL;
        leaf->right = NULL;
        node->right = leaf;
        // splay (right) child up
        pushNode(parentStack, node);
        pushBool(directionStack, FALSE);
        splay(leaf, parentStack, directionStack);
        return leaf;
      } else {
        // insert on right child recursively
        pushNode(parentStack, node);
        pushBool(directionStack, FALSE);
        node = node->right;
      }
    }
  }
}

