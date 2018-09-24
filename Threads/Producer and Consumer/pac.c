/*

  Jordan Riley
  CST-221
  Producer and Consumer

*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

//constants
#define MAX_BUFFER_SIZE 100
#define PRODUCE_AMOUNT 25
#define CONSUME_AMOUNT 10

//buffer
int Buffer = 0;


int produce() {
  //return int to add to the buffer
  return PRODUCE_AMOUNT;
}

int get() {
  //return int to consume from the buffer
  return CONSUME_AMOUNT;
}

void consume(int i) {
  //remove from the buffer
  Buffer -= i;
}

void put(int i) {
  //add to the buffer

  //check if it's full, don't go over max buffer size
  if (Buffer + i > MAX_BUFFER_SIZE) {
    Buffer = MAX_BUFFER_SIZE;
  } else {
    Buffer += i;
  }
}



void *producer(void *ptr) {
  int i;
  while (1) {

    //generate int to add to buffer
    i = produce();

    //wait until buffer has space to add to it
    while (Buffer + i >= MAX_BUFFER_SIZE) {
      printf("Buffer is full, waiting on consumer.\n");
      sleep(1);
    }

    //add int to the buffer
    put(i);

    //print values
    printf("Producing, Buffer: %i \n", Buffer);

    //sleep for 2 secs
    sleep(2);
  }
}


void *consumer(void *ptr) {
  int i;
  while (1) {

    //generate int to consume from the buffer
    i = get();

    //wait until the buffer has data to consume (should not happen)
    while (Buffer - i < 0) {
      printf("Buffer is empty, waiting on producer - ERROR.\n");
      sleep(1);
    }

    //consume the int from the buffer
    consume(i);

    //print values
    printf("Consuming: %i, Buffer: %i \n", i, Buffer);

    //sleep for 1 second
    sleep(1);
  }
}

void main() {

  //pthread id declaration
  pthread_t id;

  //consumer thread
  pthread_create(&id, NULL, consumer, NULL);

  //producer thread
  pthread_create(&id, NULL, producer, NULL);


  while(1) {

  }

}
