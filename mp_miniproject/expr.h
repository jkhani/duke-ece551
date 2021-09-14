#ifndef __EXPR_H___
#define __EXPR_H___
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <assert.h>
// expr.h defines the Expression class and subclasses (Modified from 083)

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
  virtual double evaluate() const = 0;
  virtual double evaluate(std::vector<std::string> paramVec, std::vector<double> inputArgs) const = 0;
};

class NumExpression: public Expression {
 private:
  double value;
 public:
 NumExpression(double num): value(num) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << value;
    std::string result = ss.str();
    return result;
  }
  virtual ~NumExpression() {}
  virtual double evaluate() const {
    return value;
  }
  virtual double evaluate(std::vector<std::string> paramVec, std::vector<double> inputArgs) const {
    return value;
  }
};

class VarExpression: public Expression {
 private:
  std::string variable;
 public:
 VarExpression(std::string var): variable(var){}
  virtual std::string toString() const {
    return variable;
  }
  virtual double evaluate() const {
    return 0;
  }
  virtual double evaluate(std::vector<std::string> paramVec, std::vector<double> inputArgs) const {
    for(size_t i = 0; i < paramVec.size(); i++){
      if(paramVec[i] == variable){
	return inputArgs[i];
      }
    }
    std::cerr << variable << " not member of paramater vector!\n";
    return 0;
  }
  virtual ~VarExpression() {}
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
  virtual double evaluate() const {
    double lhs = leftArg->evaluate();
    double rhs = rightArg->evaluate();
    return lhs + rhs;
  }
  virtual double evaluate(std::vector<std::string> paramVec, std::vector<double> inputArgs) const {
    double lhs = leftArg->evaluate(paramVec, inputArgs);
    double rhs = rightArg->evaluate(paramVec, inputArgs);
    return lhs + rhs;
  };
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
  virtual double evaluate() const {
    double lhs = leftArg->evaluate();
    double rhs = rightArg->evaluate();
    return lhs - rhs;
  }
  virtual double evaluate(std::vector<std::string> paramVec, std::vector<double> inputArgs) const {
    double lhs = leftArg->evaluate(paramVec, inputArgs);
    double rhs = rightArg->evaluate(paramVec, inputArgs);
    return lhs - rhs;
  };

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
  virtual double evaluate() const {
    double lhs = leftArg->evaluate();
    double rhs = rightArg->evaluate();
    return lhs * rhs;
  }
  virtual double evaluate(std::vector<std::string> paramVec, std::vector<double> inputArgs) const {
    double lhs = leftArg->evaluate(paramVec, inputArgs);
    double rhs = rightArg->evaluate(paramVec, inputArgs);
    return lhs * rhs;
  };
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
  virtual double evaluate() const {
    double lhs = leftArg->evaluate();
    double rhs = rightArg->evaluate();
    return lhs / rhs;
  }
  virtual double evaluate(std::vector<std::string> paramVec, std::vector<double> inputArgs) const {
    double lhs = leftArg->evaluate(paramVec, inputArgs);
    double rhs = rightArg->evaluate(paramVec, inputArgs);
    return lhs / rhs;
  };
};

class ModExpression: public Expression {
 private:
  Expression * leftArg;
  Expression * rightArg;
 public:
 ModExpression(Expression * lhs, Expression * rhs): leftArg(lhs), rightArg(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << leftArg->toString() << " % " << rightArg->toString() << ")";
    std::string result = ss.str();
    return result;
  }
  virtual ~ModExpression() {
    delete leftArg;
    delete rightArg;
  }
  virtual double evaluate() const {
    double lhs = leftArg->evaluate();
    double rhs = rightArg->evaluate();
    return fmod(lhs, rhs);
  }
  virtual double evaluate(std::vector<std::string> paramVec, std::vector<double> inputArgs) const {
    double lhs = leftArg->evaluate(paramVec, inputArgs);
    double rhs = rightArg->evaluate(paramVec, inputArgs);
    return fmod(lhs, rhs);
  };
};

class SinExpression: public Expression {
 private:
  Expression * inputTheta;
 public:
 SinExpression(Expression * theta): inputTheta(theta) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "sin( " << inputTheta->toString() << ")";
    std::string result = ss.str();
    return result;
  }
  virtual ~SinExpression() {
    delete inputTheta;
  }
  virtual double evaluate() const {
    double theta = inputTheta->evaluate();
    return sin(theta);
  }
  virtual double evaluate(std::vector<std::string> paramVec, std::vector<double> inputArgs) const {
    double theta = inputTheta->evaluate(paramVec, inputArgs);
    return sin(theta);
  };
};

class CosExpression: public Expression {
 private:
  Expression * inputTheta;
 public:
 CosExpression(Expression * theta): inputTheta(theta) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "cos( " << inputTheta->toString() << ")";
    std::string result = ss.str();
    return result;
  }
  virtual ~CosExpression() {
    delete inputTheta;
  }
  virtual double evaluate() const {
    double theta = inputTheta->evaluate();
    return cos(theta);
  }
  virtual double evaluate(std::vector<std::string> paramVec, std::vector<double> inputArgs) const {
    double theta = inputTheta->evaluate(paramVec, inputArgs);
    return cos(theta);
  };
};

class SqrtExpression: public Expression {
 private:
  Expression * root;
 public:
 SqrtExpression(Expression * rt): root(rt) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "sqrt( " << root->toString() << ")";
    std::string result = ss.str();
    return result;
  }
  virtual ~SqrtExpression() {
    delete root;
  }
  virtual double evaluate() const {
    double rt = root->evaluate();
    return sqrt(rt);
  }
  virtual double evaluate(std::vector<std::string> paramVec, std::vector<double> inputArgs) const {
    double rt = root->evaluate(paramVec, inputArgs);
    return sqrt(rt);
  };
};

class LogExpression: public Expression {
 private:
  Expression * number;
 public:
 LogExpression(Expression * num): number(num) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "log( " << number->toString() << ")";
    std::string result = ss.str();
    return result;
  }
  virtual ~LogExpression() {
    delete number;
  }
  virtual double evaluate() const {
    double num = number->evaluate();
    return log(num);
  }
  virtual double evaluate(std::vector<std::string> paramVec, std::vector<double> inputArgs) const {
    double num = number->evaluate(paramVec, inputArgs);
    return log(num);
  };
};

class PowExpression: public Expression {
 private:
  Expression * base;
  Expression * exponent;
 public:
 PowExpression(Expression * lhs, Expression * rhs): base(lhs), exponent(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "pow(" << base->toString() << ", " << exponent->toString() << ")";
    std::string result = ss.str();
    return result;
  }
  virtual ~PowExpression() {
    delete base;
    delete exponent;
  }
  virtual double evaluate() const {
    double lhs = base->evaluate();
    double rhs = exponent->evaluate();
    return pow(lhs,rhs);
  }
  virtual double evaluate(std::vector<std::string> paramVec, std::vector<double> inputArgs) const {
    double lhs = base->evaluate(paramVec, inputArgs);
    double rhs = exponent->evaluate(paramVec, inputArgs);
    return pow(lhs,rhs);
  };
};


#endif
