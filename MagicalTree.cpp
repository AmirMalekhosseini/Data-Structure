#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include <stack>

using namespace std;

struct Node {
    int data;
    int depth = 0;
    Node* left;
    Node* right;
    Node* parent;

    Node(int data, Node* parent) : data(data), left(nullptr), right(nullptr), parent(parent) {}
};

Node* createNode(int data, Node* parent = nullptr) {
    return new Node(data, parent);
}

void insert(Node*& root, int value) {
    if (root == nullptr) {
        root = createNode(value);
        return;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current!= nullptr) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        } else if (value > current->data) {
            current = current->right;
        } else {
            // Value already exists in the tree, do not insert
            return;
        }
    }

    current = createNode(value, parent);
    if (value < parent->data) {
        parent->left = current;
    } else {
        parent->right = current;
    }

    current->depth = parent->depth + 1;
}

void removeNode(Node*& root, Node* node) {
    if (node == nullptr) {
        return;
    }

    if (node->left == nullptr && node->right == nullptr) {
        // Node has no children, simply remove it
        if (node->parent->left == node) {
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
        delete node;
    } else if (node->left == nullptr) {
        // Node has only right child, replace node with right child
        if (node->parent->left == node) {
            node->parent->left = node->right;
        } else {
            node->parent->right = node->right;
        }
        node->right->parent = node->parent;
        delete node;
    } else if (node->right == nullptr) {
        // Node has only left child, replace node with left child
        if (node->parent->left == node) {
            node->parent->left = node->left;
        } else {
            node->parent->right = node->left;
        }
        node->left->parent = node->parent;
        delete node;
    } else {
        // Node has both left and right children, find inorder successor
        Node* inorderSuccessor = node->right;
        while (inorderSuccessor->left!= nullptr) {
            inorderSuccessor = inorderSuccessor->left;
        }

        node->data = inorderSuccessor->data;
        removeNode(node->right, inorderSuccessor);
    }
}

void deleteNodes(Node*& root, int& count) {
    if (root == nullptr || count == 0) {
        return;
    }

    while (count > 0) {
        if (root->left == nullptr && root->right == nullptr) {
            // Root node has no children, simply return it
    
            return;
        }

        int maxDepth = 0;
        int minValue = -100001;
        Node* minNode = nullptr;

        stack<Node*> s;
        Node* current = root;

        while (true) {
            while (current!= nullptr) {
                s.push(current);
                current = current->left;
            }

            if (s.empty()) {
                break;
            }

            current = s.top();
            s.pop();

            if (current->depth > maxDepth) {
                maxDepth = current->depth;
                minValue = current->data;
                minNode = current;
            } else if (current->depth == maxDepth) {
                minValue = min(minValue, current->data);
                if (minValue == current->data) {
                    minNode = current;
                }
            }

            current = current->right;
        }

        if (minNode!= nullptr && minNode!= root) {
            removeNode(root, minNode);
            count--;
        } else if (minNode == root && count > 1) {
            // Return if the root node is the only node in the tree
            return;
        }
    }
}

void postOrderTraversal(Node* root, vector<int>& result) {
    if (root == nullptr) {
        return;
    }
    postOrderTraversal(root->left, result);
    postOrderTraversal(root->right, result);
    result.push_back(root->data);
}

int main() {
    int n;
    cin >> n;
    Node* root = createNode(0);
    for (int i = 0; i < n; i++) {
        string command;
        int data;
        cin >> command >> data;
        if (command == "grow") {
            insert(root, data);
        } else if (command == "trim") {
            int count = data;
            deleteNodes(root, count);
        }
    }
    vector<int> result;
    postOrderTraversal(root, result);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}