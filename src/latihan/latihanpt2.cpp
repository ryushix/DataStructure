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
        int minValue = i;
        for (int j = i + 1 ; j < size; j++) {
            if (array[j] < array[minValue]) {
                int minValue = array[j];
            }
        }
        int temp = array[i];
        array[i] = array[minValue];
        array[minValue] = temp;
    }
}
