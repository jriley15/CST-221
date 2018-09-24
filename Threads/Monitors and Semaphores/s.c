/*

  Jordan Riley
  CST-221
  Semaphore

  Producer adds 25 to buffer every loop until it's full
  Consumer consumes 25 from the buffer every loop until it's empty

  Both lock the buffer resource using the semaphore (1 = unlocked, 0 = locked)


*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//constants
#define MAX_BUFFER_SIZE 100

//semaphore integer (1 = unlocked, 0 = locked)
int semaphore = 1;

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



void producer() {
  int i;

  //loop as long as the buffer isn't full
  while (buffer < MAX_BUFFER_SIZE) {

    //wait until the semaphore is unlocked
    while (semaphore != 1) {
    }

    //lock the semaphore
    semaphore = 0;

    //generate int to add to buffer
    i = produce();

    //add int to the buffer
    put(i);

    //print values
    printf("Producing, Buffer: %i \n", buffer);

    //unlock the semaphore
    semaphore = 1;
  }

  printf("Buffer full\n");

  //start consuming
  consumer();
}


void consumer() {
  int i;

  //loop until buffer is empty
  while (buffer > 0) {

    //wait until the semaphore is unlocked
    while (semaphore != 1) {
    }

    //lock the semaphore
    semaphore = 0;

    //generate int to consume from the buffer
    i = get();

    //consume the int from the buffer
    consume(i);

    //print values
    printf("Consuming: %i, Buffer: %i \n", i, buffer);

    //unlock the semaphore
    semaphore = 1;
  }

  printf("Buffer empty\n");

  //start Producing
  producer();
}

void main() {

  //producer function call to kick off the program
  producer();


}
