#ifndef __COMMANDS_H__
#define __COMMANDS_H__
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include "gradient.h"
#include "integrate.h"
#include "common.h"
#include "expr.h"
#include "function.h"
#include "parseExpr.h"
// commands.h controls the execution of commands for numerics program

/*
printEvalStr takes a Function pointer and prints the evaluate statement
indicating what function was called, the arguments input to the function,
and the results of evalauting the function.
*/
void printEvalStr(Function * f, std::vector<double> args){
  std::string fname = f->getFName();
  std::vector<std::string> pv = f->getPV();
  double result = f->evaluate(pv, args);

  if(result == result){
    std::cout << fname << "(";
    printPV(args);
    std::cout << ") = " << result << "\n";
  }
}

/*
printDefineStr takes a Function pointer and prints the define statement 
indicating what function was defined including the parameter vector
*/
void printDefineStr (Function * f){
  std::string fname = f->getFName();
  std::vector<std::string> pv = f->getPV();
  std::cout << "defined " << fname << "(";

  for(std::vector<std::string>::const_iterator i = pv.begin(); i != pv.end(); ++i){
    std::cout << *i;
    if(i != pv.end()-1){
      std::cout << " ";
    }
  }

  std::cout << ")" << "\n";
}

/*
printIntStatement prints a statement indicating the results of integration and indicates whether
Numerical integration or Monte Carlo integration was used. (Specifics for this print statement 
were not provided so it was designed to provide all the information about the parameters 
for the numerical integration.
*/
void printIntStatement(std::string com, Function * f, double steps, std::vector<double> low,
		       std::vector<double> high, double result){
  std::string fname = f->getFName();
  std::vector<std::string> pv = f->getPV();

  std::cout << com << "(" << fname << "(";
  printPV(pv);
  std::cout << ")) = " << result << " given from low: ";
  printPV(low);
  std::cout << " to high: ";
  printPV(high);
  if(com == "numint"){
    std::cout << " in steps of " << steps << "\n";
  }
  else{
    std::cout << " given " << steps << " trials\n";
  }
}

/*
printGradStatement
*/
void printGradStatement(std::string com, Function * f, double result){
  std::string fname = f->getFName();
  std::vector<std::string> pv = f->getPV();

  std::cout << com << "(" << fname << "(";
  printPV(pv);
  std::cout << ")) = " << result << "\n";
}

/*
findGradient uses the gradient to find the max or min of a function.
*/
void findGradient(std::string com, std::string &line, std::map<std::string, Function *> &fm){
  std::string fname = parsefName(line);
  if(!isfNameDefined(fname, fm)){
    std::cerr << fname << " not defined!\n";
  }
  else{
    Function * f = fm.find(fname)->second;
    std::string evalStr(line, line.find(fname) + fname.size(), std::string::npos);
    std::stringstream ss(evalStr);
    std::string id;
    ss >> id;
    if(!is_digits(id)){
      std::cerr << "Invalid gamma value!\n";
    }
    double gamma = convertToDouble(id);
    ss >> id;
    if(!is_digits(id)){
      std::cerr << "Invalid converged distance value!\n";
    }
    double convergedDistance = convertToDouble(id);

    size_t pnum = f->numParams();
    size_t i = 0;
    std::vector<double> startingPoints;

    while(ss >> id){
      ++i;
      if(!is_digits(id)){
	std::cerr << "Invalid value for starting points!\n";
	return;
      }

      double point = convertToDouble(id);
      startingPoints.push_back(point);

      if(i == pnum){
	break;
      }
    }

    ss >> id;
    if(!is_digits(id)){
      std::cerr << "Invalid number of steps!\n";
    }
    double numSteps = convertToDouble(id);

    double result = 0;
    if(com == "max"){
      result = ascent(f,gamma,convergedDistance,startingPoints,numSteps);
    }
    else{
      result = descent(f,gamma,convergedDistance,startingPoints,numSteps);
    }

    printGradStatement(com, f, result);
  }
}

