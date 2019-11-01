from random import shuffle
from StackSplayItPrototype import SplayTree
my_splay = SplayTree()
my_list = list(range(10**5))
shuffle(my_list)
for i in my_list:
    my_splay.insert(i)
