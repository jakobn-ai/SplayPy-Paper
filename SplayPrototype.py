class Node:
    def __init__(self, payload, left, right, parent):
        self.payload = payload
        self.left = left
        self.right = right
        self.parent = parent

    def show(self):
        if self.payload is None:
            return "None"
        else:
            return f"({self.payload}, {self.left.show()}, {self.right.show()})"

    def insert(self, payload):
        while self.payload is not None:
            if payload == self.payload:
                return self
            elif payload < self.payload:
                self = self.left
            else:
                self = self.right
        self.payload = payload
        self.left = Node(None, None, None, self)
        self.right = Node(None, None, None, self)
        self.__splay()
        return self

    def __splay(self):
        while self.parent is not None:
            if self.parent.left == self: # left child
                # our right child becomes left child of parent
                self.right.parent = self.parent
                self.parent.left = self.right
                if self.parent.parent is None:
                    # left zig: /
                    parent_in_spe = None
                else:
                    # we become child of great-grandparent
                    parent_in_spe = self.parent.parent.parent
                    if parent_in_spe is not None:
                        if parent_in_spe.left == self.parent.parent:
                            parent_in_spe.left = self
                        else:
                            parent_in_spe.right = self
                    if self.parent.parent.left == self.parent: 
                        # left zig-zig:  /
                        #               /
                        # right child of parent
                        # becomes left child of grandparent
                        self.parent.right.parent = self.parent.parent
                        self.parent.parent.left = self.parent.right
                        # grandparent becomes right child of parent
                        self.parent.parent.parent = self.parent
                        self.parent.right = self.parent.parent
                    else:                         
                        # right-left zig-zag: \
                        #                     /
                        # our left child becomes right child of grandparent
                        self.left.parent = self.parent.parent
                        self.parent.parent.right = self.left
                        # grandparent becomes our left child
                        self.parent.parent.parent = self
                        self.left = self.parent.parent
                # parent becomes our right child
                self.parent.parent = self
                self.right = self.parent
                # great-grandparent that we had to save becomes our parent
                self.parent = parent_in_spe
            else: # right child
                # our left child becomes right child of parent
                self.left.parent = self.parent
                self.parent.right = self.left
                if self.parent.parent is None:
                    # right zig: \
                    parent_in_spe = None
                else:
                    # we become child of great-grandparent
                    parent_in_spe = self.parent.parent.parent
                    if parent_in_spe is not None:
                        if parent_in_spe.left == self.parent.parent:
                            parent_in_spe.left = self
                        else:
                            parent_in_spe.right = self
                    if self.parent.parent.right == self.parent: 
                        # right zig-zig: \
                        #                 \
                        # left child of parent
                        # becomes right child of grandparent
                        self.parent.left.parent = self.parent.parent
                        self.parent.parent.right = self.parent.left
                        # grandparent becomes left child of parent
                        self.parent.parent.parent = self.parent
                        self.parent.left = self.parent.parent
                    else:                         
                        # left-right zig-zag: /
                        #                     \
                        # our right child becomes left child of grandparent
                        self.right.parent = self.parent.parent
                        self.parent.parent.left = self.right
                        # grandparent becomes our right child
                        self.parent.parent.parent = self
                        self.right = self.parent.parent
                # parent becomes our left child
                self.parent.parent = self
                self.left = self.parent
                # great-grandparent that we had to save becomes our parent
                self.parent = parent_in_spe


class SplayTree:
    def __init__(self):
        self.tree = Node(None, None, None, None)

    def show(self):
        return self.tree.show()

    def insert(self, payload):
        self.tree = self.tree.insert(payload)
