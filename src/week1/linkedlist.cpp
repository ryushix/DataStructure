#include <iostream>
using namespace std;

class Node {
public:
    int Value;
    Node* Next;

    Node(int value) {
        Value = value;
        Next = nullptr;
    }

    void setNext(Node* next) {
        Next = next;
    }

    Node* getNext() {
        return Next;
    }

    int getValue() {
        return Value;
    }
};

class LinkedList {
private:
    Node* first;

public:
    LinkedList() {
        first = nullptr;
    }

    void add(int value) {
        Node* newNode = new Node(value);
        if (!first) {
            first = newNode;
        } else {
            Node* current = first;
            while (current->getNext()) {
                current = current->getNext();
            }
            current->setNext(newNode);
        }
    }

    void insert(int value, int index) {
        if (first == nullptr) {
            cout << "The given previous node cannot be NULL";
            return;
        }

        Node* newNode = new Node(value);

        if (index == 0) {
            newNode->setNext(first);
            first = newNode;
            return;
        }

        Node* current = first;
        for (int i = 0; i < index - 1 && current != nullptr; i++) {
            current = current->getNext();
        }

        if (current == nullptr) {
            cout << "Index out of range";
            return;
        }

        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }


    void remove(int index) {
        if (index < 0) {
            cout << "Invalid index";
            return;
        }

        if (index == 0) {
            if (first) {
                Node* temp = first;
                first = first->getNext();
                delete temp;
                return;
            }
        }

        Node* current = first;
        for (int i = 0; current != nullptr && i < index - 1; i++) {
            current = current->getNext();
        }

        if (current == nullptr || current->getNext() == nullptr) {
            cout << "Index out of range";
            return;
        }

        Node* temp = current->getNext();
        current->setNext(temp->getNext());
        delete temp;
    }

    void swap(int index1, int index2) {
        if (index1 == index2) {
            return;
        }

        Node* prev1 = nullptr;
        Node* curr1 = first;
        for (int i = 0; curr1 != nullptr && i < index1; i++) {
            prev1 = curr1;
            curr1 = curr1->getNext();
        }

        Node* prev2 = nullptr;
        Node* curr2 = first;
        for (int i = 0; curr2 != nullptr && i < index2; i++) {
            prev2 = curr2;
            curr2 = curr2->getNext();
        }

        if (curr1 == nullptr || curr2 == nullptr) {
            cout << "Invalid indices for swapping";
            return;
        }

        if (prev1) {
            prev1->setNext(curr2);
        } else {
            first = curr2;
        }

        if (prev2) {
            prev2->setNext(curr1);
        } else {
            first = curr1;
        }

        Node* temp = curr1->getNext();
        curr1->setNext(curr2->getNext());
        curr2->setNext(temp);
    }

    void printList() {
        Node* current = first;
        while (current) {
            cout << current->getValue() << " ";
            current = current->getNext();
        }
        cout << endl;
    }

    int get(int index) {
        Node* current = first;
        int currentIndex = 0;

        while (current) {
            if (currentIndex == index) {
                return current->getValue();
            }

            current = current->getNext();
            currentIndex++;
        }
        throw out_of_range("Anda keluar dari batas index");
    }

};

int main() {
    LinkedList list;
    list.add(1);
    list.add(2);
    list.add(3);

    cout << "Linked List: ";
    list.printList();

    list.insert(3,1);

    cout << "Linked List: ";
    list.printList();

    list.remove(3);

    cout << "Linked List: ";
    list.printList();

    int cari;
    cout << "Cari nilai : ";
    cin >> cari;

    int valueAtIndex = list.get(cari);
    cout << "Nilai di index ke-" << list.get(cari) << " adalah : " << valueAtIndex << endl;
    return 0;
}
