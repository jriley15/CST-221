#include <stdio.h>
#include <pthread.h>

void *busy(void *ptr) {

  //while(1) {
    puts(ptr);
  //}
  return NULL;
}
void *busy2(void *ptr) {

  //while(1) {
    puts(ptr);
  //}
  return NULL;
}

int main() {

  pthread_t id;
  pthread_create(&id, NULL, busy, "Hi");

  pthread_create(&id, NULL, busy2, "Hi2");

  //scanf("%s", NULL);
  while (1) {
    
  }


}
