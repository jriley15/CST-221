/*

  Jordan Riley
  CST-221
  Monitor

  Producer adds 25 to buffer every loop until it's full
  Consumer consumes 25 from the buffer every loop until it's empty



*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//constants
#define MAX_BUFFER_SIZE 100

//monitor struct
typedef struct Monitor {

  //mutex variable (0 = locked, 1 = unlocked)
  int mutex;

  //full variable
  int full;

  //empty variable
  int empty;

} Monitor;

//buffer
int buffer = 0;


int produce() {
  //return int to add to the buffer
  return 25;
}

int get() {
  //return int to consume from the buffer
  return 25;
}

void consume(int i) {
  //remove from the buffer
  buffer -= i;
}

void put(int i) {
  //add to the buffer

    buffer += i;

}



void producer(Monitor *monitor) {
  int i;

  //loop as long as the buffer isn't full
  while (monitor->full == 0) {

    //wait until the mutex is unlocked
    while (monitor->mutex != 1) {
    }

    //set monitor to not empty
    monitor->empty = 0;

    //lock the mutex
    monitor->mutex = 0;

    //generate int to add to buffer
    i = produce();

    //add int to the buffer
    put(i);

    //print values
    printf("Producing, Buffer: %i \n", buffer);

    //set monitor to full if buffer is full
    if (buffer >= MAX_BUFFER_SIZE) {
      monitor->full = 1;
    }

    //unlock the mutex
    monitor->mutex = 1;
  }

  printf("Buffer full\n");

  //start consuming
  consumer(monitor);
}


void consumer(Monitor *monitor) {
  int i;

  //loop until buffer is empty
  while (monitor->empty == 0) {

    //wait until the mutex is unlocked
    while (monitor->mutex != 1) {
    }

    //set monitor to not full
    monitor->full = 0;

    //lock the mutex
    monitor->mutex = 0;

    //generate int to consume from the buffer
    i = get();

    //consume the int from the buffer
    consume(i);

    //print values
    printf("Consuming: %i, Buffer: %i \n", i, buffer);

    //set monitor to empty if buffer is empty
    if (buffer <= 0) {
      monitor->empty = 1;
    }

    //unlock the mutex
    monitor->mutex = 1;
  }

  printf("Buffer empty\n");

  //start Producing
  producer(monitor);
}

void main() {

  //create monitor struct
  Monitor monitor = {
    //set unlocked
    .mutex = 1,
    //set not full
    .full = 0,
    //set empty
    .empty = 1
  };


  //producer function call to kick off the program, pass in monitor struct
  producer(&monitor);


}
