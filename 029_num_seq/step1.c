#include <stdio.h>
#include <stdlib.h>

//This file is for Step 1.
//You should do 
//  Step 1 (A): write seq1
// seq1() returns the xth element in the sequence
int seq1(int x){
  // the function can be described by the equation y = 4x-3
  int seq = 4*x-3;
  return seq;
}

//  Step 1 (B): write main to test seq1
/* Main for just testing seq1 -> moved to single main for both seq1 and printSeq1Range
int main(void){
  int testCases[] = {-100,-50,-4,-1,0,1,4,50,100};
  int numCases = sizeof(testCases)/sizeof(*testCases);
  for (int x = 0; x < numCases; x++){
    int result = seq1(testCases[x]);
    printf("seq1(%d) = %d\n", testCases[x], result);
  }
  return EXIT_SUCCESS;
}
*/
//  Step 1 (C): write printSeq1Range
// 
void printSeq1Range(int low, int high){
  if (low < high) {
    for (int i = low; i < high; i++){
      int result = seq1(i);
      printf("%d", result);
      if (i < (high - 1)){
	  printf(",");
      }
    }
  }
  printf("\n");
}
//  Step 1 (D): add test cases to main to test printSeq1Range
//
int main(void){
  // array of testcases for testing seq1(), tests large negatives, small negatives, examples from instructions, and large positive values
  int testCases[] = {-10000,-100,-50,-4,-1,0,1,4,50,100,10000};
  // calculate number of testcases (could be hardcoded)
  int numCases = sizeof(testCases)/sizeof(*testCases);
  // for loop for running through testcase arrays
  for (int x = 0; x < numCases; x++){
    int result = seq1(testCases[x]);
    // print call and results of seq1
    printf("seq1(%d) = %d\n", testCases[x], result);
  };

  // 2 arrays for testing printSeq1Range
  // array of "low" values
  int testLows[] = {0,-2,7,2,0,100,-1,-1,-6};
  // array of "high" values
  int testHighs[] = {4,6,3,-1,0,1,-4,-100,-1};
  // calculate number of test cases from the number of elements
  int numTests = sizeof(testLows)/sizeof(*testLows);
  for (int i = 0; i < numTests; i++){
    // print call and results of printSeq1Range
    printf("printSeq1Range(%d,%d)\n",testLows[i],testHighs[i]);
    printSeq1Range(testLows[i],testHighs[i]);
  }
  
  return EXIT_SUCCESS;
}

// Be sure to #include any header files you need!

