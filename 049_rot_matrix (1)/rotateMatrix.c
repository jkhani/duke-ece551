#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// set line size based on instructions
#define LINE_SIZE 10
void rotateMatrix(FILE * f){

  // to rotate clockwise, elements in the 1st row should be placed in the last column
  // so colInd of rotated matrix starts at 10
  int colInd = LINE_SIZE;
  char newMatrix[10][10]; // matrix to store chars from input matrix
  char line[LINE_SIZE+2]; //+2 to hold the \n and \0 characters
  char ch;

  while (fgets(line, LINE_SIZE+2, f) != NULL){
    // error if line longer than 10
    if (strchr(line, '\n') == NULL || strchr(line, '\0') == NULL) {
      fprintf(stderr,"Line is too long!\n");
      exit(EXIT_FAILURE);
    }

    // subtract 1 from the colInd before using b/c 0-indexing
    colInd--;

    if (colInd < 0){
      fprintf(stderr, "Too many rows\n");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < LINE_SIZE; i++){
      ch = line[i];
      // error if newline character before 10 non-newline characters
      if (ch == '\n'){
	fprintf(stderr,"Line too short!\n");
	exit(EXIT_FAILURE);
      }
      newMatrix[i][colInd] = ch;
    }
  }

      // error if there are less than 10 rows
  if (colInd != 0){
    fprintf(stderr,"Matrix not right number of rows!\n");
    exit(EXIT_FAILURE);
  }


  for (int i = 0; i < LINE_SIZE; i++){
    for (int j = 0; j < LINE_SIZE; j++){
      printf("%c",newMatrix[i][j]);
    }
    printf("\n");
  }
    
}

int main(int argc, char ** argv){

  // check that input file was provided as argument
  if (argc != 2){
    fprintf(stderr,"Usage: rotateMatrix inputFilename\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");

  // error if file not openable
  if (f == NULL){
    fprintf(stderr,"Could not open file!\n");
    return EXIT_FAILURE;
  }

  rotateMatrix(f);

  // error if file doesn't close
  if (fclose(f) != 0) {
    fprintf(stderr,"Failed to close the input file!\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
