#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;


template<typename T>
class Matrix{
 private:
  int numRows;
  int numColumns;
  vector< vector<T> > rows;
 public:
 Matrix(): numRows(0), numColumns(0) {
 }
 Matrix(int r, int c): numRows(r), numColumns(c){
    for (int i=0; i<r; i++){
      rows[i] = new vector<T>(c);
    }
  }
 Matrix(const Matrix & rhs): numRows(rhs.numRows), numColumns(rhs.numColumns), rows(new vector<T>*[rhs.numRows]){
    for (int i=0; i<numRows; i++){
      vector<T>* tempArr = new vector<T>(*rhs.rows[i]);
      rows[i] = tempArr;
    }
  }
 ~Matrix() {
    for (int i=0; i<numRows; i++){
      delete rows[i];
    }

    delete[]rows;
  }
  Matrix & operator=(const Matrix & rhs){
    if(this != &rhs){
      vector<T> ** temp = new vector<T>*[rhs.numRows];

      for (int i=0; i<rhs.numRows; i++){
	vector<T>* tempArr = new vector<T>(*rhs.rows[i]);
	temp[i] = tempArr;
      }
      delete[]rows;

      numRows = rhs.numRows;
      numColumns = rhs.numColumns;

      rows = temp;
    }

    return *this;
  }

  int getRows() const {
    return numRows;
  }

  int getColumns() const {
    return numColumns;
  }

  const vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return (*rows[index]);
  }

  vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return (*rows[index]);
  }

  bool operator==(const Matrix & rhs) const {
    if (numRows != rhs.numRows || numColumns != rhs.numColumns){
      return false;
    }

    for (int i=0; i < numRows; i++){
      if ((*rows[i]) != (*rhs.rows[i])){
	return false;
      }
    }
    return true;
  }

  Matrix operator+(const Matrix & rhs) const{
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);

    Matrix sumMatrix(numRows, numColumns);

    for (int i=0; i < numRows; i++){
      for (int j=0; j < numColumns; j++){
	(*sumMatrix.rows[i])[j] = (*rows[i])[j]+(*rhs.rows[i])[j];
      }
    }

    return sumMatrix;
  }

};

template<typename S>
std::ostream & operator<<(std::ostream & s, const Matrix<S> & rhs) {
  s << "[ ";
  for (int i=0; i < rhs.getRows(); i++){
    s << "{";
    for (int j = 0; j <rhs.getColumns(); j++){
      s << rhs[i][j];
      if (j < (rhs.getColumns()-1)){
	s << ", ";
      }
    }
    s << "}";
    if (i < (rhs.getRows() -1)){
	s << ",\n";
      }
  }

  s << " ]";

  return s;
}

  

#endif
