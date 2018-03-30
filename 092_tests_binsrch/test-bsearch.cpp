#include "function.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedInFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int, int> *f;
  const char *mesg;
public:
  CountedInFn(unsigned n, Function<int, int> *fn, const char* m):remaining(n), f(fn), mesg(m){}
  virtual int invoke(int arg){
    if(remaining == 0){
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> *f, int low, int high, int expected_ans, const char *mesg){
  int remain = high > low ? log2(high - low)+1 : 1;
  Function<int, int> *Countedf = new CountedInFn(remain, f, mesg);
  if( binarySearchForZero(Countedf, low, high) != expected_ans){
    fprintf(stderr, "The answer is %s\n", mesg);
    exit(EXIT_FAILURE);
  }

  delete Countedf;
}

int main(){
  class Linearf : public Function<int, int>{
  public:
    virtual int invoke( int arg){
      return 3*arg+100;
    }
  };

  class square: public Function<int, int>{
  public:
    virtual int invoke( int arg){
      return arg* arg;
    }
  };

  Function<int, int> *f1 = new Linearf();

  Function<int, int> *f2 = new square();

  check(f1, -100, 100, -34, "1\n");
  check(f1, 1, 1, 1, "2\n");
  check(f1, 3, 5, 3, "3\n");
  check(f1, -40, -35, -36, "4\n");
  check(f1, -35, -34, -35, "5\n");
  check(f1, -34, -33, -34, "6\n");
  check(f1, -34, -34, -34, "7\n");
  check(f1, -10000, 10000, -34, "8\n");

  return EXIT_SUCCESS;

}
