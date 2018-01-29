#include <stdio.h>
#include <stdlib.h>

unsigned power_helper(unsigned base, unsigned exp){
  // corner case
  if (base==0 && exp==0) {
    return 1;
  }

  // base case
  if (exp ==1) {
    return base;
  }
  
  return (base*power_helper(base,exp-1));

}
  

unsigned power(unsigned x, unsigned y) {
  return power_helper(x,y);
}
