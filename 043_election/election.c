#include "election.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//include any other headers you need here...


/* parseLine parses an input string with the expected format:
   Name:Population:Electoral Votes
   returns a struct for each state with the parsed info
*/
state_t parseLine(const char * line) {
  //STEP 1: write me
  
  state_t stateData;
  
  // loop through line until pointer points to ':'
  int i = 0;
  while(*line != ':'){
    stateData.name[i] = *line;
    i++;
    line++;
  }

  // advance pointer to next character after :
  line++;
  stateData.population = atoi(line);

  // advance pointer until next : in string
  while(*line != ':'){
    line++;
  }

  line++;
  stateData.electoralVotes = atoi(line);

  return stateData;
  
}
unsigned int countElectoralVotes(state_t * stateData, 
				 uint64_t * voteCounts, 
				 size_t nStates) {
  //STEP 2: write me
  unsigned int totalVotesForA = 0;
  uint64_t currPop = 0;

  for(size_t currState = 0; currState < nStates; currState++){
    currPop = stateData[currState].population;
    if(*voteCounts > currPop/2){
      totalVotesForA += stateData[currState].electoralVotes;
    }
  }
  
  return totalVotesForA;
}

void printRecounts(state_t * stateData, 
		   uint64_t * voteCounts, 
		   size_t nStates) {
  //STEP 3: write me
}
void printLargestWin(state_t * stateData, 
		     uint64_t * voteCounts, 
		     size_t nStates) {
  //STEP 4: write me
}
