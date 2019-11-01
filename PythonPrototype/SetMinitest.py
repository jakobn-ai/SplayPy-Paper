from random import shuffle
my_set = set()
my_list = list(range(10**5))
shuffle(my_list)
for i in my_list:
    my_set.add(i)
