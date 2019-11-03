#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Enums.h"
#include "Node.h"
#include "BoolStack.h"
#include "NodeStack.h"
#include "SplayPrototype.h"

// length of test array
#define LENGTH 100000

void showInt(void* a) {
  printf("%d", *(int*) a);
}

enum order orderInts(void* a, void* b) {
  return *(int*) a < *(int*) b ? LESS : *(int*) a == *(int*) b ? EQUALS : GREATER;
}

int main(int argc, char** argv) {
  srand(time(NULL));

  int* myArray = malloc(LENGTH * sizeof(int));
  for (int i = 0; i < LENGTH; i++)
    myArray[i] = i;
  // Fisher-Yates shuffle
  int j, tmp;
  for (int i = LENGTH - 1; i >= 0; i--) {
    j = rand() % (i + 1);
    tmp = myArray[j];
    myArray[j] = myArray[i];
    myArray[i] = tmp;
  }

  struct node* mySplay = initTree();
  for (int i = 0; i < LENGTH; i++) {
    mySplay = insert(mySplay, myArray + i, &orderInts);
  }

  // showTree(mySplay, &showInt);
  clearTree(mySplay);
  free(myArray);
}

