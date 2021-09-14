#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>
#include <math.h>
#include <vector>
#include <limits>
#include "expr.h"

/*
Function class objects inherit the virtual evaulate and toString methods from our Expression class
from 083. The Function class has fields to store the function definitions after parsing.
*/

class Function: public Expression {
 private:
  std::string functionName;
  std::vector<std::string> paramVec; // string vector of variable names for the parameters
  Expression * expression;
 public:
  // default constructor
 Function(): functionName(), paramVec(), expression(NULL) {
    // std::cout << "construct: " << functionName << "=" << expression << "\n";
  }
 Function(std::string fname, std::vector<std::string> pv):  functionName(fname), paramVec(pv), expression(NULL) {}
 Function(std::string fname, std::vector<std::string> pv, Expression * expr):  functionName(fname), paramVec(pv), expression(expr) {}

  // destructor
  ~Function() {
    paramVec.clear();
    delete expression;
  }

  // returns the function expression
  virtual std::string toString() const {
    if (expression != NULL){
      std::stringstream ss;
      ss << expression->toString();
      std::string result = ss.str();
      return result;
    }
    // prevent SEGFAULT during testing
    return "NULL";
  }

  std::string getFName() const {
    return functionName;
  }

  // returns vector of variable names
  std::vector<std::string> getPV() const {
    return paramVec;
  }

  // assignExpr allows for inputing an expression to an already instantiated Function object
  void assignExpr(Expression * expr){
    expression = expr;
  }

  Expression * getExpr() const {
    return expression;
  }

  size_t numParams() const {
    return paramVec.size();
  }

  virtual double evaluate() const{
    double result = expression->evaluate();
    return result;
  }

  virtual double evaluate(std::vector<std::string> pv, std::vector<double> input) const {
    if(pv == getPV() && pv.size() == input.size()){
      double result = expression->evaluate(pv,input);
      return result;
    }

    std::cerr << "Wrong number of arguments for this function!\n";
    return NAN;
  }
};


#endif
