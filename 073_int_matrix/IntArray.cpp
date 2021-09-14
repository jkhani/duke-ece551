#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray() {
  numElements = 0;
  data = NULL;
}
IntArray::IntArray(int n):data(new int[n]),numElements(n) {
}

IntArray::IntArray(const IntArray & rhs):data(new int[rhs.numElements]),numElements(rhs.numElements) {
  for(int i = 0; i<numElements; i++){
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[]data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if(this != &rhs){
    int * temp = new int[numElements];

    for (int i=0; i<numElements; i++){
      temp[i] = rhs.data[i];
    }

    delete[]data;
    numElements = rhs.numElements;
    data = temp;
  }

  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index >=0 && index < numElements);
  return data[index];
}
int & IntArray::operator[](int index) {
  assert(index >=0 && index < numElements);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  for(int i=0; i<numElements; i++){
    if(data[i] != rhs.data[i]){
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  for(int i=0; i<numElements; i++){
    if(data[i] != rhs.data[i]){
      return true;
    }
  }
  return false;

  
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for(int i=0; i< rhs.size() ; i++){
    s << rhs[i];
    if (i < (rhs.size()-1)){
      s << ", ";
    }
  }

  s << "}";

  return s;
}
