/**
*
* Jordan Riley
* CST-221
* 10-3-2018
* Deadlock Avoidance
*
* This program demonstrates the un-safe usage of the Banker's algorithm
*
*
*
*
**/

#include<iostream>
#include<string>
#include <fstream>
using namespace std;

// Number of processes
const int P = 5;

// Number of resources
const int R = 3;

ofstream txtFile;

// Function to find the need of each process
// To calculate the need, we take the max matrix and subtract the allocation matrix from it
void calculateNeed(int need[P][R], int maxm[P][R], int allot[P][R])
{
    // Calculating Need of each P
    for (int i = 0 ; i < P ; i++)
        for (int j = 0 ; j < R ; j++)

            // Need of instance = maxm instance - allocated instance
            need[i][j] = maxm[i][j] - allot[i][j];
}


void printMatrix(string msg, int array[P][R]) {
  cout << msg << endl;
  txtFile << msg << endl;
  for ( int x = 0; x < P; x ++ ) {
    cout << "[";
    txtFile << "[";
    for ( int y = 0; y < R; y++ ) {
        cout << array[x][y] << " ";
        txtFile << array[x][y] << " ";
    }
    txtFile << "]" << endl;
    cout << "]" << endl;
  }
}


// Function to find the system is in safe state or not
bool isSafe(int processes[], int avail[], int maxm[][R], int allot[][R])
{
    int need[P][R];

    // Function to calculate need matrix
    calculateNeed(need, maxm, allot);

    printMatrix("Needed Resources Matrix: ", need);


    // Mark all processes as infinish
    bool finish[P] = {0};

    // To store safe sequence
    int safeSeq[P];

    // Make a copy of available resources
    int work[R];
    for (int i = 0; i < R ; i++)
        work[i] = avail[i];

    // While all processes are not finished
    // or system is not in safe state.
    int count = 0;
    while (count < P)
    {
        // Find a process which is not finish and
        // whose needs can be satisfied with current
        // work[] resources.
        bool found = false;
        for (int p = 0; p < P; p++)
        {
            // First check if a process is finished,
            // if no, go for next condition
            if (finish[p] == 0)
            {
                // Check if for all resources of
                // current P need is less
                // than work
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                // If all needs of p were satisfied.
                if (j == R)
                {
                    // Add the allocated resources of
                    // current P to the available/work
                    // resources i.e.free the resources
                    for (int k = 0 ; k < R ; k++)
                        work[k] += allot[p][k];

                    // Add this process to safe sequence.
                    safeSeq[count++] = p;

                    // Mark this p as finished
                    finish[p] = 1;

                    found = true;
                }
            }
        }

        // If we could not find a next process in safe
        // sequence.
        if (found == false)
        {
            cout << "System is not in safe state";
            txtFile << "System is not in safe state";
            return false;
        }
    }

    // If system is in safe state then
    // safe sequence will be as below
    cout << "System is in a safe state.\nSafe sequence is: ";
    txtFile << "System is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < P ; i++) {
        cout << safeSeq[i] << " ";
        txtFile << safeSeq[i] << " ";
    }
    return true;
}

// Driver code
int main()
{
    txtFile.open("d-unsafe.txt");

    int processes[] = {0, 1, 2, 3, 4};

    // Available instances of resources
    int avail[] = {2, 3, 1};

    // Maximum R that can be allocated
    // to processes
    int maxm[][R] = {{3, 7, 6},
                     {5, 4, 6},
                     {7, 5, 8},
                     {6, 3, 7},
                     {8, 9, 4}};
    printMatrix("Maximum Resource Matrix: ", maxm);

    // Resources allocated to processes
    int allot[][R] = {{2, 2, 2},
                      {1, 3, 5},
                      {1, 2, 6},
                      {3, 2, 5},
                      {6, 3, 1}};
    printMatrix("Allocated Resources Matrix: ", allot);


    // Check system is in safe state or not
    isSafe(processes, avail, maxm, allot);

    txtFile.close();

    return 0;
}
