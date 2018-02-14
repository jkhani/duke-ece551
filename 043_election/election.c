#include "election.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//include any other headers you need here...


/* 
parseLine parses an input string with the expected format:
   Name:Population:Electoral Votes
returns a struct for each state with the parsed info
*/
state_t parseLine(const char * line) {
  //STEP 1: write me

  // exit with error if line provided is NULL
  if (line == NULL){
    fprintf(stderr,"Line provided is NULL");
    exit(EXIT_FAILURE);
  }

  // declare struct for storing state data
  state_t stateData;
  
  // loop through line until pointer points to ':'
  int i = 0;
  while(*line != ':' && *line != '\0'){
    // exit with error if first part of string contains non-alphabetic characters
    if (!isalpha(*line) && *line != ' '){
      fprintf(stderr,"Line provided includes non-alphabetic values where name should be!\n");
      exit(EXIT_FAILURE);
    }
     // exit with error if name exceeds max length for state
    if(i > MAX_STATE_NAME_LENGTH){
      fprintf(stderr,"State name too long!");
      exit(EXIT_FAILURE);
    }
    stateData.name[i] = *line;
    i++;
    line++;
  }

  // append '\0' to end of name
  stateData.name[i] = '\0';

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

/*
countElectoralVotes takes 3 arguments, a pointer to stateData struct, pointer to voteCounts, and number of states
for each state, if voteCounts > .5*population of state, candidate A gets all the electoral votes from that state
returns the total number of electoral votes for candidate A

 */
unsigned int countElectoralVotes(state_t * stateData, 
				 uint64_t * voteCounts, 
				 size_t nStates) {
  //STEP 2: write me
  unsigned int totalVotesForA = 0;
  uint64_t currPop = 0;

  for(size_t currState = 0; currState < nStates; currState++){
    currPop = stateData[currState].population;
    // compare voteCounts for currState with 1/2 population for currState
    // candidate A gets all votes for currState if more than 50% of vote
    if(voteCounts[currState] > (currPop/2)){
      totalVotesForA += stateData[currState].electoralVotes;
    }
  }
  
  return totalVotesForA;
}
/*
printRecounts determines which states had a margin of victory within +/-0.5%
prints to terminal the identified states and the results
*/
void printRecounts(state_t * stateData, 
		   uint64_t * voteCounts, 
		   size_t nStates) {
  //STEP 3: write me
  float percentOfVotes = 0;
  // need to typecast voteCounts and population as float
  float currVoteCount = 0;
  float currPop = 0;

  for(size_t currState = 0; currState < nStates; currState++){
    currVoteCount = voteCounts[currState];
    currPop = stateData[currState].population;
   
    percentOfVotes = currVoteCount/currPop;
    // check if percentOfVotes won by Candidate A is between 49.5 and 50.5% of the population for currState
    // if so, report results
    if(percentOfVotes >= .495 && percentOfVotes <= .505){
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",stateData[currState].name,percentOfVotes*100);
    }
  }
}

/*
printLargestWin determines the state where Candidate A won the largest percentage of the vote andprints the results to terminal.
 */
void printLargestWin(state_t * stateData, 
		     uint64_t * voteCounts, 
		     size_t nStates) {
  //STEP 4: write me
  float percentOfVotes = 0;
  // need to typecast voteCounts and population as float
  float currVoteCount = 0;
  float currPop = 0;
  // track the state where Candidate A had he largest percent of the vote and what that percentage was
  size_t stateWithMax;
  float maxPercentWin = 0;

  for(size_t currState = 0; currState < nStates; currState++){
    currVoteCount = voteCounts[currState];
    currPop = stateData[currState].population;
    percentOfVotes = currVoteCount/currPop;

    // if currState has higher percent than current max state, change max state
    if(percentOfVotes > maxPercentWin){
      maxPercentWin = percentOfVotes;
      stateWithMax = currState;
    }
  }

  
  printf("Candidate A won %s with %.2f%% of the vote\n",stateData[stateWithMax].name,maxPercentWin*100);
}
