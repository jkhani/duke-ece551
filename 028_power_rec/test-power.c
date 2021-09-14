#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {

  unsigned ans = power(x,y);
  printf("power(%d,%d) = %d \n",x,y,ans);

  if (ans != expected_ans){
    exit(EXIT_FAILURE);

  }
};

int main(void) {
  run_check(0,0,1);
  run_check(1,1,1);
  run_check(0,1,0);
  run_check(2,3,8);
  run_check(-1,2,1);
  run_check(10000,10000,0);
  run_check(10,5,100000);
  
  return EXIT_SUCCESS;
}
