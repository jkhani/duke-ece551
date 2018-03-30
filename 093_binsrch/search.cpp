#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high){
  int y;
  int mid = low+(((high-low)/2.0));

  if (low == high) {
    return mid;
  }

  y = f->invoke(mid);

  if (y <= 0){
    if (low == high-1){
      return low;
    }
    low = mid;
    return binarySearchForZero(f, low, high);
  }
  else {
    high = mid;
    return binarySearchForZero(f, low, high);
  }
}
