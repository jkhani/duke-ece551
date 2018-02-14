#include "election.h"
//include any other headers you need here...

state_t parseLine(const char * line) {
  //STEP 1: write me

  state_t stateData;

  // loop through line until pointer to :
  int i = 0;
  while(*line != ':'){
    stateData.name[i] = *line;
    i++;
    line++;
  }

  // progress pointer to next character after :
  line++;
  stateData.population = atoi(line);

  // progress pointer until next : in string
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
  return 0;
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
