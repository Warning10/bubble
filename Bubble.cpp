#include <omp.h>
#include <iostream>
#include <time.h>
using namespace std;

void serialBubbleSort(int array[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void parallelBubbleSort(int array[], int n) {
    int var = 0;
#pragma omp parallel
    {
        for (int i = 0; i < n; i++) {
#pragma omp for
            for (int j = var; j < n - 1; j += 2) {
                if (array[j] > array[j + 1]) {
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }

#pragma omp single
            {
                if (var == 0)
                    var = 1;
                else
                    var = 0;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of elements : ";
    cin >> n;
    cout << endl;

    int array[n] = {0};

    srand(time(NULL));
    for(int i=0;i<n;i++)
    {
        array[i]=rand()%32;
    }

    cout << "Original Array: ";
    for (int i = 0; i < n; i++) cout << array[i] << " ";
    cout << endl;

    clock_t start, stop;

    // Serial Execution
    start = clock();
    serialBubbleSort(array, n);
    stop = clock();

    cout << "\nFinal Array (Serial): ";
    for (int i = 0; i < n; i++) cout << array[i] << " ";
    cout << endl;

    cout << "\nTime required for Serial Execution: " << (double)(stop - start) << " ms" << endl;
    
    // Reset array for parallel execution
    srand(time(NULL));
    for(int i=0;i<n;i++)
    {
        array[i]=rand()%32;
    }

    // Parallel Execution
    start = clock();
    parallelBubbleSort(array, n);
    stop = clock();

    cout << "\nFinal Array (Parallel): ";
    for (int i = 0; i < n; i++) cout << array[i] << " ";
    cout << endl;

    cout << "\nTime required for Parallel Execution: " << (double)(stop - start) << " ms" << endl;

    return 0;
}
