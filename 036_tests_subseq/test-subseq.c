#include <stdio.h>
#include <stdlib.h>

//call to function outside scope
size_t maxseq(int * array, size_t n);


//function for checking output of maxseq() against expectation
void run_check(int * array, size_t n, size_t expected_ans){

  //call maxseq()
  size_t ans = maxseq(array,n);
  printf("maxseq(%d,%zd) = %zd\n",array,n,ans);

  if (ans != expected_ans){
    exit(EXIT_FAILURE);
  }
};


int main(){

  int test1[] = {1,2,1,3,5,7,2,4,6,9};
  run_check(test1,10,4);

  return EXIT_SUCCESS;
}
