#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n){
  // corner case for array size 0
  if (n == 0){
    return 0;
  }
  else{
    // variable for holding current length of increasing numbers
    size_t temp_seq = 1;
    // variable for holding largest number of increasing numbers in a row
    size_t seq_max = temp_seq;
    for (int i = 1; i < n; i++){
      // check if next number in array is larger than the last
      if (array[i] > array[i-1]){
	// if so, add to the sequence
	temp_seq += 1;
	// check if current longest seq is greater than the previous max sequence
	if (temp_seq > seq_max){
	  // if so, change max sequence to new longest streak
	  seq_max = temp_seq;
	}
      }
      else{
	temp_seq = 1;
      }
    }
    return seq_max;
  }
}
