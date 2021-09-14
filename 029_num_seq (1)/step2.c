#include <stdio.h>
#include <stdlib.h>

//This file is for Step 2.
//You should do 
//  Step 2 (A): write seq2
// seq2 described by y = x^2+3x+1
int seq2(int x){
  int seq = (x*x)+(3*x)+1;
  return seq;
}

//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
// takes 2 values and returns the sum of the results from seq2 between those values
int sumSeq2(int low, int high){
  // create variable for keeping track of sum
  int sum = 0;
  for (int i = low; i < high; i++){
    // evaluate seq2 and add value to previous value
    sum += seq2(i);
  }

  return sum;
}
//  Step 2 (D): add test cases to main to test sumSeq2
//
int main(void){
  // create range of test cases from example sequences in instructions
  int testStart = -4;
  int testStop = 14;
  // loop through test cases
  for (int x = testStart; x <= testStop; x++){
    int result = seq2(x);
    // print call and results from seq2
    printf("seq2(%d) = %d\n", x, result);
  }

  // additional tests cases to test large negatives and positives
  int testAdditional[] = {-1000,-100,50,997};
  int numAddTest = sizeof(testAdditional)/sizeof(*testAdditional);
  for (int ix = 0; ix < numAddTest; ix++){
    // results from additional tests
    int resultAdd = seq2(testAdditional[ix]);
    // print call and results from seq2
    printf("seq2(%d) = %d\n", testAdditional[ix], resultAdd);
  }

  // create test cases for sumSeq2
  int testLows[] = {0,3,9,-100,-100,0,100,1000};
  int testHighs[] = {2,6,7,-101,-99,0,99,1010};
  int numTests = sizeof(testLows)/sizeof(*testLows);
  for (int i = 0; i < numTests; i++){
    int resultsSum = sumSeq2(testLows[i],testHighs[i]);
    // print call and results from sumSeq2
    printf("sumSeq2(%d, %d) = %d\n",testLows[i],testHighs[i],resultsSum);
  }

  return EXIT_SUCCESS;
}
// Be sure to #include any header files you need!
