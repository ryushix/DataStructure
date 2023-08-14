#include <iostream>
#include <array>
using namespace std;

int main() {
    array <float, 6> monthsArray;

    // float monthsArray[6] = {100,220,300,0,200,250}; -> another way to create array

    float total = 0;
    for (int i = 0; i <= monthsArray.size() ; i++) {
        cout << "Enter amount for month " << i+1 << " : ";
        cin >> monthsArray[i];
        total += monthsArray[i];
    }

    float average = total/6;
    float inTwoYears  = average * 24;

    // total, average, inTwoYears
    cout << "Total = " << total << endl;
    cout << "Average = " << average << endl;
    cout << "inTwoYears = " << inTwoYears << endl;

    return 0;
}
