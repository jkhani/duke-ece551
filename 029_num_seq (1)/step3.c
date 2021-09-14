#include <stdio.h>
#include <stdlib.h>
//This file is for Step 3.
//You should do 
//  Step 3 (A): write seq3
// seq3 can be described by z = (x+2)(y-3)+6
int seq3(int x, int y){
  int seq = (x+2)*(y-3)+6;
  return seq;
}
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
// evaluate seq3 from xLow to xHi and yLow and yHi and count the number of even values returned
int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi){
  // create variable for storing the number of evens returned in the range called
  // default return is 0
  int evens = 0;
  // loop through integers between xLow and xHi
  for (int ix = xLow; ix < xHi; ix++){
    // loop through integers between yLow and yHi
    for (int iy = yLow; iy < yHi; iy++){
      // call seq3
      int temp = seq3(ix, iy);
      // check if returned value is even and add 1 if so
      if (temp % 2 == 0){
	evens += 1;
      }
    }
  }

  return evens;
}
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
int main(void){
  // test numbers from matrix provided in instructions
  int testxLow = -5;
  int testxHi = 5;
  int testyLow = -5;
  int testyHi = 5;
  // loop through elements in the matrix
  for (int ix = testxLow; ix <= testxHi; ix++){
    for (int iy = testyLow; iy <= testyHi; iy++){
      int result = seq3(ix,iy);
      // print call and return value of seq3
      printf("seq3(%d, %d) = %d\n",ix, iy, result);
    }
  }

  // test case given in instructions. test x when large negatives, same value, large positives
  int xLow[] = {0,-100,-100,0,2,100,100,3,2,2,1,3,100};
  int xHi[] = {2,-101,-98,0,1,99,103,6,6,5,5,8,1000};
  // test y when large negatives, large positives, same value
  int yLow[] = {0,2,2,3,2,2,2,-5,-100,-100,100,0,-1000};
  int yHi[] = {3,4,1,4,5,3,4,-2,-92,-106,108,0,-100};
  int numCases = sizeof(xLow)/sizeof(*xLow);
  for (int i = 0; i < numCases; i++){
    int evenResult = countEvenInSeq3Range(xLow[i],xHi[i],yLow[i],yHi[i]);
    // print call and returned value from countEvenInSeq3Range
    printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",xLow[i],xHi[i],yLow[i],yHi[i],evenResult);
  }
}
// Be sure to #include any header files you need!

