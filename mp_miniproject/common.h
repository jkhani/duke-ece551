#ifndef __COMMON_H__
#define __COMMON_H__
#include "expr.h"
#include "function.h"
// common.h contains helpful bools and other functions for numerics program

/*
printPV takes a vector and prints its contents. It is templated in order to 
print vector of strings when printing parameter vector or vector of doubles
when printing input arguments to a function.
*/
template<typename T>
void printPV(std::vector<T> &pv){
  for(size_t i = 0; i < pv.size(); ++i){
    std::cout << pv[i];
    if (i < (pv.size() - 1)){
      std::cout << " ";
    }
  }
}

/*
FOR TESTING, SHOW MAP CONTENTS
*/
void printFMap(std::map<std::string, Function *> &fm){
  std::map<std::string, Function *>::iterator it = fm.begin();
  std::cout << "Functions in fMap: \n";
  std::vector<std::string> pv;

  while (it != fm.end()){
    std::cout << it->first << "(";
    pv = it->second->getPV();
    printPV(pv);
    std::cout << ") = " << it->second->toString() << "\n";
    ++it;
  }
}

/*
deleteFMap takes a pointer to a function map then iterates through to delete the
Function pointers then erases all the contents
*/
void deleteFMap(std::map<std::string, Function *> * fm){
  std::map<std::string, Function *>::iterator it = fm->begin();
  while(it != fm->end()){
    delete it->second;
    it++;
  }

  fm->erase(fm->begin(),fm->end());
}

/*
removeSpaces takes a string and removes extra spaces between tokens.
Standardizes string for parsing expressions.
*/
std::string removeSpaces(std::string str){
  std::stringstream ss(str);
  std::stringstream newStr;
  std::string temp;
  while(ss >> temp){
    newStr << temp << " ";
  }

  return newStr.str();
}

std::string getToken(std::string &str){
  std::stringstream ss(str);
  std::string token;
  ss >> token;
  
  return token;
}

/*
convertToDouble takes a string and converts to double
*/
double convertToDouble(std::string id){
  double num;
  std::stringstream convert(id);
  convert >> num;

  return num;
}  

/*
isValidExprStr takes a string and ensures the parentheses are balanced
*/

bool isValidExprStr(std::string str){
  return std::count(str.begin(),str.end(),'(') == std::count(str.begin(),str.end(),')');
}

/*
isValidOp takes a operation string and returns true if it is a member of the set
of valid operations
*/
bool isValidOp(std::string & op){
  std::string tmp[] = {"+","-","*","/","%","sin","cos","sqrt","log","pow"};
  std::set<std::string> validOps(tmp, tmp + sizeof(tmp) / sizeof(tmp[0]));

  return validOps.find(op) != validOps.end();
}

/*
isSingleArgOp takes a operation string and returns true if it is a member of the set
of valid operations
*/
bool isSingleArgOp(std::string & op){
  std::string tmp[] = {"sin","cos","sqrt","log"};
  std::set<std::string> validOps(tmp, tmp + sizeof(tmp) / sizeof(tmp[0]));

  return validOps.find(op) != validOps.end();
}

/*
isValidCommand takes a command string and returns true if it is a member of the set
of valid commands
*/
bool isValidCommand(std::string & com){
  // set of all valid commands
  std::string tmp[] = {"define","evaluate","numint","mcint","max","min","//"};
  std::set<std::string> validComs(tmp, tmp + sizeof(tmp) / sizeof(tmp[0]));

  return validComs.find(com) != validComs.end();
}

/*
is_digits checks if string contains only numbers. returns true if string is made
up of only digits, negative sign, or decimal
*/
bool is_digits(std::string & str)
{
  return str.find_first_not_of("0123456789-.") == std::string::npos;
}

/*
isValidDefine takes a define string to ensure it has opening and closing
parentheses and only 1 = sign
*/
bool isValidDefine (std::string & str){
  return str.find('(') != std::string::npos &&
    // should only have 1 '=' sign
    std::count(str.begin(),str.end(),'=') == 1 &&
    str.find(')') != std::string::npos;
}

/*
isValidParam ensures the parameters for the function definition do not include parentheses
or consists of only numbers
*/
bool isValidParam(std::string & p){
  return !is_digits(p) &&
    p.find('(') == std::string::npos &&
    p.find(')') == std::string::npos;
}

/*
isMemberParamVec checks if parameter name already exists in the parameter
vector. Ensures there are no repeated parameter names.
*/
bool isMemberParamVec(std::string p, std::vector<std::string> &pv){
  return find(pv.begin(), pv.end(), p) != pv.end();
}

/*
isfNameDefined takes a function name string and a reference to the function map
returns true if function identified by fn is already defined
*/
bool isfNameDefined (std::string fn, std::map<std::string, Function *> &fm){
  std::map<std::string, Function *>::iterator it = fm.find(fn);

  return it != fm.end();
}

/*
parseParamVec parses and returns paramter vector from initializer string (lhs)
*/
std::vector<std::string> parseParamVec (std::string & initStr){
  std::stringstream ss(initStr);
  std::vector<std::string> pv;
  std::string param;

  while(ss >> param){
    if(!isValidParam(param)){
      std::cerr << "Invalid parameter.\n";
      return std::vector<std::string>();
    }
    if(isMemberParamVec(param,pv)){
      std::cerr << "Ignored repeated parameter name.\n";
      continue;
    }
    pv.push_back(param);
  }

  return pv;
}

/*
parsefName takes a string and returns the function name
*/
std::string parsefName (std::string & str){
  std::string fname = getToken(str);

  // remove first opening (
  if(fname.find('(') == 0){
    fname = fname.substr(1,std::string::npos);
  }

  return fname;
}

#endif
