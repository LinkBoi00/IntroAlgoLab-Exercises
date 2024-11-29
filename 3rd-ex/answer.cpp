#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class answer
{
    vector<int> vector1;
    vector<int> vector2;
    vector<int> mergedvector;
    int vector1_size = 0;
    int vector2_size = 0;
    int mergedvector_size = 0;

    public:
    answer() {
        readVector("Vector1.txt", vector1, vector1_size);
        readVector("Vector2.txt", vector2, vector2_size);
    }

    void mergeSortedVectors() {
        int i = vector1_size - 1, j = vector2_size - 1;

        while ((i >= 0) && (j >= 0)) {
            if (vector1[i] <= vector2[j]) {
                mergedvector.push_back(vector1[i]);
                i--;
                printStats(i, vector1, "Vector 1");
            } else {
                mergedvector.push_back(vector2[j]);
                j--;
                printStats(j, vector2, "Vector 2");
            }
        }

        while (i >= 0) {
            mergedvector.push_back(vector1[i]);
            i--;
            printStats(i, vector1, "Vector 1");
        }

        while (j >= 0) {
            mergedvector.push_back(vector2[j]);
            j--;
            printStats(j, vector2, "Vector 2");
        }

        mergedvector_size = mergedvector.size();

        printMergedVector();
    }

    void doBinarySearch() {
        int inputNum = 0;
        bool numFound = false;

        cout << "Input a number for binary search: ";
        cin >> inputNum;

        numFound = binarySearch(inputNum, 0, mergedvector_size - 1);
        cout << "Binary search function result: " << numFound << endl;
        cout << "The number " << (numFound ? "exists." : "doesn't exist") << endl;
    }

    private:
    void printStats(int iter, vector<int> vec, string vecName) {
        float previousPercentage = (float)(iter+2) / (vec.size()-1);
        float currentPercentage = (float) (iter+1) / (vec.size()-1);

        if ((currentPercentage < 0.5) && (previousPercentage >= 0.5)) {
            cout << "Element with index: " << iter + 1 << " and value: " << vec[iter + 1] << " of vector: " << vecName << endl;
            float percentage = (float) mergedvector.size() / (vector1.size() + vector2.size());
            cout << "Percentage of mergedvector: " << percentage << endl;
            cout << endl;
        }
    }

    void printMergedVector() {
        cout << "Merged Vector: " << endl;
        for (int icount = 0; icount < mergedvector_size; icount++) {
            cout << mergedvector[icount] << " ";
        }
        cout << endl;
    }

    void readVector(string filename, vector<int>& vec, int& vectorSize) {
        int current_number;
        ifstream inputFile(filename);

        if (inputFile.good()) {
            while (inputFile >> current_number)
                vec.push_back(current_number);
            inputFile.close();

            cout << "The numbers from " << filename << " are: " << endl;
            vectorSize = vec.size();
            for (int icount = 0; icount < vectorSize; icount++) {
                cout << vec[icount] << " ";
            }
            cout << endl;
            cout << "Size of vector from " << filename << " is: " << vectorSize << endl;
            cout << endl;
        } else {
            cout << "Error in reading file " << filename << "!" << endl;
        }
    }

    bool binarySearch(int target, int imin, int imax) {
        bool found;

        if (imin <= imax) {
            int imid = (imin + imax) / 2;

            if (mergedvector[imid] == target) {
                return true;
            } else if (mergedvector[imid] > target) {
                found = binarySearch(target, imin, imid-1);
            } else if (mergedvector[imid] < target) {
                found = binarySearch(target, imid+1, imax);
            }
            return found;
        } else
            return false;
    }

};

int main() {
    answer myanswer;
    myanswer.mergeSortedVectors();
    myanswer.doBinarySearch();

    return 0;
}
