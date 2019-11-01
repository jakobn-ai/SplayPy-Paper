class Node:
    def __init__(self, payload, left, right):
        self.payload = payload
        self.left = left
        self.right = right

    def show(self):
        if self.payload is None:
            return "None"
        else:
            output_str = f"({self.payload}, "
            if self.left is None:
                output_str += "None, "
            else:
                output_str += f"{self.left.show()}, "
            if self.right is None:
                output_str += "None)"
            else:
                output_str += f"{self.right.show()})"
            return output_str

    def insert(self, payload):
        parent_stack = []
        while True:
            # break using return when inserted
            if self.payload is None:
                # empty tree
                self.payload = payload
                return self
            elif payload < self.payload:
                if self.left is None:
                    leaf = Node(payload, None, None)
                    self.left = leaf
                    # splay new child up, appending self to the parent stack,
                    # the child being a left child of self
                    self.left.__splay(parent_stack + [(self, True)])
                    # newly inserted node is new root after splay
                    return leaf
                else:
                    # insert to the left recursively, child is left child
                    parent_stack.append((self, True))
                    self = self.left
            elif payload == self.payload:
                # element is present (no double elements in sets), just splay up
                self.__splay(parent_stack)
                # node is root after splay
                return self
            else:
                if self.right is None:
                    leaf = Node(payload, None, None)
                    self.right = leaf
                    # splay (right) child up
                    self.right.__splay(parent_stack + [(self, False)])
                    return leaf
                else:
                    # insert on right child recursively
                    parent_stack.append((self, False))
                    self = self.right

    def __splay(self, parent_stack):
        while parent_stack != []:
            parent, is_left_child = parent_stack.pop()
            if parent_stack == []:
                # zig
                if is_left_child:
                    # left zig: /
                    parent.left = self.right
                    self.right = parent
                else:
                    # right zig: \
                    parent.right = self.left
                    self.left = parent
            else:
                # zig-zig or zig-zag
                grandparent, is_left_grandchild = parent_stack.pop()
                if is_left_child and is_left_grandchild:
                    # left zig-zig:  /
                    #               /
                    grandparent.left = parent.right
                    parent.left = self.right
                    parent.right = grandparent
                    self.right = parent
                elif not is_left_child and is_left_grandchild:
                    # left-right zig-zag: /
                    #                     \
                    parent.right = self.left
                    grandparent.left = self.right
                    self.left = parent
                    self.right = grandparent
                elif not is_left_child and not is_left_grandchild:
                    # right zig-zig: \
                    #                 \
                    grandparent.right = parent.left
                    parent.left = grandparent
                    parent.right = self.left
                    self.left = parent
                else:
                    # right-left zig-zag: \
                    #                     /
                    grandparent.right = self.left
                    parent.left = self.right
                    self.left = grandparent
                    self.right = parent


class SplayTree:
    def __init__(self):
        self.tree = Node(None, None, None)

    def show(self):
        return self.tree.show()

    def insert(self, payload):
        self.tree = self.tree.insert(payload)
