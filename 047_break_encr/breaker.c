#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// breaker: function for decrypting encrypted message
void breaker(FILE * f){
  int c;
  int letterFreq[26] = {0};
  // count the frequency of each letter until reach the end of file
  while ((c = fgetc(f)) != EOF){
    if (isalpha(c)){
      c = tolower(c);
      // get value of c in the range of 0-25
      c -= 'a';
      letterFreq[c]++;
    }
  }

  // find index with highest frequency and assume it is 'e'
  int e_encrypted = 0;
  for (int i = 0; i<26; i++){
    if (letterFreq[i] > letterFreq[e_encrypted]){
      e_encrypted = i;
    }
  }


  int key = (e_encrypted+'a')-'e';

  // print key to command line
  printf("%d\n",key);
}

int main(int argc, char ** argv) {
  // check that the correct number of arguments have been passed to the program
  if (argc != 2){
    fprintf(stderr,"Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  // check that file is not NULL
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  breaker(f);

  if (fclose(f) !=0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;  
}
