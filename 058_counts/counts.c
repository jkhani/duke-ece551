#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * countsArray = malloc(sizeof(*counts_t));
  countsArray->stringCounts = NULL;
  countsArray->numStrings = 0;
  countsArray->unknownCounts = 0;

  return countsArray;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if(c->numStrings == 0){
    size_t numStrings = 1;
    c->stringCounts = realloc(c->stringCounts,
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
}

void freeCounts(counts_t * c) {
  //WRITE ME
}
