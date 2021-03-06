#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "function.h"
#include "expr.h"

// checks for valid 'define' command strings
bool isValidDefine (std::string str){
  if((str.find('(') != std::string::npos) &&
     // should only have 1 '=' sign
     (std::count(str.begin(),str.end(),'=') == 1) &&     
     (str.find(')') != std::string::npos)) {
    return true;
  }

  return NULL;
}

// checks for valid 'evaluate' command strings
bool isValidEval (std::string str){
  if((str.find("(") != std::string::npos) &&
     (str.find('=') == std::string::npos) &&
     (str.find(')') != std::string::npos)) {
    return true;
  }

  return NULL;
}

// parses and returns function name from initializer string
std::string parsefName(std::string str){
  std::stringstream ss(str);
  std::string fname;

  ss >> fname;

  return fname;
}

// parse and returns paramter vector from initializer string
std::vector<std::string> parseParamVec (std::string str){
  std::stringstream ss(str);
  std::vector<std::string> pv;
  std::string param;

  ss >> param;

  while(ss >> param){
    pv.push_back(param);
  }

  return pv;
}

// prints the define statement indicating what function was defined
void printDefineStr (std::string fname, std::vector<std::string> pv){
  std::cout << "defined " << fname << "(";

  for(std::vector<std::string>::const_iterator i = pv.begin(); i != pv.end(); ++i){
    std::cout << *i;
    if(i != pv.end()-1){
      std::cout << " ";
    }
  }

  std::cout << ")" << "\n";

}

// prints the evaluate statement indicating the function evaluated and returned value
void printEvalStr (std::string fname, std::vector<std::string> pv, double val){
  std::cout << fname << "(";

  for(std::vector<std::string>::const_iterator i = pv.begin(); i != pv.end(); ++i){
    std::cout << *i;
    if(i != pv.end()-1){
      std::cout << " ";
    }
  }

  std::cout << ") = " << val << "\n";

}

// parses define string and returns a Function pointer with fields determined by input string
Function * doDefine (std::string str){
  size_t initStart = str.find_first_of('(') + 1;
  size_t initStop = str.find('=');

  size_t initLength = initStop - initStart;
  std::string initStr(str,initStart,initLength);

  initStr = initStr.substr(0,initStr.find_last_of(')'));
  
  std::string fname = parsefName(initStr);
  std::vector<std::string> paramVec = parseParamVec(initStr);

  printDefineStr(fname, paramVec);

  // parse expression string for function starting after = sign
  std::string exprStr(str,initStop+1,std::string::npos);
  exprStr = exprStr.substr(exprStr.find_first_of('('),exprStr.find_last_of(')'));

  return new Function(fname, paramVec, exprStr);  
}

// declare above for recursive calling
Expression * parse(const char ** strp);

void skipSpace(const char ** strp) {
  while(isspace(**strp)) {
    *strp = *strp + 1;
  }
}

Expression * makeExpr(char op, Expression * lhs, Expression * rhs) {
  switch(op) {
  case '+':
    return new PlusExpression(lhs,rhs);
  case '-':
    return new MinusExpression(lhs,rhs);
  case '*':
    return new TimesExpression(lhs,rhs);
  case '/':
    return new DivExpression(lhs,rhs);
  default:
    std::cerr << "Impossible op char: " << op << "\n";
    abort();
  }
}
bool isValidOp(char c) {
  return strchr("+-*/", c) != NULL;
}


Expression * parseOp(const char ** strp) {
  skipSpace(strp);
  char op = **strp;
  if (!isValidOp(op)) {
    std::cerr << "Invalid op: "<< op<< "\n";
    return NULL;
  }
  *strp = *strp + 1;
  Expression * lhs = parse(strp);
  if (lhs == NULL) {
    return NULL;
  }
  Expression * rhs = parse(strp);
  if (rhs == NULL) {
    delete lhs;
    return NULL;
  }
  skipSpace(strp);
  if (**strp == ')') {
    *strp = *strp + 1;
    return makeExpr(op,lhs,rhs);
  }
  std::cerr <<"Expected ) but found " << *strp << "\n";
  delete lhs;
  delete rhs;
  return NULL;
}
Expression * parse(const char ** strp) {
  skipSpace(strp);
  if (**strp == '\0') {
    std::cerr << "End of line found mid expression!\n";
    return NULL;
  }
  else if (**strp == '(') {
    *strp = *strp + 1;
    return parseOp(strp);
  }
  else {
    //number
    char * endp;
    long num = strtol(*strp, &endp, 10);
    if (endp == *strp) {
      std::cerr << "Expected a number, but found " << *strp << "\n";
      return NULL;
    }
    *strp = endp;
    return new NumExpression(num);
  }
}

// parse evaluate command string
void doEval (std::string str, std::map<std::string, Function *> * fm){
  size_t initStart = str.find_first_of('(') + 1;
  size_t initStop = str.find_last_of(')');
  size_t initLength = initStop - initStart;
  std::string initStr = str.substr(initStart,initLength);

  std::string fname = parsefName(initStr);
  std::vector<std::string> inputArgs = parseParamVec(initStr);

  std::map<std::string, Function *>::iterator it = fm->find(fname);

  // check that function to evaluate is in fmap
  if(it != fm->end()){
    // pull out the functions parameter vector and expression string
    std::vector<std::string> tempPV = it->second->getPV();
    std::string evalStr = it->second->getExpr();

    // replace each instance of the parameter with the corresponding input argument
    for(size_t i = 0; i < tempPV.size(); i++){
      size_t pos = evalStr.find(tempPV[i]);
      while(pos != std::string::npos){
	evalStr.replace(pos, tempPV[i].size(), inputArgs[i]);
	pos = evalStr.find(tempPV[i], pos + tempPV[i].size());
      }
    }

    std::cout << "Gotten this far: " << evalStr << "\n";

    // convert string to char pointer
    const char *evalCharp = evalStr.c_str();

    Expression * expr = parse(&evalCharp);

    if(expr != NULL) {
      double value = expr->evaluate();
      printEvalStr(fname, inputArgs, value);

    }

    delete expr;

  }
}

// delete Function pointers in map then erase all the contents
void deleteFMap(std::map<std::string, Function *> * fm){
  std::map<std::string, Function *>::iterator it = fm->begin();
  while(it != fm->end()){
    delete it->second;
    it++;
  }

  fm->erase(fm->begin(),fm->end());
}

int main(int argc, char** argv){
  std::ifstream ifs(argv[1]);
  std::string str;
  std::map<std::string, Function *> fMap;
  
  // open file
  if(ifs.is_open() && ifs.good()){

    // parse each line one at a time
    while(getline(ifs,str) && !ifs.eof()){
      std::stringstream ss(str);
      std::string command;

      // parse 1st word of string to get command
      ss >> command;

      if(command == "define" && isValidDefine(str)){
	Function * definedFunction = doDefine(str);
	fMap.insert(std::make_pair(definedFunction->getFName(),definedFunction));
      }

      if(command == "evaluate" && isValidEval(str)){
	doEval(str, &fMap);
      }
    }

    deleteFMap(&fMap);
    fMap.clear();
  }

  ifs.close();

  return EXIT_SUCCESS;
}
