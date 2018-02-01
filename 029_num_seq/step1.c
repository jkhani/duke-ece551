#include <stdio.h>
#include <stdlib.h>

//This file is for Step 1.
//You should do 
//  Step 1 (A): write seq1
int seq1(int x){
  int seq = 4*x-3;
  return seq;
}

//  Step 1 (B): write main to test seq1
/* Main for just testing seq1
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
  int testCases[] = {-100,-50,-4,-1,0,1,4,50,100};
  int numCases = sizeof(testCases)/sizeof(*testCases);
  for (int x = 0; x < numCases; x++){
    int result = seq1(testCases[x]);
    printf("seq1(%d) = %d\n", testCases[x], result);
  }

  printSeq1Range(0,4);
  printSeq1Range(-2,6);
  printSeq1Range(7,3);
  printSeq1Range(2,-1);
  printSeq1Range(100,1);
  printSeq1Range(-1,-4);
  printSeq1Range(-1,-100);
  printSeq1Range(-6,-1);
  
  return EXIT_SUCCESS;
}

// Be sure to #include any header files you need!

