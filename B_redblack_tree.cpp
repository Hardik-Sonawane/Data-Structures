#include <iostream>
using namespace std;

// ------------------- B-Tree Node and Operations -------------------

#define MAX 3

class BTreeNode {
public:
    int keys[MAX];
    BTreeNode* children[MAX + 1];
    int numKeys;
    bool isLeaf;

    BTreeNode(bool leaf) {
        isLeaf = leaf;
        numKeys = 0;
        for (int i = 0; i < MAX + 1; i++) {
            children[i] = nullptr;
        }
    }
};

class BTree {
private:
    BTreeNode* root;

    void insertNonFull(BTreeNode* node, int key) {
        int i = node->numKeys - 1;

        if (node->isLeaf) {
            while (i >= 0 && node->keys[i] > key) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
            node->numKeys++;
        } else {
            while (i >= 0 && node->keys[i] > key) {
                i--;
            }
            i++;

            if (node->children[i]->numKeys == MAX) {
                splitChild(node, i);
                if (node->keys[i] < key) {
                    i++;
                }
            }
            insertNonFull(node->children[i], key);
        }
    }

    void splitChild(BTreeNode* parent, int i) {
        BTreeNode* fullChild = parent->children[i];
        BTreeNode* newChild = new BTreeNode(fullChild->isLeaf);

        parent->children[i + 1] = newChild;
        parent->keys[i] = fullChild->keys[MAX / 2];
        parent->numKeys++;

        for (int j = 0; j < MAX / 2; j++) {
            newChild->keys[j] = fullChild->keys[j + MAX / 2 + 1];
        }

        if (!fullChild->isLeaf) {
            for (int j = 0; j < MAX / 2 + 1; j++) {
                newChild->children[j] = fullChild->children[j + MAX / 2 + 1];
            }
        }

        fullChild->numKeys = MAX / 2;
    }

    void traverse(BTreeNode* node) {
        if (node != nullptr) {
            for (int i = 0; i < node->numKeys; i++) {
                traverse(node->children[i]);
                cout << node->keys[i] << " ";
            }
            traverse(node->children[node->numKeys]);
        }
    }

public:
    BTree() {
        root = new BTreeNode(true);
    }

    void insert(int key) {
        BTreeNode* r = root;
        if (r->numKeys == MAX) {
            BTreeNode* newNode = new BTreeNode(false);
            newNode->children[0] = root;
            root = newNode;
            splitChild(root, 0);
            insertNonFull(root, key);
        } else {
            insertNonFull(root, key);
        }
    }

    void display() {
        traverse(root);
        cout << endl;
    }
};

// ------------------- Red-Black Tree Node and Operations -------------------

enum Color { RED, BLACK };

class RedBlackNode {
public:
    int data;
    Color color;
    RedBlackNode *left, *right, *parent;

    RedBlackNode(int data) {
        this->data = data;
        left = right = parent = nullptr;
        color = RED;
    }
};

class RedBlackTree {
private:
    RedBlackNode *root;

    void rotateLeft(RedBlackNode *&node) {
        RedBlackNode *newParent = node->right;
        node->right = newParent->left;
        if (newParent->left != nullptr) {
            newParent->left->parent = node;
        }
        newParent->parent = node->parent;
        if (node->parent == nullptr) {
            root = newParent;
        } else if (node == node->parent->left) {
            node->parent->left = newParent;
        } else {
            node->parent->right = newParent;
        }
        newParent->left = node;
        node->parent = newParent;
    }

    void rotateRight(RedBlackNode *&node) {
        RedBlackNode *newParent = node->left;
        node->left = newParent->right;
        if (newParent->right != nullptr) {
            newParent->right->parent = node;
        }
        newParent->parent = node->parent;
        if (node->parent == nullptr) {
            root = newParent;
        } else if (node == node->parent->right) {
            node->parent->right = newParent;
        } else {
            node->parent->left = newParent;
        }
        newParent->right = node;
        node->parent = newParent;
    }

    void fixViolations(RedBlackNode *&node) {
        while (node != root && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                RedBlackNode *uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateRight(node->parent->parent);
                }
            } else {
                RedBlackNode *uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void inorderTraversal(RedBlackNode *node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

public:
    RedBlackTree() {
        root = nullptr;
    }

    void insert(int data) {
        RedBlackNode *newNode = new RedBlackNode(data);
        if (root == nullptr) {
            root = newNode;
            root->color = BLACK;
            return;
        }

        RedBlackNode *parent = nullptr;
        RedBlackNode *current = root;
        while (current != nullptr) {
            parent = current;
            if (data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        newNode->parent = parent;
        if (data < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        fixViolations(newNode);
    }

    void display() {
        inorderTraversal(root);
        cout << endl;
    }
};

// ------------------- Main Program -------------------

int main() {
    BTree btree;
    RedBlackTree rbtree;
    int choice, key;

    while (true) {
        cout << "\nChoose Data Structure:\n1. B-Tree\n2. Red-Black Tree\n3. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 3) break;

        cout << "Choose Operation:\n1. Insert\n2. Traverse\nEnter choice: ";
        int op;
        cin >> op;

        if (choice == 1) {
            if (op == 1) {
                cout << "Enter key to insert: ";
                cin >> key;
                btree.insert(key);
            } else if (op == 2) {
                cout << "B-Tree Traversal: ";
                btree.display();
            }
        } else if (choice == 2) {
            if (op == 1) {
                cout << "Enter key to insert: ";
                cin >> key;
                rbtree.insert(key);
            } else if (op == 2) {
                cout << "Red-Black Tree Traversal: ";
                rbtree.display();
            }
        }
    }

    return 0;
}
