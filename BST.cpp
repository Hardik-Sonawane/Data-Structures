#include <iostream>
using namespace std;

class BST {
public:
    int salary;
    string name;
    BST *left;
    BST *right;

    BST(int s, string n) {
        salary = s;
        name = n;
        left = NULL;
        right = NULL;
    }

    BST *insert(BST *root, int s, string n) {
        if (root == NULL)
         return new BST(s, n);
        if (s < root->salary) 
        root->left = insert(root->left, s, n);
        else root->right = insert(root->right, s, n);
        return root;
    }

    BST *search(BST *root, int s) {
        if (root == NULL || root->salary == s) 
        return root;
        if (s < root->salary) 
        return search(root->left,s);
        return search(root->right, s);
    }

    void update(BST*& root, int OldSalary, int NewSalary,string name) {
       root = deleteNode(root, OldSalary);
       root = insert(root,NewSalary,name);
       cout<<"salary Updated ";
    }

    void display(BST* root) {
        if (root) {
         
            display(root->left);
            cout << root->name << "- " << root->salary << endl;
            display(root->right);
           
        }
    }

    BST *findMin(BST *root) {
        while (root && root->left) 
        root = root->left;
        return root;
    }

    BST *findMax(BST *root) {
        while (root && root->right) 
        root = root->right;
        return root;
    }

    int count(BST *root) {
        if (!root) 
        return 0;
        return 1 + count(root->left) + count(root->right);
    }

    int sum(BST *root) {
        if (!root)
         return 0;
        return root->salary + sum(root->left) + sum(root->right);
    }

    void averageSalary(BST* root) {
        int total = count(root);
        if (total == 0) {
            cout << "No employees found\n";
        } else {
            cout << "Average Salary: " << sum(root) / total << endl;
        }
    }

    BST *deleteNode(BST *root, int s) {
        if (root == NULL) 
        return root;

        if (s < root->salary)
         root->left = deleteNode(root->left, s);
        else if (s > root->salary) 
        root->right = deleteNode(root->right, s);
        else {
            if (root->left == NULL) {
                BST *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL) {
                BST *temp = root->left;
                delete root;
                return temp;
            }
            BST *temp = findMin(root->right);
            root->salary = temp->salary;
            root->name = temp->name;
            root->right = deleteNode(root->right, temp->salary);
        }
        return root;
    }
};

int main() {
    BST *root = NULL;
    BST bst(0,"Root");  

    int ch, salary;
    string name;

    do {
        cout << "1. Insert Employee\n2.Search Employee\n3. Update Salary\n4. Display Employees\n";
        cout << "5. Delete Employee\n6. Minimum Salary\n7. Maximum Salary\n8. Average Salary\n9. Total Employees\n10. Exit\nEnter choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "Enter name and salary: ";
                cin >> name >> salary;
                root = bst.insert(root, salary, name);
                break;
            case 2:
                cout << "Enter salary to search: ";
                cin >> salary;
                if (bst.search(root, salary)) cout << "Employee found!\n";
                else cout << "Employee not found!\n";
                break;
            case 3:
                int NewSalary;
                cout << "Enter old salary and new salary: ";
                cin >> salary >> NewSalary;
                {
                BST *emp = bst.search(root,salary);
                if (emp){
                string empName = emp->name;
                bst.update(root,salary,NewSalary,name);
                }
                else{
                cout<<"Not found";
                }
                }
                break;
            case 4:
                cout << "Employee List:\n";
                bst.display(root);
                break;
            case 5:
                cout << "Enter salary to delete: ";
                cin >> salary;
                root = bst.deleteNode(root, salary);
                cout << "Employee deleted \n";
                break;
            case 6:
                cout << "Minimum Salary is: " << bst.findMin(root)->salary << endl;
                break;
            case 7:
                cout << "Maximum Salary is : " << bst.findMax(root)->salary << endl;
                break;
            case 8:
                bst.averageSalary(root);
                break;
            case 9:
                cout << "Total Employees: " << bst.count(root) << endl;
                break;
        }
    } while (ch != 10);

    return 0;
}
