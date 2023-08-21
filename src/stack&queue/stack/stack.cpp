#include <iostream>
#include <stdexcept>

using namespace std;

class Node {
private:
    int value;
    Node* next;

public:
    Node(int val) {
        value = val;
        next = nullptr;
    }

    void setNext(Node* n) {
        next = n;
    }

    Node* getNext() {
        return next;
    }

    int getValue() {
        return value;
    }
};

class Stack {
private:
    Node* top;

public:
    Stack() {
        top = nullptr;
    }

    bool hasPop() {
        return top != nullptr;
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->setNext(top);
        top = newNode;
    }

    int pop() {
        if (top == nullptr) {
            cerr << "Stack is empty." << endl;
            return -1; // You can choose to throw an exception here instead
        }

        int poppedValue = top->getValue();
        Node* temp = top;
        top = top->getNext();
        delete temp;
        return poppedValue;
    }

    void swap(int index1, int index2) {
        // Count nodes to ensure valid indices
        int count = 0;
        Node* current = top;
        while (current != nullptr) {
            count++;
            current = current->getNext();
        }

        if (index1 < 0 || index2 < 0 || index1 >= count || index2 >= count) {
            cerr << "Invalid indices." << endl;
            return;
        }

        if (index1 == index2) {
            return; // No need to swap if indices are the same
        }

        // Find nodes at index1 and index2
        Node* prev1 = nullptr;
        Node* prev2 = nullptr;
        Node* node1 = top;
        Node* node2 = top;

        for (int i = 0; i < count - index1 - 1; i++) {
            prev1 = node1;
            node1 = node1->getNext();
        }

        for (int i = 0; i < count - index2 - 1; i++) {
            prev2 = node2;
            node2 = node2->getNext();
        }

        if (prev1 != nullptr) {
            prev1->setNext(node2);
        } else {
            top = node2;
        }

        if (prev2 != nullptr) {
            prev2->setNext(node1);
        } else {
            top = node1;
        }

        Node* temp = node1->getNext();
        node1->setNext(node2->getNext());
        node2->setNext(temp);
    }

    void printStack() {
        Node* current = top;
        while (current != nullptr) {
            cout << current->getValue() << " ";
            current = current->getNext();
        }
        cout << endl;
    }

};

int main() {
    Stack stack;

    int menu;
    while (true) {
        cout << "Pilih Angka Menu yang Tersedia : \n"
        "1.hasPop\n"
        "2.Push\n"
        "3.Pop\n"
        "4.Swap\n"
        "5.Selesai" << endl;
        cin >> menu;
        if(menu == 1) {
            if (stack.hasPop()) {
                stack.printStack();
                cout << "Stack memiliki elemen yang bisa di pop." << endl;
            } else {
                cout << "Stack kosong." << endl;
            }
        } else if(menu == 2) {
            int value;
            cout << "Masukkan nilai (0 untuk selesai): ";
            cin >> value;

            while (value != 0) {
                stack.push(value);
                cout << "Masukkan nilai (0 untuk selesai): ";
                cin >> value;
            }

            cout << "Stack setelah menggunakan fungsi push: ";
            stack.printStack();
            cout << endl;
        } else if(menu == 3) {
            stack.pop();
            stack.printStack();
        } else if(menu == 4) {
            int value1;
            cout << "Masukkan indeks pertama untuk penukaran: ";
            cin >> value1;
            int value2;
            cout << "Masukkan indeks kedua untuk penukaran: ";
            cin >> value2;

            stack.swap(value1, value2);
            stack.printStack();
        } else if (menu == 5) {
            break;
        } else {
            cout << "invalid input: pilih menu yang tersedia!" << endl;
        }
    }
    return 0;
}
