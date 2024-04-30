class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
        self.parent = None 
        self.color = "red"


class RedBlackTree:
    def __init__(self):
        self.root = None

    def insert(self, value):
        new_node = Node(value)
        if self.root is None:
            self.root = new_node
            self.root.color = "black"
        else:
            parent = None
            current = self.root
            while current is not None:
                parent = current
                if value < current.value:
                    current = current.left
                else:
                    current = current.right
            new_node.parent = parent
            if value < parent.value:
                parent.left = new_node
            else:
                parent.right = new_node

            new_node.left = None
            new_node.left = None
            new_node.color = "red"
            
            if new_node.parent is not None:

                self._fix_insert(new_node)

    def _fix_insert(self, node):

        while node.parent.color == "red":
            if node.parent == node.parent.parent.left:
                uncle = node.parent.parent.right
                if uncle is not None and uncle.color == "red":
                    node.parent.color = "black"
                    uncle.color = "black"
                    node.parent.parent.color = "red"
                    node = node.parent.parent
                else:
                    if node == node.parent.right:
                        node = node.parent
                        self._left_rotate(node)
                    node.parent.color = "black"
                    node.parent.parent.color = "red"
                    self._right_rotate(node.parent.parent)
            else:
                uncle = node.parent.parent.left
                if uncle is not None and uncle.color == "red":
                    node.parent.color = "black"
                    uncle.color = "black"
                    node.parent.parent.color = "red"
                    node = node.parent.parent
                else:
                    if node == node.parent.left:
                        node = node.parent
                        self._right_rotate(node)
                    node.parent.color = "black"
                    node.parent.parent.color = "red"
                    self._left_rotate(node.parent.parent)
                    
            if node.parent is None:
                break
        self.root.color = "black"

    def _left_rotate(self, node):
        y = node.right
        node.right = y.left
        if y.left is not None:
            y.left.parent = node
        y.parent = node.parent
        if node.parent is None:
            self.root = y
        elif node == node.parent.left:
            node.parent.left = y
        else:
            node.parent.right = y
        y.left = node
        node.parent = y

    def _right_rotate(self, node):
        y = node.left
        node.left = y.right
        if y.right is not None:
            y.right.parent = node
        y.parent = node.parent
        if node.parent is None:
            self.root = y
        elif node == node.parent.left:
            node.parent.left = y
        else:
            node.parent.right = y
        y.right = node
        node.parent = y

    def sum_red_nodes(self):
        return self._sum_red_nodes_recursive(self.root)

    def _sum_red_nodes_recursive(self, node):
        if node is None:
            return 0
        if node.color == "red":
            return node.value + self._sum_red_nodes_recursive(node.left) + self._sum_red_nodes_recursive(node.right)
        else:
            return self._sum_red_nodes_recursive(node.left) + self._sum_red_nodes_recursive(node.right)


n = int(input())
values = list(map(int, input().split()))
tree = RedBlackTree()

for value in values:
    tree.insert(value)
    print(tree.sum_red_nodes())
