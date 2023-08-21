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

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    bool hasPop() {
        return front != nullptr;
    }

    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {  // Jika antrian kosong, front dan rear sama
            front = newNode;
            rear = newNode;
        } else {
            rear->setNext(newNode);
            rear = newNode;
        }
    }

    int dequeue() {
        if (front == nullptr) {
            cerr << "Queue is empty." << endl;
            return -1;
        }

        int dequeuedValue = front->getValue();
        Node* temp = front;
        front = front->getNext();
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return dequeuedValue;
    }

    void swap(int index1, int index2) {
        int count = 0;
        Node* current = front;
        while (current != nullptr) {
            count++;
            current = current->getNext();
        }

        if (index1 < 0 || index2 < 0 || index1 >= count || index2 >= count) {
            cerr << "Invalid indices." << endl;
            return;
        }

        if (index1 == index2) {
            return;
        }

        Node* prev1 = nullptr;
        Node* prev2 = nullptr;
        Node* node1 = front;
        Node* node2 = front;

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
            front = node2;
        }

        if (prev2 != nullptr) {
            prev2->setNext(node1);
        } else {
            front = node1;
        }

        Node* temp = node1->getNext();
        node1->setNext(node2->getNext());
        node2->setNext(temp);
    }

    void printQueue() {
        Node* current = front;
        while (current != nullptr) {
            cout << current->getValue() << " ";
            current = current->getNext();
        }
        cout << endl;
    }
};

int main() {
    Queue queue;

    int menu;
    while (true) {
        cout << "Pilih Angka Menu yang Tersedia : \n"
        "1.hasPop\n"
        "2.Enqueue\n"
        "3.Dequeue\n"
        "4.Swap\n"
        "5.Selesai" << endl;
        cin >> menu;
        if(menu == 1) {
            if (queue.hasPop()) {
                queue.printQueue();
                cout << "Queue memiliki elemen yang bisa di pop." << endl;
            } else {
                cout << "Queue kosong." << endl;
            }
            cout << endl;
        } else if(menu == 2) {
            int value;
            cout << "Masukkan nilai (0 untuk selesai): ";
            cin >> value;

            while (value != 0) {
                queue.enqueue(value);
                cout << "Masukkan nilai (0 untuk selesai): ";
                cin >> value;
            }

            cout << "Queue setelah menggunakan fungsi enqueue: ";
            queue.printQueue();
            cout << endl;
        } else if(menu == 3) {
            queue.dequeue();

            cout << "Queue setelah menggunakan fungsi dequeue: ";
            queue.printQueue();
            cout << endl;
        } else if(menu == 4) {
            int value1;
            cout << "Masukkan indeks pertama untuk penukaran: ";
            cin >> value1;
            int value2;
            cout << "Masukkan indeks kedua untuk penukaran: ";
            cin >> value2;
            queue.swap(value1, value2);

            cout << "Queue setelah menggunakan fungsi swap: ";
            queue.printQueue();
            cout << endl;
        } else if (menu == 5) {
            break;
        } else {
            cout << "invalid input: pilih menu yang tersedia!" << endl;
        }
    }
    return 0;
}