/*
integrateFunc works for either numint or mcint. Parses the input string to get the function, 
stepsize/ number of trials, and range for each parameter. Then calls numIntegrate to compute 
the integral using the mid-point rectangular method if the command is 'numint' and the Monte 
Carlo methd if the command is 'mcint'.
*/
void integrateFunc(std::string com, std::string &line, std::map<std::string, Function *> &fm){
  std::string fname = parsefName(line);
  if(!isfNameDefined(fname, fm)){
    std::cerr << fname << " not defined!\n";
  }
  else{
    Function * f = fm.find(fname)->second;
    std::string evalStr(line, line.find(fname) + fname.size(), std::string::npos);
    std::stringstream ss(evalStr);
    std::string id;
    ss >> id;
    // step size for numint and number of trials for mcint
    double step = convertToDouble(id);
    if(step <= 0){
      std::cerr << "Invalid step size!\n";
      return;
    }
    std::vector<double> low;
    std::vector<double> high;

    size_t count = 1;
    while(ss >> id){
      if(!is_digits(id)){
	std::cerr << "Integral bounds must be numbers!\n";
	return;
      }
      double val = convertToDouble(id);

      if((count % 2) == 0){
	if(val <= low.back()){
	  std::cerr << "Invalid ranges! The high value must be greater than the low boundary!\n";
	  return;
	}
	high.push_back(val);
      }
      else{
	low.push_back(val);
      }
      count++;      
    }

    if(low.size() != high.size() || low.size() != f->numParams()){
      std::cerr << "Number of ranges not correct!\n";
      return;
    }

    double result = 0;

    if(com == "numint"){
      result = numIntegrate(f,step,low,high);
    }
    else{
      double numTrials = step;
      result = mcIntegrate(f,numTrials,low,high);
    }

    printIntStatement(com,f,step,low,high,result);
  }
}

/*
evaluateFunc takes a string and the Function map, parses the main function, 
gets input arguments to the main funciton, then calls print function for
evaluate statements.
*/
void evaluateFunc(std::string &line, std::map<std::string, Function *> &fm){

  std::string fname = parsefName(line);
  if(isfNameDefined(fname,fm)){
    Function * f = fm.find(fname)->second;
    std::string evalStr(line,line.find(fname) + fname.size(),std::string::npos);
    
    std::vector<double> args = parseInputArgs(evalStr,fm);
    
    printEvalStr(f,args);

  }
  else{
    std::cerr << fname << " has not been defined!\n";
  }
}

/*
defineFunc takes a string and the Function map, parses the string for the
function name and parameter vector, creates a new Function object, gets the
Function expression, adds the funtion to the map, then prints a statement
indicating what function was defined.
*/
void defineFunc(std::string &line, std::map<std::string, Function *> &fm) {
  if(!isValidDefine(line)){
    std::cerr << "Invalid string for define command!\n";
    return;
  }
  else{
    std::string fname = parsefName(line);
    if(isfNameDefined(fname,fm)){
      std::cerr << fname << " is already defined!\n";
      return;
    }
    if(is_digits(fname)){
      std::cerr << "Function names cannot be numbers!\n";
      return;
    }

    // parse initializer string (string to define function)
    size_t initStart = line.find(fname) + fname.size();
    size_t initStop = line.find(')');
    size_t initLength = initStop - initStart;

    std::string initStr(line, initStart,initLength);
    std::vector<std::string> paramVec = parseParamVec(initStr);

    if(paramVec.size() > 0){
      Function * func = new Function(fname,paramVec);
      std::string exprStr(line,line.find('=') + 1, std::string::npos);

      Expression * expr = parseExpr(exprStr, func, fm);
      if(expr != NULL){
	func->assignExpr(expr);
	fm.insert(std::pair<std::string, Function *>(func->getFName(),func));
	printDefineStr(func);

	return;
      }
      else{
	std::cerr << "Could not parse expression!\n";
	delete func;
	return;
      }
    }
    else {
      std::cerr << "Function must have at least 1 input argument!\n";
      return;
    }
  }
}

/*
evalCommand takes a command string, a line string of everything following the command, 
and a reference to the function map.
*/
void evalCommand(std::string com, std::string & line, std::map<std::string, Function *> & fm){
  // first check for valid command before proceeding
  if(!isValidCommand(com)){
    std::cerr << com << " is not a valid command!\n";
    return;
  }

  if(com == "define"){
    if(!isValidExprStr(line)){
      std::cerr << "Parentheses not balanced!\n";
      return;
    }
    defineFunc(line, fm);
  }
  else if(com == "evaluate"){
    if(!isValidExprStr(line)){
      std::cerr << "Parentheses not balanced!\n";
      return;
    }
    evaluateFunc(line,fm);
  }
  else if(com == "numint" || com == "mcint"){
    integrateFunc(com, line, fm);
  }
  else if(com == "max" || com == "min"){
    findGradient(com, line, fm);
  }
  else if(com == "//"){
    std::cout << "Comment: " << line << "\n";
  }
}

#endif
