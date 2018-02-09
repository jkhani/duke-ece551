#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define LINE_SIZE 10
int rotateMatrix(FILE * f){

  int colInd = LINE_SIZE;
  char newMatrix[10][10];
  char line[LINE_SIZE+1];
  while (fgets(line, LINE_SIZE+2, f) != NULL){
    if (strchr(line, '\n') == NULL) {
      printf("Line is too long!\n");
      return EXIT_FAILURE;
    }

    colInd--;

    for (int i = 0; i < LINE_SIZE; i++){
      char ch = line[i];
      newMatrix[i][colInd] = ch;
    }      
  }

  for (int i = 0; i < LINE_SIZE; i++){
    for (int j = 0; j < LINE_SIZE; j++){
      printf("%c",newMatrix[i][j]);
    }
    printf("\n");
  }

  return EXIT_SUCCESS;

  /* 1st APPROACH
  char  newMatrix[10][10];
  int rowInd = 0;
  int colInd = 0;
  int index = 0;
  while ((c = fgetc(f)) != EOF){
    rowInd = index % 10;
    colInd = 9-index/10;
    printf("c = %d, row = %d, col = %d\n",c,rowInd,colInd);
    newMatrix[rowInd][colInd]=c;
    index++;
  }*/
    
}

int main(int argc, char ** argv){

  if (argc != 2){
    fprintf(stderr,"Usage: rotateMatrix inputFilename\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL){
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  rotateMatrix(f);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
