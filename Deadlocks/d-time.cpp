/**
*
* Jordan Riley
* CST-221
* 10-3-2018
* Deadlock Avoidance
*
* This program demonstrates a process being in an unsafe state,
* being put to sleep by a time interval, and then being awoken to
* try and request the resources it needs.
* (Resources will be hard coded to be available once process is awoken)
*
*
*
**/
#include<iostream>
#include<string>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>

using namespace std;

// Number of processes
const int P = 5;

// Number of resources
const int R = 3;

ofstream txtFile;

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

// Resources allocated to processes
int allot[][R] = {{2, 2, 2},
                  {1, 3, 5},
                  {1, 2, 6},
                  {3, 2, 5},
                  {6, 3, 1}};


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
            cout << "System is not in safe state" << endl;
            txtFile << "System is not in safe state" << endl;
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


//checks if the processes are in a safe state to run
//if not, it sleeps for 5 seconds and tries again
void *process(void *pointer) {

  while (!isSafe(processes, avail, maxm, allot)) {

    cout << "Process 1 sleeping for time interval of 5 seconds" << endl;
    txtFile << "Process 1 sleeping for time interval of 5 seconds" << endl;

    sleep(6);

    cout << "Process 1 waking up, checking resources again.." << endl;
    txtFile << "Process 1 waking up, checking resources again.." << endl;

  }


}

//sleeps for 2 seconds initially,
//then sets the matrixes to a new, safe state
void *freeResources(void *pointer) {

  sleep(3);

  cout << "Process 2 frees up resources" << endl;
  txtFile << "Process 2 frees up resources" << endl;

  int newProcesses[] = {0, 1, 2, 3, 4};

  memcpy(processes, newProcesses, sizeof(newProcesses));

  // Available instances of resources
  int newAvail[] = {3, 3, 2};

  memcpy(avail, newAvail, sizeof(newProcesses));

  // Maximum R that can be allocated
  // to processes
  int newMaxm[][R] = {{7, 5, 3},
                   {3, 2, 2},
                   {9, 0, 2},
                   {2, 2, 2},
                   {4, 3, 3}};

  memcpy(maxm, newMaxm, sizeof(newMaxm));

  printMatrix("New maximum Resource Matrix: ", newMaxm);

  // Resources allocated to processes
  int newAllot[][R] = {{0, 1, 0},
                    {2, 0, 0},
                    {3, 0, 2},
                    {2, 1, 1},
                    {0, 0, 2}};
  memcpy(allot, newAllot, sizeof(newAllot));
  printMatrix("New allocated Resources Matrix: ", newAllot);

}



// Driver code
int main()
{
    txtFile.open("d-time.txt");

    //print matrixes
    printMatrix("Maximum Resource Matrix: ", maxm);
    printMatrix("Allocated Resources Matrix: ", allot);

    pthread_t threadID;

    //create a pthread to act as the current running process that is starved
    pthread_create(&threadID, NULL, process, NULL);

    //create a pthread to act as a second process that free's up it's used resources
    pthread_create(&threadID, NULL, freeResources, NULL);



    txtFile.close();

    while (1) {

    }

    return 0;
}
