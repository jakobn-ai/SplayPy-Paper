#include <stdlib.h>
#include <stdio.h>
#include "Enums.h"
#include "BoolStack.h"

// 8 (byte), zero indexed
#define SLOTS 7

struct boolStack* initBoolStack() {
  struct boolStack* stack = malloc(sizeof(struct boolStack));
  if (stack == NULL) {
    fprintf(stderr, "Alloc of empty boolStack failed");
    exit(1);
  }
  stack->height = -1;
  // ensure pushing char upon initial push
  stack->frameIdx = SLOTS;
  stack->payload = malloc(0);
  return stack;
}

void clearBoolStack(struct boolStack* stack) {
  free(stack->payload);
}

enum boolean isEmptyBool(struct boolStack* stack) {
  return stack->height == -1 ? TRUE : FALSE;
}

void pushBool(struct boolStack* stack, enum boolean payload) {
  if (stack->frameIdx == SLOTS) {
    stack->frameIdx = 0;
    int oldHeight = stack->height;
    stack->height++;
    if (oldHeight > stack->height) {
      fprintf(stderr, "Stack overflow on boolStack");
      exit(1);
    }
    stack->payload = realloc(stack->payload, (stack->height + 1) * sizeof(unsigned char*));
    if (stack->payload == NULL) {
      fprintf(stderr, "Growing of boolStack failed");
      exit(1);
    }
    stack->payload[stack->height] = payload == TRUE;
  } else {
    stack->frameIdx++;
    // shift bit to position and put it there
    stack->payload[stack->height] |= (payload == TRUE) << stack->frameIdx;
  }
}

enum boolean popBool(struct boolStack* stack) {
  if (stack->frameIdx == 0) {
    if (stack->height < 0) {
      fprintf(stderr, "Popped empty boolStack");
      exit(1);
    }
    enum boolean payload = stack->payload[stack->height] ? TRUE : FALSE;
    stack->payload = realloc(stack->payload, stack->height * sizeof(unsigned char*));
    if (stack->payload == NULL) {
      fprintf(stderr, "Shrinking of boolStack failed");
      exit(1);
    }
    // at highest position again
    stack->frameIdx = SLOTS;
    stack->height--;
    return payload;
  } else {
    // mask bit at position out
    unsigned char mask = 1 << stack->frameIdx;
    enum boolean payload = (stack->payload[stack->height] & mask) >> stack->frameIdx ? TRUE : FALSE;
    // zero out at position
    stack->payload[stack->height] &= ~mask;
    stack->frameIdx--;
    return payload;
  }
}

