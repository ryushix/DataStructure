#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void generateRandomArray(int array[], int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1001; // Menghilangkan std::
    }
}

void selectionSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1 ; j < size; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        int temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;
    }
}

int main() {
    int size;
    cout << "Masukkan ukuran array: ";
    cin >> size;

    int* myArray = new int[size];

    generateRandomArray(myArray, size);

    cout << "Isi array sebelum diurutkan: ";
    for (int i = 0; i < size; i++) {
        cout << myArray[i] << " ";
    }
    cout << endl;

    selectionSort(myArray, size);

    cout << "Isi array setelah diurutkan: ";
    for (int i = 0; i < size; i++) {
        cout << myArray[i] << " ";
    }
    cout << endl;

    delete[] myArray;

    return 0;
}
