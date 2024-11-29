#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class answer
{
    vector<int> numbers;
    int numbersRead = 0;
    int maxNumPos = 0;
    int minNumPos = 0;

    private:
    void findMinMaxElements() {
        for (int i = 1; i < numbersRead; i++) {
            if (numbers[i] > numbers[maxNumPos])
                maxNumPos = i;
            if (numbers[i] < numbers[minNumPos])
                minNumPos = i;
        }
        cout << "Max element is in idx: " << maxNumPos << " with value: " << numbers[maxNumPos] << endl;
        cout << "Min element is in idx: " << minNumPos << " with value: " << numbers[minNumPos] << endl;
    }

    public:
    void myReadFile() {
        int current_number;
        ifstream inputFile ("input.txt");
        if (inputFile.good()) {
            while (inputFile >> current_number)
                numbers.push_back(current_number);
            inputFile.close();
            cout << "The numbers from input.txt are: " << endl;
            numbersRead=numbers.size();
            for (int icount = 0; icount < numbersRead; icount++) {
                cout << numbers[icount] << " ";
            }
            cout << endl;
        } else
            cout << "Error in reading file!";
    }

    void swapElements() {
        int tempNum;

        findMinMaxElements();

        tempNum = numbers[numbersRead - 2];
        numbers[numbersRead - 2] = numbers[minNumPos];
        numbers[minNumPos] = tempNum;

        tempNum = numbers[numbersRead - 1];
        numbers[numbersRead - 1] = numbers[maxNumPos];
        numbers[maxNumPos] = tempNum;

        cout << "The numbers after changes are: " << endl;
        for (int i = 0; i < numbersRead; i++) {
            cout << numbers[i] << " ";
        }
        cout << endl;
    }

    void myWriteFile() {
        ofstream outputfile;
        outputfile.open ("output.txt");
        for (int icount = 0; icount < numbersRead; icount++) {
            outputfile << numbers[icount] << " ";
        }
        outputfile.close();
    }
};

main() {
    answer myanswer;
    myanswer.myReadFile();
    myanswer.swapElements();
    myanswer.myWriteFile();
}
