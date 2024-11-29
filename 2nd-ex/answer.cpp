#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class answer
{
    vector<int> heap;

    private:
    void printHeap() {
        for (int icount = 1; icount < heap.size(); icount++) {
            cout << heap[icount] << " ";
        }
        cout << endl;
    }

    int readUserInput() {
        int userInput = -1;

        cout << "Please input a number to insert in the heap: ";
        cin >> userInput;
        cout << endl;
        if (!cin) {
            cout << "That isn't a valid integer. Issues will occur." << endl;
        } else
            cout << "You entered: " << userInput << endl;

        return userInput;
    }

    int myHeapifyDown(int i) {
        int j;

        if (2*i > heap.size())
            return i;
        else if (2*i == heap.size())
            j=2*i;
        else {
            int left = 2*i;
            int right = 2*i + 1;
            heap[left] <= heap[right] ? j=left:j=right;
        }

        if (heap[j]<heap[i]){
            cout << "Moving element " << heap[i] << " from position " << i << " to position " << j << endl;
            swap(heap[j],heap[i]);
            printHeap();
            return myHeapifyDown(j);
        }
        return i;
    }

    void myHeapifyUp(int index) {
        cout << "Running Heapify-Up..." << endl;
        while (index > 1) {
            int parentIndex = index / 2;

            if (heap[index] >= heap[parentIndex])
                break;
            else {
                cout << "Moving element " << heap[index] << " from position " << index << " to position " << parentIndex << endl;
                swap(heap[index], heap[parentIndex]);
            }
            index = parentIndex;
        }
        cout << "Final vector:" << endl;
        printHeap();
    }

    public:
    void myReadHeap() {
        int current_number;
        ifstream inputFile ("Heap.txt");
        heap.push_back(-1);
        if (inputFile.good()) {
            while (inputFile >> current_number)
                heap.push_back(current_number);
            inputFile.close();
            cout << "The vector from Heap.txt is: " << endl;
            printHeap();
        } else
            cout << "Error in reading file!";
    }

    void extractHeapRoot() {
        if (heap.empty()) {
            cout << "The heap is empty" << endl;
            return;
        }

        cout << "1) Extract root (min element) of the heap" << endl;

        int minKey = heap[1];
        swap(heap[1],heap.back());
        heap.pop_back();

        cout << "Running Heapify-Down..." << endl;
        printHeap();
        myHeapifyDown(1);

        cout << "The root is: " << minKey << endl;
    }

    void pushHeapElem() {
        int userInput;

        cout << "2) Push element to heap" << endl;
        userInput = readUserInput();

        heap.push_back(userInput);
        myHeapifyUp(heap.size() - 1);
    }

    void myWriteHeap() {
        ofstream outputfile;
        outputfile.open ("output.txt");
        for (int icount = 1; icount < heap.size(); icount++) {
            outputfile << heap[icount] << " ";
        }
        outputfile.close();
    }
};

int main() {
    answer myanswer;
    myanswer.myReadHeap();
    myanswer.extractHeapRoot();
    myanswer.pushHeapElem();
    myanswer.myWriteHeap();
}
