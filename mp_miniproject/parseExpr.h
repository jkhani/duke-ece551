#ifndef __PARSEEXPR_H__
#define __PARSEEXPR_H__
#include <vector>
#include <iterator>
#include "expr.h"
#include "function.h"
#include "common.h"


// getResults initialized here for recursive calls between parseInputArgs and getResults
double getResult(std::string str, std::map<std::string, Function *> &fm);

/*
parseInputArgs works recursively with getResuls. Returns vector of input arguments. Calls
getResults when a function is found in the input vector for the main function being evaluated.
*/
std::vector<double> parseInputArgs(std::string str, std::map<std::string, Function *> &fm){
  std::vector<double> args;
  double val;
  std::stringstream ss(str);
  std::string temp;

  while(ss >> temp){
    if(temp.at(0) == '('){
      val = getResult(str, fm);
      if(val == val){
	args.push_back(val);
      }
      else{
	std::cerr << "Could not evaluate function!\n";
	return std::vector<double>();
      }

      str = str.substr(2,std::string::npos);
      std::string tempStr(str,0,std::string::npos);

      tempStr = str.substr(str.find_first_of(')') + 1, std::string::npos);

      str = tempStr;
	
      std::stringstream tempSS(str);
      ss.swap(tempSS);
    }
    else{
      if(temp.find(')') != std::string::npos){
	temp = temp.substr(0, temp.find_first_of(')'));
	
	if(is_digits(temp)){
	  val = convertToDouble(temp);
	  args.push_back(val);
	}
	
	break;
      }
      if(is_digits(temp)){
	val = convertToDouble(temp);
	args.push_back(val);
      }
    }
  }

  return args;
}

/*
getResults works recursively with parseInputArgs to provide the input arguments to the 
main function being evaluated. Evaluates any functions in the input to the main function
and returns the value so that it can be added to the vector of input arguments.
*/
double getResult(std::string str, std::map<std::string, Function *> &fm){
  double val = NAN;
  std::string fname = parsefName(str);

  if(isfNameDefined(fname,fm)){
    str = str.substr(str.find_first_of(fname) + 1, std::string::npos);
    Function * f = fm.find(fname)->second;
    std::vector<std::string> pv = f->getPV();
    std::vector<double> args = parseInputArgs(str,fm);

    val = f->evaluate(pv,args);
  }

  return val;  
}

/*
(Modified from expr.cpp in assignment 083)
makeExpr creates the appropriate Expression subclass object given the operation
string, lefthand argument, and righhand argument.
*/
Expression * makeExpr(std::string & op, Expression * lhs, Expression * rhs){
  if(op[0] == '+'){return new PlusExpression(lhs,rhs);}
  else if(op[0] == '-'){return new MinusExpression(lhs,rhs);}
  else if(op[0] == '*'){return new TimesExpression(lhs,rhs);}
  else if(op[0] == '/'){return new DivExpression(lhs,rhs);}
  else if(op[0] == '%'){return new ModExpression(lhs,rhs);}
  else if(op == "pow"){return new PowExpression(lhs,rhs);}
  else if(op == "sqrt"){return new SqrtExpression(lhs);}
  else if(op == "sin"){return new SinExpression(lhs);}
  else if(op == "cos"){return new CosExpression(lhs);}
  else if(op == "log"){return new LogExpression(lhs);}
  else if(op == "pow"){return new PowExpression(lhs,rhs);}
  else{
    std::cerr << "Invalid op.\n";
  }
  return NULL;
}

// parseExpr initialized here for recursive calls between parseExpr and parseOp
Expression * parseExpr(std::string str, Function * f, std::map<std::string, Function *> &fm);

/*
(Modified from expr.cpp in assignment 083)
parseOp acts recursively along with parseExpr to get operation string, lefthand argument,
and righthand argument from an input string. Also takes a Function pointer and 
function map to check if a previously defined function is part of the input string.
*/
Expression * parseOp(std::string str, Function * f, std::map<std::string, Function *> &fm){
  std::stringstream ss(str);
  std::string op;

  ss >> op;

  if(!isValidOp(op)) {
    std::cerr << "Invalid op: " << op << "\n";
    return NULL;
  }

  str = str.substr(op.size()+1,std::string::npos);
  Expression * lhs = parseExpr(str,f,fm);
  if (lhs == NULL){
    return NULL;
  }

  Expression * rhs;

  if(isSingleArgOp(op)){
    str = str.substr(lhs->toString().length(),std::string::npos);
    rhs = NULL;
  }
  else{
    str = str.substr(lhs->toString().length()+1,std::string::npos);
    rhs = parseExpr(str,f,fm);
    if(rhs == NULL){
      delete lhs;
      return NULL;
    }
  }

  if(rhs != NULL){
    str = str.substr(rhs->toString().length(),std::string::npos);
  }

  if(str.at(0) == ')'){
    return makeExpr(op,lhs,rhs);
  }

  std::cerr << "Expected ')' but found " << str << "!\n";

  delete lhs;
  delete rhs;
  return NULL;
}

/*
(Modified from expr.cpp in assignment 083)
parseExpr acts recursively along with parseOp to get operation string, lefthand argument,
and righthand argument from an input string. Also takes a Function pointer and 
function map to check if a previously defined function is part of the input string.
*/
Expression * parseExpr(std::string str, Function * f, std::map<std::string, Function *> &fm){
  std::stringstream ss(str);
  std::string id;

  ss >> id;
  
  if(id.find(')') != std::string::npos){
    id = id.substr(0,id.find_first_of(')'));
  }
  if(id == "\n" || id == "\0" || id.at(0) == ')'){
      std::cerr << "Invalid argument!\n";
      return NULL;
  }

  if(id.find('(') == 0){
    str = str.substr(str.find_first_of('(') + 1,std::string::npos);
    return parseOp(str,f,fm);
  }

  else if(is_digits(id)){
    double num = convertToDouble(id);
    return new NumExpression(num);
  }
  else{
    std::vector<std::string> tempPV = f->getPV();
    if(isMemberParamVec(id,tempPV)){
      return new VarExpression(id);
    }
    else{
      std::cerr << id << " not member of the paramater vector for "
		<< f->getFName() << "()\n";
    }
  }

  return NULL;
}

#endif
