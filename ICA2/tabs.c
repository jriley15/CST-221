#include<stdio.h>

main() {

  int tabLength = 8;

  int length = 50;
  char input[length];

  printf("Enter a string with tabs\n");
  scanf("%[^\n]s", input);

  int inputIndex = 0;
  
  char output[length];
  int outputIndex = 0;

  while (inputIndex < length) {

      if (input[inputIndex] == '\t') {
        for (int spaces = 0; spaces < tabLength; spaces++) {
          output[outputIndex] = ' ';
          outputIndex++;
        }

      } else {

        output[outputIndex] = input[inputIndex];
        outputIndex++;
      }

      inputIndex++;
  }


  printf("Tabs converted to spaces: %s \n", output);


}
