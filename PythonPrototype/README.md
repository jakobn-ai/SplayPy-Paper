# Python Prototypes

This folder contains several splay tree prototypes written in Python.

* `DLSplayPrototype.py` uses a double linked iterative implementation.
* `StackSplayRecPrototype.py` uses a stack-based recursive implementation.
* `StackSplayItPrototype.py` uses a stack-based iterative implementation.
* `CythonPrototype.pyx` does the same with Cython hints. Run `python[3] setup.py build_ext --inplace` before using.

To run the minitest for one of these implementations, select the respective one in the `SplayTree` import line in `SplayMinitest.py` and run it. It inserts 10^5 shuffled entries. `SetMinitest.py` does the same with native Python sets.
