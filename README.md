# SplayPy-Paper

Implementation of [Splay trees](https://www.cs.cmu.edu/~sleator/papers/self-adjusting.pdf "Sleator, Tarjan: Self-Adjusting Binary Search Trees") in Python as part of a research paper (German).

Upstream is tested with Conda & Python 3.7. Any Python distribution >=3.7 should work, but is not regularly tested.

For setup under Conda, run `conda install --file requirements.txt` and `pip install -r pip_only_requirements.txt`.

For setup under a normal `pip` environment, run `pip install -r all_requirements.txt` (or `pip3` if applicable).

Regardless of Conda or regular `pip`, [Graphviz](http://graphviz.org/) will need to be installed. For Cython, a working C compiler, such as [GCC](https://gcc.gnu.org/), [Clang/LLVM](https://clang.llvm.org/), or [MSVC](https://visualstudio.microsoft.com/), will need to be installed.

Run `jupyter notebook` to open the notebook.
