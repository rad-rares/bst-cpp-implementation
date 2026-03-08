#include <iostream>
#include <sstream>
using namespace std;

struct Node {
    int data;
    Node* p;
    Node* left;
    Node* right;
};

Node* root = nullptr;

Node* createNode(int data) {
    Node* node = new Node();
    node->data = data;
    node->left = node->right = node->p = nullptr;
    return node;
}

Node* insert(Node* root, int data) {
    Node* y = nullptr;
    Node* z = createNode(data);
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->p = y;
    if (y == nullptr)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    return root;
}

Node* search(Node* root, int key) {
    while (root != nullptr && root->data != key) {
        if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

Node* treeMinimum(Node* x) {
    while (x->left != nullptr)
        x = x->left;
    return x;
}

Node* treeMaximum(Node* x) {
    while (x->right != nullptr)
        x = x->right;
    return x;
}

Node* successor(Node* x) {
    if (x->right != nullptr)
        return treeMinimum(x->right);

    Node* y = x->p;
    while (y != nullptr && x == y->right) {
        x = y;
        y = y->p;
    }
    return y;
}

Node* del(Node* z) {
    Node* y;
    Node* x;

    if (z->left == nullptr || z->right == nullptr)
        y = z;
    else
        y = successor(z);

    if (y->left != nullptr)
        x = y->left;
    else
        x = y->right;

    if (x != nullptr)
        x->p = y->p;

    if (y->p == nullptr)
        root = x;
    else if (y == y->p->left)
        y->p->left = x;
    else
        y->p->right = x;

    if (y != z)
        z->data = y->data;

    return y;
}

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

int main() {
    string line;
    cout << "Enter values: ";
    getline(cin, line);
    stringstream ss(line);
    int value;
    while (ss >> value) {
        root = insert(root, value);
    }

    cout << "Tree: ";
    inorder(root);
    cout << endl;

    int choice;
    while (true) {

        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Find Minimum\n";
        cout << "4. Find Maximum\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Value to insert: ";
                cin >> value;
                root = insert(root, value);
                cout << "Tree (sorted): ";
                inorder(root);
                cout << endl;
                break;

            case 2:
                cout << "Value to delete: ";
                cin >> value;
                {
                    Node* z = search(root, value);
                    if (z != nullptr) {
                        del(z);
                        cout << "Deleted.\n";
                    } else {
                        cout << "Value not found.\n";
                    }
                    cout << "Tree (sorted): ";
                    inorder(root);
                    cout << endl;
                }
                break;

            case 3:
                if (root != nullptr)
                    cout << "Minimum: " << treeMinimum(root)->data << endl;
                else
                    cout << "Tree is empty.\n";
                break;

            case 4:
                if (root != nullptr)
                    cout << "Maximum: " << treeMaximum(root)->data << endl;
                else
                    cout << "Tree is empty.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }
}