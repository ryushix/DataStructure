#include <iostream>
#include <stdexcept>

using namespace std;

class Node {
public:
    int Key;
    bool Red;
    Node* Parent;
    Node* Right;
    Node* Left;

public:
    Node(int key) {
        Key = key;
        Right = nullptr;
        Left = nullptr;
    }

    int getKey() {
        return Key;
    }

    void setParent(Node* parent) {
        Parent = parent;
    }

    Node* getParent() {
        return Parent;
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

    void setRed(bool red) {
        Red = red;
    }

    bool isRed() {
        return Red;
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
        newNode->setRed(true); // Set node baru menjadi merah

        if (!root) {
            root = newNode;
            root->setRed(false); // Akar selalu hitam
        } else {
            Node* current = root;
            while (true) {
                if (key > current->getKey()) {
                    if (current->getRight() == nullptr) {
                        current->setRight(newNode);
                        newNode->setParent(current);
                        break;
                    } else {
                        current = current->getRight();
                    }
                } else {
                    if (current->getLeft() == nullptr) {
                        current->setLeft(newNode);
                        newNode->setParent(current);
                        break;
                    } else {
                        current = current->getLeft();
                    }
                }
            }

            // Lakukan pengecekan dan rotasi untuk menjaga sifat Red-Black Tree
            while (newNode != root && newNode->getParent()->isRed()) {
                if (newNode->getParent() == newNode->getParent()->getParent()->getLeft()) {
                    Node* uncle = newNode->getParent()->getParent()->getRight();
                    if (uncle != nullptr && uncle->isRed()) {
                        newNode->getParent()->setRed(false);
                        uncle->setRed(false);
                        newNode->getParent()->getParent()->setRed(true);
                        newNode = newNode->getParent()->getParent();
                    } else {
                        if (newNode == newNode->getParent()->getRight()) {
                            newNode = newNode->getParent();
                            rotateLeft(newNode);
                        }
                        newNode->getParent()->setRed(false);
                        newNode->getParent()->getParent()->setRed(true);
                        rotateRight(newNode->getParent()->getParent());
                    }
                } else {
                    // Kasus simetris
                    Node* uncle = newNode->getParent()->getParent()->getLeft();
                    if (uncle != nullptr && uncle->isRed()) {
                        newNode->getParent()->setRed(false);
                        uncle->setRed(false);
                        newNode->getParent()->getParent()->setRed(true);
                        newNode = newNode->getParent()->getParent();
                    } else {
                        if (newNode == newNode->getParent()->getLeft()) {
                            newNode = newNode->getParent();
                            rotateRight(newNode);
                        }
                        newNode->getParent()->setRed(false);
                        newNode->getParent()->getParent()->setRed(true);
                        rotateLeft(newNode->getParent()->getParent());
                    }
                }
            }
        }

        root->setRed(false); // Pastikan akar tetap hitam
        return true;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->getLeft() != nullptr) {
            current = current->getLeft();
        }
        return current;
    }

    bool remove(int key) {
        if (!isExist(key)) {
            cout << "Error: Key not found" << endl;
            return false;
        }

        root = remove(root, key);

        if (root != nullptr) {
            root->setRed(false); // Pastikan akar tetap hitam setelah menghapus node
        }

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

        // Lakukan pengecekan dan rotasi untuk menjaga Red-Black Tree
        if (node->isRed()) {
            return node; // Tidak perlu tindakan jika node itu merah
        }

        if (node->getLeft() != nullptr && node->getLeft()->isRed()) {
            if (node == node->getParent()->getLeft()) {
                Node* sibling = node->getParent()->getRight();
                if (sibling != nullptr && !sibling->isRed()) {
                    // Kasus 1: Node hitam dengan sibling hitam
                    sibling->setRed(true);
                    node->getParent()->setRed(false);
                    rotateRight(node->getParent());
                    sibling = node->getParent()->getRight();
                }
                if ((sibling->getLeft() == nullptr || !sibling->getLeft()->isRed()) &&
                    (sibling->getRight() == nullptr || !sibling->getRight()->isRed())) {
                    // Kasus 2: Node hitam dengan sibling merah
                    sibling->setRed(true);
                    node = node->getParent();
                } else {
                    if (sibling->getRight() == nullptr || !sibling->getRight()->isRed()) {
                        // Kasus 3: Node hitam dengan sibling hitam-merah
                        sibling->getLeft()->setRed(false);
                        sibling->setRed(true);
                        rotateRight(sibling);
                        sibling = node->getParent()->getRight();
                    }
                    // Kasus 4: Node hitam dengan sibling merah-merah
                    sibling->setRed(node->getParent()->isRed());
                    node->getParent()->setRed(false);
                    sibling->getRight()->setRed(false);
                    rotateLeft(node->getParent());
                    node = root; // Selesai
                }
            }
        } else {
            if (node->getRight() != nullptr && node->getRight()->isRed()) {
                if (node == node->getParent()->getRight()) {
                    Node* sibling = node->getParent()->getLeft();
                    if (sibling != nullptr && !sibling->isRed()) {
                        // Kasus 1: Node hitam dengan sibling hitam
                        sibling->setRed(true);
                        node->getParent()->setRed(false);
                        rotateLeft(node->getParent());
                        sibling = node->getParent()->getLeft();
                    }
                    if ((sibling->getRight() == nullptr || !sibling->getRight()->isRed()) &&
                        (sibling->getLeft() == nullptr || !sibling->getLeft()->isRed())) {
                        // Kasus 2: Node hitam dengan sibling merah
                        sibling->setRed(true);
                        node = node->getParent();
                    } else {
                        if (sibling->getLeft() == nullptr || !sibling->getLeft()->isRed()) {
                            // Kasus 3: Node hitam dengan sibling hitam-merah
                            sibling->getRight()->setRed(false);
                            sibling->setRed(true);
                            rotateLeft(sibling);
                            sibling = node->getParent()->getLeft();
                        }
                        // Kasus 4: Node hitam dengan sibling merah-merah
                        sibling->setRed(node->getParent()->isRed());
                        node->getParent()->setRed(false);
                        sibling->getLeft()->setRed(false);
                        rotateRight(node->getParent());
                        node = root; // Selesai
                    }
                }
            }
        }

        return node;
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
            if (ptr->isRed()) {
                cout << "\033[1;31m" << ptr->getKey() << "\033[0m"; // Merah
            } else {
                cout << ptr->getKey(); // Hitam
            }
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

    void rotateRight(Node* node) {
        Node* newParent = node->getLeft();
        if (node->getParent() != nullptr) {
            if (node == node->getParent()->getLeft()) {
                node->getParent()->setLeft(newParent);
            } else {
                node->getParent()->setRight(newParent);
            }
        } else {
            root = newParent;
        }
        newParent->setParent(node->getParent());
        node->setLeft(newParent->getRight());
        if (newParent->getRight() != nullptr) {
            newParent->getRight()->setParent(node);
        }
        newParent->setRight(node);
        node->setParent(newParent);
    }

    void rotateLeft(Node* node) {
        Node* newParent = node->getRight();
        if (node->getParent() != nullptr) {
            if (node == node->getParent()->getLeft()) {
                node->getParent()->setLeft(newParent);
            } else {
                node->getParent()->setRight(newParent);
            }
        } else {
            root = newParent;
        }
        newParent->setParent(node->getParent());
        node->setRight(newParent->getLeft());
        if (newParent->getLeft() != nullptr) {
            newParent->getLeft()->setParent(node);
        }
        newParent->setLeft(node);
        node->setParent(newParent);
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

