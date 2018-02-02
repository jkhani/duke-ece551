#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n){
  // corner case for NULL array
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
	if (temp_seq > seq_max){
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
