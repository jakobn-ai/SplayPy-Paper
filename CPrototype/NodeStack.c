#include <stdlib.h>
#include <stdio.h>
#include "Enums.h"
#include "Node.h"
#include "NodeStack.h"

struct nodeStack* initNodeStack() {
  struct nodeStack* stack = malloc(sizeof(struct nodeStack));
  if (stack == NULL) {
    fprintf(stderr, "Alloc of empty nodeStack failed");
    exit(1);
  }
  stack->height = -1;
  stack->node = malloc(0);
  if (stack->node == NULL) {
    fprintf(stderr, "Alloc of empty nodeStack array failed");
    exit(1);
  }
  return stack;
}

void clearNodeStack(struct nodeStack* stack) {
  free(stack->node);
}

enum boolean isEmptyNode(struct nodeStack* stack) {
  return stack->height == -1 ? TRUE : FALSE;
}

void pushNode(struct nodeStack* stack, struct node* node) {
  int oldHeight = stack->height;
  stack->height++;
  if (oldHeight > stack->height) {
    fprintf(stderr, "Stack overflow on nodeStack");
    exit(1);
  }
  stack->node = realloc(stack->node, (stack->height + 1) * sizeof(struct node));
  if (stack->node == NULL) {
    fprintf(stderr, "Growing of boolStack failed");
    exit(1);
  }
  stack->node[stack->height] = node;
}

struct node* popNode(struct nodeStack* stack) {
  if (stack->height < 0) {
    fprintf(stderr, "Popped empty boolStack");
    exit(1);
  }
  struct node* node = stack->node[stack->height];
  stack->node = realloc(stack->node, stack->height * sizeof(struct node));
  if (stack->node == NULL) {
    fprintf(stderr, "Shrinking of boolStack failed");
    exit(1);
  }
  stack->height--;
  return node;
}

