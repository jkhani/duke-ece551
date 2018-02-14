#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"



kvarray_t * readKVs(const char * fname) {
  //WRITE ME

  FILE * f = fopen(fname, "r");
  if (f == NULL){
    fprintf(stderr,"Could not open file");
    exit(EXIT_FAILURE);
  }

  kvpair_t pairs;
  kvarray_t * pairArray = malloc(sizeof(*pairArray));

  char *curr = NULL;
  size_t linecap;
  // count kv pairs
  size_t numPairs = 0;
  // count key length
  size_t i = 0;
  // count pair length
  size_t j = 0;
  while(getline(&curr, &linecap, f) >= 0){
    while(*curr != '=' && *curr != '\0'){
      pairs.key[i]=*curr;
      i++;
      curr++;
    }
    pairs.key[i]='\0';
    
    while(*curr != '\0'){
      pairs.value[j]=*curr;
      j++;
      curr++;
      curr = NULL;
    }

    pairArray = realloc(pairArray, (numPairs+1) *sizeof(*pairArray));
    pairArray[numPairs].kv_array = pairs;
    
  }

  if(fclose(f) != 0){
    fprintf(stderr, "Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
      
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME

  size_t numPairs = pairs.numPairs;
  for(size_t i = 0; i < numPairs; i++){
    free(pairs->kv_array[i]);
  }

  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
}
