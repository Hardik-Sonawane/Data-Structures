#include <iostream>
using namespace std;

class BT {
public:
    string data;
    BT *left; 
    BT *right;
    
    BT(string x) {
        data = x;
        left = NULL;
        right = NULL;
    }

    void insert(BT *parent, BT *child) {
        if (parent->left == NULL) {
            parent->left = child;
        } else {
            BT *temp = parent->left;
            while (temp->right != NULL) {
                temp = temp->right;
            }
            temp->right = child;
        }
    }

    BT* search(BT *parent, string member) {
        if (parent == NULL) 
        return NULL;
        if (parent->data == member) 
        return parent;

        BT *found = search(parent->left, member);
        if (found) 
        return found;

        return search(parent->right, member);
    }

    void updateMember(BT* parent, string oldData, string newData) {
        if (parent == NULL) 
        return;
        if (parent->data == oldData) {
            parent->data = newData;
            cout << "Member updated!" << endl;
            return;
        }
        updateMember(parent->left, oldData, newData);
        updateMember(parent->right, oldData, newData);
    }

    bool findAncestors(BT* parent, string member) {
        if (parent == NULL)
         return false;

        if (parent->data == member) 
        return true;

        if (findAncestors(parent->left, member) || findAncestors(parent->right, member)) {
            cout << parent->data << " ";
            return true;
        }
        return false;
    }

    void findDescendants(BT* root, string member) {
        if (root == NULL)
         return;
        if (root->data == member) {
            cout << "Descendants: ";
            if (root->left == NULL) {
                cout << "None" << endl;
            } else {
                BT* temp = root->left;
                while (temp) {
                    cout << temp->data << " ";
                    temp = temp->right;
                }
                cout << endl;
            }
            return;
        }
        findDescendants(root->left, member);
        findDescendants(root->right, member);
    }

    void findSiblings(BT* root, string member) {
        if (root == NULL) 
        return;
        if (root->left && root->left->data == member) {
            BT* temp = root->left->right;
            if (!temp) {
                cout << "No siblings" << endl;
            } else {
                while (temp) {
                    cout << temp->data << " ";
                    temp = temp->right;
                }
                cout << endl;
            }
            return;
        }
        findSiblings(root->left, member);
        findSiblings(root->right, member);
    }

    void findOldest(BT* root) {
        if (root) cout << "Oldest member: " << root->data << endl;
        else cout << "No members found!" << endl;
    }

    int countMembers(BT* root) {
        if (root == NULL) return 0;
        return 1 + countMembers(root->left) + countMembers(root->right);
    }

    void printCount(BT* root) {
        cout << "Total family members: " << countMembers(root) << endl;
    }
};

int main() {
    int ch;
    string name;
    BT *root = NULL, *newnode;

    do {
        cout << "1. Insert new member\n2. Search a member\n3. Update a member\n"
             << "4. Find ancestors\n5. Find descendants\n6. Find siblings\n"
             << "7. Find oldest member\n8. Count family members\n9. Exit\n"
             << "Enter choice: ";
        cin >> ch;

        switch (ch) {
            case 1: {
                cout << "Enter member name: ";
                cin >> name;
                newnode = new BT(name);
                if (root == NULL) root = newnode;
                else {
                    cout << "Enter parent member: ";
                    string parent;
                    cin >> parent;
                    BT* parentNode = root->search(root, parent);
                    if (parentNode) root->insert(parentNode, newnode);
                    else cout << "Parent not found!" << endl;
                }
                break;
            }

            case 2: {
                cout << "Enter member to search: ";
                cin >> name;
                if (root->search(root, name))
                    cout << "Member found!" << endl;
                else
                    cout << "Member not found!" << endl;
                break;
            }

            case 3: {
                string oldName, newName;
                cout << "Enter old and new values: ";
                cin >> oldName >> newName;
                root->updateMember(root, oldName, newName);
                break;
            }

            case 4: {
                cout << "Enter member to find ancestors: ";
                cin >> name;
                if (!root->findAncestors(root, name)) cout << "No ancestors found!" << endl;
                cout << endl;
                break;
            }

            case 5: {
                cout << "Enter member to find descendants: ";
                cin >> name;
                root->findDescendants(root, name);
                break;
            }

            case 6: {
                cout << "Enter member to find siblings: ";
                cin >> name;
                root->findSiblings(root, name);
                break;
            }

            case 7:
                root->findOldest(root);
                break;

            case 8:
                root->printCount(root);
                break;
        }
    } while (ch != 9);

    return 0;
}
