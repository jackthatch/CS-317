#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

void quickSort(int start, int end, double arr[], int &comparison_count);
int partition(int start, int end, double arr[], int &comparison_count);
bool LESS(double a, double b, int &comparison_count);
void output(double arr[], int &comparison_count, int arrLen);
void medianOfThree(double arr[], int start, int end, int &comparison_count);

int main(){

    string path =  "input.txt";

    ifstream file(path);

    if (!file.is_open()) {
        cout << "Error opening file: " << path << endl;
        return 0;
    }

    string line;

    getline(file, line);
    int arrLen = stoi(line);        //get length of array from first line of file
    double arr[arrLen];
    int i  = 0;

    while (getline(file, line)) {       //load lines 2-n into array
        arr[i] = stod(line);
        i++;
    }

    int comparison_count = 0;
    quickSort(0, arrLen - 1, arr, comparison_count);
    output(arr, comparison_count, arrLen);

    for (int i = arrLen - 100; i < arrLen; i++) {      //print array contents for testing purposes
        cout << "Index: " << i << " == " << arr[i] << endl;
    }
    cout << "Comparison Count = " << comparison_count << endl;

    file.close();
    return 1;
}

void quickSort(int start, int end, double arr[], int &comparison_count) {
    if (end <= start) {
        return;
    }

    int pivot = partition(start, end, arr, comparison_count);
    quickSort(start, pivot - 1, arr, comparison_count);
    quickSort(pivot + 1, end, arr, comparison_count);

}
 
int partition(int start, int end, double arr[], int &comparison_count) {

    medianOfThree(arr, start, end, comparison_count);
    int pivot = end;
    int i = start - 1;
    double temp;

    for(int j = start; j < end; j++) {
        
        if (LESS(arr[j], arr[end], comparison_count)) {             //if arr[start] < arr[end]
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        } 
    }

    i++;
    temp = arr[i];
    arr[i] = arr[end];
    arr[end] = temp;

    return i;       // returning the pivot index
}

bool LESS(double a, double b, int &comparison_count) {

    comparison_count++;
    return a < b;
}

void output(double arr[], int &comparison_count, int arrLen) {

    ofstream output;
    output.open("jlt0060.txt");

    if (!output.is_open()) {
        cout << "Error opening output file" << endl;
    }

    output << arrLen << endl;

    for (int i = 0; i < arrLen; i++) {
        output << arr[i] << endl;
    } 

    output << "Comparison count: " << comparison_count << endl;
    output.close();
}

void medianOfThree(double arr[], int start, int end, int &comparison_count) {

    int middle = (start + end) / 2;

    if (LESS(arr[start], arr[middle], comparison_count) ^ LESS(arr[start], arr[end], comparison_count)) {     // if start < mid XOR start < end (start is median) 
        swap(arr[start], arr[end]);
    } else if (LESS(arr[middle], arr[start], comparison_count) ^ LESS(arr[middle], arr[end], comparison_count)) {     // if mid < start XOR mid < end (mid is median) 
        swap(arr[middle], arr[end]);   
    }                                                                                                       // else end is median
}