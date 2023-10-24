#include <iostream>
#include <stdexcept>

using namespace std;

class Node {
public:
    int Key;
    Node* Right;
    Node* Left;

public:
    Node(int key) {
        Key = key;
        Right = nullptr;
        Left = nullptr;
    }

    void setRight(Node* right) {
        Right = right;
    }

    Node* getRight() {
        return Right;
    }

    void setLeft(Node* left) {
        Left = left;
    }

    Node* getLeft() {
        return Left;
    }

    int getKey() {
        return Key;
    }

    Node* getRoot() {
        return this;
    }
};

class binarySearchTree {
private:
    Node* root;

public:
    binarySearchTree() {
        root = nullptr;
    }

    void Display() {
        Display(0, root);
    }

    bool isExist(int key) {
        return isExist(root, key);
    }

    bool isExist(Node* node, int key) {
        if (node == nullptr) {
            return false;
        }
        if (key == node->getKey()) {
            return true;
        } else if (key < node->getKey()) {
            return isExist(node->getLeft(), key);
        } else {
            return isExist(node->getRight(), key);
        }
    }

    bool add(int key) {
        if (isExist(key)) {
            cout << "Error: Key already exists" << endl;
            return false;
        }
        Node* newNode = new Node(key);
        if (!root) {
            root = newNode;
        } else {
            Node* current = root;
            while (true) {
                if (key > current->getKey()) {
                    if (current->getRight() == nullptr) {
                        current->setRight(newNode);
                        break;
                    } else {
                        current = current->getRight();
                    }
                } else {
                    if (current->getLeft() == nullptr) {
                        current->setLeft(newNode);
                        break;
                    } else {
                        current = current->getLeft();
                    }
                }
            }
        }
        return true;
    }

    bool remove(int key) {
        root = remove(root, key);
        return true;
    }

    Node* remove(Node* node, int key) {
        if (node == nullptr) {
            return node;
        }
        if (key < node->getKey()) {
            node->setLeft(remove(node->getLeft(), key));
        } else if (key > node->getKey()) {
            node->setRight(remove(node->getRight(), key));
        } else {
            if (node->getLeft() == nullptr) {
                Node* temp = node->getRight();
                delete node;
                return temp;
            } else if (node->getRight() == nullptr) {
                Node* temp = node->getLeft();
                delete node;
                return temp;
            }
            Node* temp = minValueNode(node->getRight());
            node->Key = temp->getKey();
            node->setRight(remove(node->getRight(), temp->getKey()));
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->getLeft() != nullptr) {
            current = current->getLeft();
        }
        return current;
    }

    Node* getRoot() {
        return root;
    }

    void Display(int level, Node* ptr) {
        int i;
        if (ptr != nullptr) {
            Display(level + 1, ptr->getRight());
            cout << endl;
            if (ptr == root) {
                cout << "Root -> ";
            }
            for (i = 0; i < level && ptr != root; i++) {
                cout << "        ";
            }
            cout << ptr->getKey();
            Display(level + 1, ptr->getLeft());
        }
    }

    void printPreorder(Node* node) {
        if (node != nullptr) {
            cout << node->Key << " ";
            printPreorder(node->Left);
            printPreorder(node->Right);
        }
    }

    void printInorder(Node* node) {
        if (node != nullptr) {
            printInorder(node->Left);
            cout << node->Key << " ";
            printInorder(node->Right);
        }
    }

    void printPostorder(Node* node) {
        if (node != nullptr) {
            printPostorder(node->Left);
            printPostorder(node->Right);
            cout << node->Key << " ";
        }
    }

    void printPreorder() {
        printPreorder(root);
        cout << endl;
    }

    void printInorder() {
        printInorder(root);
        cout << endl;
    }

    void printPostorder() {
        printPostorder(root);
        cout << endl;
    }

};

int main() {
    binarySearchTree bst;
    int menu, key;

    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Tambahkan kunci" << endl;
        cout << "2. Hapus kunci" << endl;
        cout << "3. Cek keberadaan kunci" << endl;
        cout << "4. Print preOrder" << endl;
        cout << "5. Print inOrder" << endl;
        cout << "6. Print postOrder" << endl;
        cout << "7. Selesai" << endl;
        cout << "Pilihan: ";
        cin >> menu;

        switch (menu) {
            case 1:
                cout << "Masukkan kunci yang akan ditambahkan: ";
                cin >> key;
                if (bst.add(key)) {
                    cout << "Kunci " << key << " berhasil ditambahkan." << endl;
                }
                bst.Display();
                break;
            case 2:
                cout << "Masukkan kunci yang akan dihapus: ";
                cin >> key;
                if (bst.remove(key)) {
                    cout << "Kunci " << key << " berhasil dihapus." << endl;
                }
                bst.Display();
                break;
            case 3:
                cout << "Masukkan kunci yang akan dicek: ";
                cin >> key;
                if (bst.isExist(key)) {
                    cout << "Kunci " << key << " ditemukan." << endl;
                } else {
                    cout << "Kunci " << key << " tidak ditemukan." << endl;
                }
                break;
            case 4:
                cout << "Preorder Traversal: ";
                bst.printPreorder();
                break;
            case 5:
                cout << "Inorder Traversal: ";
                bst.printInorder();
                break;
            case 6:
                cout << "Postorder Traversal: ";
                bst.printPostorder();
                break;
            case 7:
                cout << "Terima kasih, keluar dari program." << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }

    return 0;
}

