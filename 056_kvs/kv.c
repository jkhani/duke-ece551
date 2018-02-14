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
  kv_array pairArray;

  const char *curr = NULL;
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
    while(*curr != '\0'){
      pairs.value[j]=*curr;
      j++;
      curr++;
    }

    pairArray = realloc(pairArray, (numPairs+1) *sizeof(*pairArray));
    pairArray[numPairs].kv_array = pairs;
    
  }
    
  
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
}
