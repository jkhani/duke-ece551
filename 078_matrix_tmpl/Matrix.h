#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___
#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

//YOUR CODE GOES HERE!

template<typename T>
class Matrix{
 private:
  int numRows;
  int numColumns;
  vector< vector<T> > rows;

 public:
  //default constructor
 Matrix():numRows(0),numColumns(0){
  }
 Matrix(int r, int c):numRows(r), numColumns(c) {
    assert(numRows >= 0 && numColumns >=0);
    for (int i = 0; i < numRows; i++){
      rows.push_back(vector<T>(numColumns));
    }
  }
  //copy constructor
 Matrix(const Matrix & rhs):numRows(rhs.getRows()),numColumns(rhs.getColumns()){
    for (int i = 0; i < numRows; i++){
      rows.push_back(rhs[i]);
    }
  }
  //destructor
  ~Matrix() {
    for (int i = 0; i < numRows; i++){
      rows[i].clear();
    }
    rows.clear();
  }
  //assigment operator
  Matrix & operator=(const Matrix & rhs) {
    if(&rhs == this){ return *this;}
    for (int i = 0; i <numRows; i++){
      rows[i].clear();
    }
    rows.clear();
    numRows = rhs.getRows();
    numColumns = rhs.getColumns();
    for (int i = 0; i < numRows; i++){
      rows.push_back(rhs[i]);
    }
    return *this;
  }

  int getRows() const { return numRows;}
  int getColumns() const { return numColumns;}
  const vector<T>  & operator[](int index) const {
    assert(index >= 0 && index <= numRows-1);
      return rows[index];
    }
  vector<T> & operator[](int index){
      assert(index >= 0 && index <= numRows-1);
      return rows[index];
    }
  bool operator==(const Matrix & rhs) const {
      if(&rhs == this){ return 1;}
      if (numRows != rhs.getRows() || numColumns != rhs.getColumns()){
	return 0;
      }
      else{
	for(int i = 0; i < numRows; i++){
	  if (rows[i] != (rhs[i])){
	    return 0;
	  }
	}
      }
      return 1;
    }
    Matrix operator+(const Matrix & rhs) const {
      assert( (numRows == rhs.getRows()) && (numColumns == rhs.getColumns()));
      Matrix matrix(*this);
      for (int i = 0; i < numRows; i ++){
	for (int j = 0; j < numColumns; j++){
	  matrix[i][j] += rhs[i][j];
	}
      }
      return matrix;
    }
  };


  template<typename S>
    std::ostream & operator<<(std::ostream & s, const Matrix<S> & rhs) {
    if( rhs.getRows() == 0 ){
      s <<"[  ]";
    }
    else
      {
	std::cout << "[ {";
	for (int i = 0; i < rhs.getRows(); i++){
	  for (int j = 0; j < rhs.getColumns(); j++){
	    s << rhs[i][j];
	    if (j < rhs.getColumns()-1){
	      s<<", ";
	    }
	  }
	  if (i < rhs.getRows()-1){
	    s << "},\n{";
	  }
	}
	s<<"} ]";
      }
    return s;
  }

#endif
