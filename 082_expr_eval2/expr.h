#ifndef __EXPR_H___
#define __EXPR_H___
#include <iostream>
#include <cstdlib>
#include <sstream>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression: public Expression {
 private:
  long value;
 public:
  NumExpression(long num): value(num) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << value;
    std::string result = ss.str();
    return result;
  }
  virtual ~NumExpression() {}
};

class PlusExpression: public Expression {
 private:
  Expression * leftArg;
  Expression * rightArg;
 public:
  PlusExpression(Expression * lhs, Expression * rhs): leftArg(lhs), rightArg(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << leftArg->toString() << " + " << rightArg->toString() << ")";
    std::string result = ss.str();
    return result;
  }
  virtual ~PlusExpression() {
    delete leftArg;
    delete rightArg;
  }
};

class MinusExpression: public Expression {
 private:
  Expression * leftArg;
  Expression * rightArg;
 public:
  MinusExpression(Expression * lhs, Expression * rhs): leftArg(lhs), rightArg(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << leftArg->toString() << " - " << rightArg->toString() << ")";
    std::string result = ss.str();
    return result;
  }
  virtual ~MinusExpression() {
    delete leftArg;
    delete rightArg;
  }
};

class TimesExpression: public Expression {
 private:
  Expression * leftArg;
  Expression * rightArg;
 public:
  TimesExpression(Expression * lhs, Expression * rhs): leftArg(lhs), rightArg(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << leftArg->toString() << " * " << rightArg->toString() << ")";
    std::string result = ss.str();
    return result;
  }
  virtual ~TimesExpression() {
    delete leftArg;
    delete rightArg;
  }
};

class DivExpression: public Expression {
 private:
  Expression * leftArg;
  Expression * rightArg;
 public:
  DivExpression(Expression * lhs, Expression * rhs): leftArg(lhs), rightArg(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << leftArg->toString() << " / " << rightArg->toString() << ")";
    std::string result = ss.str();
    return result;
  }
  virtual ~DivExpression() {
    delete leftArg;
    delete rightArg;
  }
};

#endif
