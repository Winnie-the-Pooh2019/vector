#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "vector.h"

using namespace std;

vector<double> inputFile() {
    ifstream ifs("./input.txt");
    vector<double> result = {};

    if (!ifs.is_open()) {
        cout << "no input file found: expected filename \"input.txt\"" << endl;

        return {};
    }

    string str;
    while (getline(ifs, str)) {
        double number;

        try {
            number = stod(str);
        } catch (...) {
            cout << "\ninvalid input file structure\n"
            << "do u want to get filling file tutorial? YES - y; NO - n\n" << endl;

            char c;
            cin >> c;

            if (c == 'y') {
                cout << "\nevery single number gets place in its own line"
                << "there sould be no spaces or other simbols besides"
                << "digits or dots\n" << endl;
            }
        }

        result.add(number);
    }

    return result;
}

int getNumberPosition(vector<double>* array, double number) {
    for (int i = 0; i < array->capacity; i++) {
        if (array->get(i) == number)
            return i;
    }

    cout << "\nthere are no such element\n\n";

    return -2;
}

bool deleteAll(vector<double>* array, double number) {
    bool result = false;
    int c;

    while ((c = array->indexOf(number)) != -1) {
        array->del(c);
        result = true;
    }

    return result;
}

void echoArray(vector<double>* array) {
    cout << "array echo\n";
    for (int i = 0; i < array->capacity; i++) {
        cout << array->get(i) << endl;
    }
    cout << "\n";
}

int main() {
    srand(time(0));

    char input;
    double number, randNum;
    int position;
    cout << "executing program. press any button to run\n\n";
    // cin >> input;

    vector<double> array = inputFile();
    cout << "vector is filled of numbers form file\n\n";
    echoArray(&array);

    cout << "!!! task 1. to add a value to the end of the vector\n";
    randNum = ((double) rand()) / ((double) rand());
    cout << "rand number = " << randNum << endl;
    array.add(randNum);
    cout << "added random number to the end of the vector\n\n";

    cout << "input number: ";
    cin >> number;
    cout << "\n";
    array.add(number);
    cout << "number is put to the end\n\n";
    echoArray(&array);

    cout << "!!! task 2. to add a value to the begining of vector\n";
    randNum = ((double) rand()) / ((double) rand());
    cout << "rand number = " << randNum << endl;
    array.put(randNum, 0);
    cout << "added random number to the begining of the vector\n\n";

    cout << "input number: ";
    cin >> number;
    cout << "\n";
    array.put(number, 0);
    cout << "number is put to the begining\n\n";
    echoArray(&array);

    cout << "!!! task 3. to add a value to some position\n";
    cout << "input position: ";
    cin >> position;
    randNum = ((double) rand()) / ((double) rand());
    cout << "rand number = " << randNum << endl;
    array.put(randNum, position);
    cout << "random number is put to the position\n\n";

    cout << "input number: ";
    cin >> number;
    array.put(number, position);
    cout << "\nnumber is put to the position\n\n";
    echoArray(&array);

    cout << "!!! task 4. delete last element\n";
    array.del(array.capacity - 1);
    cout << "last number is deleted\n\n";
    echoArray(&array);

    cout << "!!! task 5. delete first element\n";
    array.del(0);
    cout << "first number is deleted\n\n";
    echoArray(&array);

    cout << "!!! task 6. delete some element\n";
    cout << "input position: ";
    cin >> position;
    array.del(position);
    cout << "\nnumber is deleted from position\n\n";
    echoArray(&array);

    cout << "!!! task 7. add an element after first similar\n"
    << "if there is no such elements in vector, throw exception\n";
    randNum = ((double) rand()) / ((double) rand());
    cout << "rand number = " << randNum << endl;
    if (array.put(number, getNumberPosition(&array, randNum) + 1))
        cout << "number was putted\n\n";

    cout << "input number: ";
    cin >> number;
    if (array.put(number, getNumberPosition(&array, number) + 1))
        cout << "\nnumber putted\n\n";
    echoArray(&array);

    cout << "!!! task 8. delete all elements similar to input"
    << "if there are no such values, throw an exception\n";
    cout << "input number: ";
    cin >> number;
    if (deleteAll(&array, number))
        cout << "\nall elements was successfully deleted\n\n";
    else
        cout << "\nthere is no such element\n\n";
    echoArray(&array);

    return 0;
}