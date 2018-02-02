#include <stdio.h>
#include <stdlib.h>

//call to function outside scope
size_t maxSeq(int * array, size_t n);

void printArray(int * array, size_t n){

  printf("{");
  for (int i=0; i<n; i++){
    printf("%d", array[i]);
    if (i < (n-1)){
      printf(",");
    }
  }
  printf("}");
};


//function for checking output of maxseq() against expectation
void run_check(int * array, size_t n, size_t expected_ans){

  //call maxseq()
  size_t ans = maxSeq(array,n);
  printf("maxSeq(");
  printArray(array,n);
  printf(",%zd) = %zd\n",n,ans);

  if (ans != expected_ans){
    exit(EXIT_FAILURE);
  }
};


int main(){

  int test1[] = {1,2,1,3,5,7,2,4,6,9};
  int test2[] = {-4,-3,-2,0,3,2,1};
  int test3[] = {-1};
  int test4[] = {5,4,3,2,1};
  int test5[] = {0,0,0};

  run_check(NULL,0,0);
  run_check(test4,5,1);
  run_check(test5,3,1);
  run_check(test1,10,4);
  run_check(test2,7,5);
  run_check(test3,1,1);

  return EXIT_SUCCESS;
}
