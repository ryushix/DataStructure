#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>

using namespace std;
using namespace chrono;

class ArraySorter {
private:
    vector<int> arr;

public:
    ArraySorter() {
    }

    void add(int value) {
        arr.push_back(value);
    }

    void insert(int value, int index) {
        if (index < 0 || index > arr.size()) {
            cout << "Invalid index" << endl;
            return;
        }

        arr.insert(arr.begin() + index, value);
    }

    void remove(int index) {
        if (index < 0 || index >= arr.size()) {
            cout << "Invalid index" << endl;
            return;
        }

        arr.erase(arr.begin() + index);
    }

    void swap(int index1, int index2) {
        if (index1 < 0 || index1 >= arr.size() || index2 < 0 || index2 >= arr.size()) {
            cout << "Invalid indices for swapping" << endl;
            return;
        }

        int temp = arr[index1];
        arr[index1] = arr[index2];
        arr[index2] = temp;
    }

    void printArray() {
        for (int i = 0; i < arr.size(); i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void bubbleSort() {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    int get(int index) {
        if (index < 0 || index >= arr.size()) {
            throw out_of_range("Index out of range");
        }
        return arr[index];
    }

    int length() {
        return arr.size();
    }
};

class ArrayGenerator {
public:
    static void generateRandomValues(ArraySorter& arrSorter, int n) {
        srand(time(0));
        for (int i = 0; i < n; i++) {
            int randomValue = 1 + rand() % 1000;
            arrSorter.add(randomValue);
        }
    }

    static void generateReversedValues(ArraySorter& arrSorter, int n) {
        for (int i = n; i >= 1; i--) {
            arrSorter.add(i);
        }
    }
};

int main() {
    ArraySorter arrSorter;
    ArrayGenerator random, reversedValue;
    int menu;
    while (true) {
        cout << "Pilih Angka Menu yang Tersedia : \n"
        "1.Add\n"
        "2.Insert\n"
        "3.Remove\n"
        "4.Swap\n"
        "5.Get Value\n"
        "6.Generate Value\n"
        "7.Bubble Sort\n"
        "8.Selesai" << endl;
        cin >> menu;
        if (menu == 1) {
            int value;
            cout << "Masukkan nilai (0 untuk selesai): ";
            cin >> value;

            while (value != 0) {
                arrSorter.add(value);
                cout << "Masukkan nilai (0 untuk selesai): ";
                cin >> value;
            }

            cout << "Array setelah menggunakan fungsi add: ";
            arrSorter.printArray();
            cout << endl;
        } else if (menu == 2) {
            int value, index;
            cout << "Masukkan nilai yang ingin disisipkan: ";
            cin >> value;

            cout << "Masukkan indeks di mana nilai akan disisipkan: ";
            cin >> index;

            arrSorter.insert(value, index);

            cout << "Array setelah menggunakan fungsi insert: ";
            arrSorter.printArray();
            cout << endl;
        } else if (menu == 3) {
            int index;
            cout << "Masukkan indeks yang ingin dihapus: ";
            cin >> index;

            arrSorter.remove(index);

            cout << "Array setelah menggunakan fungsi remove: ";
            arrSorter.printArray();
            cout << endl;
        } else if(menu == 4) {
            int index1, index2;
            cout << "Masukkan indeks pertama untuk penukaran: ";
            cin >> index1;

            cout << "Masukkan indeks kedua untuk penukaran: ";
            cin >> index2;

            arrSorter.swap(index1, index2);

            cout << "Array setelah menggunakan fungsi swap: ";
            arrSorter.printArray();
            cout << endl;
        } else if (menu == 5) {
            int index;
            cout << "Masukkan indeks untuk mendapatkan nilai: ";
            cin >> index;

            try {
                int value = arrSorter.get(index);
                cout << "Nilai pada index " << index << ": " << value << endl;
            } catch (const out_of_range& e) {
                cerr << "Error: " << e.what() << endl;
            }
        } else if (menu == 6) {
            int generator;
            while (true) {
                cout << "Pilih Generator yang ingin digunakan : \n"
                "1.Random\n"
                "2.Reversed\n"
                "3.Keluar" << endl;
                cin >> generator;
                if (generator == 1) {
                    int numValues;
                    cout << "Masukkan banyak nilai acak yang ingin di-generate: ";
                    cin >> numValues;

                    random.generateRandomValues(arrSorter, numValues);

                    cout << "Array setelah menggunakan fungsi generateRandomValues: ";
                    arrSorter.printArray();
                    cout << endl;
                    break;
                } else if (generator == 2) {
                    int numValues;
                    cout << "Masukkan banyak nilai terurut terbalik yang ingin di-generate: ";
                    cin >> numValues;

                    reversedValue.generateReversedValues(arrSorter, numValues);

                    cout << "Array setelah menggunakan fungsi generateReversedValues: ";
                    arrSorter.printArray();
                    cout << endl;
                    break;
                } else if (generator == 3) {
                    break;
                } else {
                    cout << "invalid input" << endl;
                }
            }
        } else if(menu == 7) {
            high_resolution_clock::time_point startTime = high_resolution_clock::now();
            arrSorter.bubbleSort();
            high_resolution_clock::time_point endTime = high_resolution_clock::now();
            duration<double> timeElapsed = duration_cast<duration<double>>(endTime - startTime);

            cout << "Array setelah Bubble Sort: ";
            arrSorter.printArray();
            cout << "Waktu yang diperlukan untuk Bubble Sort: " << timeElapsed.count() << " detik" << endl;
            cout << endl;
        } else if (menu == 8) {
            break;
        } else {
            cout << "invalid input" << endl;
        }
    }
    return 0;
}
