

#include<iostream>
#include<string>
#include <fstream>
using namespace std;

// Number of processes
const int P = 5;

// Number of resources
const int R = 3;


void printMatrix(string msg, int array[P][R]) {
  cout << msg << endl;
  txtFile << msg << endl;
  for ( int x = 0; x < P; x ++ ) {
    cout << "[";
    for ( int y = 0; y < R; y++ ) {
        cout << array[x][y] << " ";
    }
    cout << "]" << endl;
  }
}

void change() {


}


// Driver code
int main()
{

    int* processes[5] = {0, 1, 2, 3, 4};

    // Available instances of resources
    int avail[] = {3, 3, 2};

    // Maximum R that can be allocated
    // to processes
    int maxm[][R] = {{7, 5, 3},
                     {3, 2, 2},
                     {9, 0, 2},
                     {2, 2, 2},
                     {4, 3, 3}};
    printMatrix("Maximum Resource Matrix: ", maxm);

    // Resources allocated to processes
    int allot[][R] = {{0, 1, 0},
                      {2, 0, 0},
                      {3, 0, 2},
                      {2, 1, 1},
                      {0, 0, 2}};
    printMatrix("Allocated Resources Matrix: ", allot);

    change();

    printMatrix("Maximum Resource Matrix: ", maxm);
    printMatrix("Allocated Resources Matrix: ", allot);


    return 0;
}
