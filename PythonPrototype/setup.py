from distutils.core import setup
from Cython.Build import cythonize

setup(name="Splay prototype",
      ext_modules=cythonize("CythonPrototype.pyx"))
