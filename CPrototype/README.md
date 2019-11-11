# C Prototype

This folder contains a splay tree prototype written in C.

* `Enums.h` contains required enums
* `Node.h` contains the struct definition for nodes (payload is of type `void*`)
* `BoolStack.c` defines a very memory efficient stack for booleans. This is used as a stack of directions when splaying.
* `NodeStack.c` defines a stack for nodes. This is used as a stack of parents when splaying.
* `SplayPrototype.c` gives a stack-based iterative splay tree implementation.
* `SplayMinitest.c` inserts 10^5 shuffled entries into a splay tree.

To run the minitest, run `make SplayMinitest` and execute `SplayMinitest.o`. A C compiler is required. `make` is required if you want to compile using the Makefile (not a necessity, just a convenience).
