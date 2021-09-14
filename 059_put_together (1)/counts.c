#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"


counts_t * createCounts(void) {
  //WRITE ME
  counts_t * countsArray = malloc(sizeof(*countsArray));
  countsArray->stringCounts = NULL;
  countsArray->numStrings = 0;
  countsArray->unknownCounts = 0;

  return countsArray;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME

  // if name is NULL, add to unKnownCounts and move on
  if(name == NULL){
    c->unknownCounts++;
  }
  else{
    // check if it is the first name added to the struct
    if(c->numStrings == 0){
      c->stringCounts = realloc(c->stringCounts,(c->numStrings+1) *sizeof(*c->stringCounts));
      c->stringCounts[c->numStrings].stringVal = name;
      c->stringCounts[c->numStrings].counts=1;
      c->numStrings++;
    }
    else{
      // flag for whether the string has a record already
      int priorEntry = 0;

      // check name against all strings in the struct
      for(size_t i = 0; i < c->numStrings; i++){
	// if the string already has a record, add and move on
	if(!strcmp(name,c->stringCounts[i].stringVal)){
	  c->stringCounts[i].counts++;
	  // flag as having prior entry
	  priorEntry = 1;
	}
      }

      if(!priorEntry){
	c->stringCounts = realloc(c->stringCounts,(c->numStrings+1) *sizeof(*c->stringCounts));
	c->stringCounts[c->numStrings].stringVal = name;
	c->stringCounts[c->numStrings].counts = 1;
	c->numStrings++;
      }
    }
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for(size_t i = 0; i < c->numStrings; i++){
    fprintf(outFile,"%s: %zu\n",c->stringCounts[i].stringVal,c->stringCounts[i].counts);
  }

  if(c->unknownCounts > 0){
    fprintf(outFile,"<unknown> : %zu\n",c->unknownCounts);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  free(c->stringCounts);
  free(c);
}
