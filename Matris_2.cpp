#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct TrieNode {
    static const int ALPHABET_SIZE = 21; // Assuming the matrix rows are numbers within the range 0-20

    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
    int row;

    TrieNode() : isEndOfWord(false), row(-1) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }
};

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class mylist {
public:
    Node* head;
    Node* tail;

public:
    mylist() : head(nullptr), tail(nullptr) {}

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

};

class Trie {
private:
    TrieNode* root;
    int* duplicateRows;
    int duplicateRowsSize;

public:
    Trie() {
        root = new TrieNode();
        duplicateRows = new int[1000000];
        duplicateRowsSize = 0;
    }

    ~Trie() {
        delete[] duplicateRows;
    }

    void insert(const string& key, int row) {
        TrieNode* node = root;
        bool isDuplicate = false;

        mylist numbersList;

        stringstream ss(key);
        int num;
        while (ss >> num) {
            numbersList.push_back(num);
        }

        Node* current = numbersList.head;
        while (current != nullptr) {
            int index = current->data;
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
            current = current->next;
        }

        if (node->isEndOfWord) {
            isDuplicate = true;
        }

        node->isEndOfWord = true;
        node->row = row;

        if (isDuplicate) {
            duplicateRows[duplicateRowsSize++] = row + 1;
        }
    }

    int* getDuplicateRows() {
        return duplicateRows;
    }

    int getDuplicateRowsSize() {
        return duplicateRowsSize;
    }
};

int main() {
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    string** matrix = new string*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new string[m];
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }

    Trie trie;
    for (int i = 0; i < n; i++) {
        string rowString = "";
        for (int j = 0; j < m; j++) {
            rowString += matrix[i][j] + " "; // Add a space after each element
        }
        trie.insert(rowString, i);
    }

    int* duplicateRows = trie.getDuplicateRows();
    int duplicateRowsSize = trie.getDuplicateRowsSize();
    for (int i = 0; i < duplicateRowsSize; i++) {
        cout << duplicateRows[i] << " ";
  }
  cout << endl;

  // Free the dynamically allocated memory
  for (int i = 0; i < n; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;

  return 0;
}