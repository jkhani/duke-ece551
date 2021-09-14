#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <map>
#include "function.h"
//#include "expr.h"

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

// delete Function pointers in map then erase all the contents
void deleteFMap(std::map<std::string, Function *> * fm){
  std::map<std::string, Function *>::iterator it = fm->begin();
  while(it != fm->end()){
    delete it->second;
    it++;
  }

  fm->erase(fm->begin(),fm->end());
}

// FOR TESTING, SHOW MAP CONTENTS
void printFMap(std::map<std::string, Function *> *fm){
  std::map<std::string, Function *>::iterator it = fm->begin();
  std::cout << "Functions in fMap: " << "\n";

  while (it != fm->end()){
    std::cout << it->first << "::" << it->second->getExpr() << "\n";
    it++;
  }
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

  //  ss >> param;

  while(ss >> param){
    // check if parameters for function definition contain ()
    if(param.find('(') != std::string::npos ||
       param.find(')') != std::string::npos){
      std::cout << "Invalid parameter. Can't have '(' or ')' in parameteter." << "\n";
      // if so, return empty string vector
      return std::vector<std::string>();
    }

    // ignores repeated variables and numbers in parameter vector
    if(find(pv.begin(), pv.end(), param) == pv.end() && param.find_first_not_of("0123456789") != std::string::npos){
      pv.push_back(param);
    }
  }

  return pv;
}

// parses define string and returns a Function pointer with fields determined by input string
Function * doDefine (std::string str){
  size_t initStart = str.find_first_of('(') + 1;
  size_t initStop = str.find('=');

  size_t initLength = initStop - initStart;
  std::string initStr(str,initStart,initLength);

  initStr = initStr.substr(0,initStr.find_last_of(')'));

  std::string fname = parsefName(initStr);
  initStr = initStr.substr(initStr.find(fname)+fname.size(),std::string::npos);
  std::vector<std::string> paramVec = parseParamVec(initStr);
  if(paramVec.size() == 0){
    return new Function();
  }

  // parse expression string for function starting after = sign
  std::string exprStr(str,initStop+1,std::string::npos);
  exprStr = exprStr.substr(exprStr.find_first_of('('),exprStr.find_last_of(')'));

  return new Function(fname, paramVec, exprStr);  
}

void doEval (std::string str, std::map<std::string, Function *> * fm) {
  size_t initStart = str.find_first_of('(') + 1;
  size_t initStop = str.find_last_of(')');
  size_t initLength = initStop - initStart;

  std::string evalStr = str.substr(initStart,initLength);

  std::string fname = parsefName(evalStr);

  std::map<std::string, Function *>::iterator it = fm->find(fname);

  if(it == fm->end()){
    std::cout << fname << " not defined.\n";
  }
  else{
    evalStr = evalStr.substr(evalStr.find(fname)+fname.size(),std::string::npos);
    std::vector<std::string> inputArgs = parseParamVec(evalStr);
  }
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

	if(definedFunction->numParams() != 0){
	  printDefineStr(definedFunction->getFName(), definedFunction->getPV());
	  // add new function to fMap
	  fMap.insert(std::make_pair(definedFunction->getFName(),definedFunction));
	}
	else{
	  delete definedFunction;
	  // std::cout << "Invalid function definition.\n";
	}
      }

      if(command == "evaluate" && isValidEval(str)){
	doEval(str, &fMap);
      }

      if(command == "numint"){
	// do numerical integration
      }

      if(command == "mcint"){
	// do monte carlo integration
      }

      if(command == "max"){
	// do gradient ascent
      }

      if(command == "min"){
	// do gradient descent
      }
      
    }

    //    printFMap(&fMap);

    deleteFMap(&fMap);
    fMap.clear();
  }

  ifs.close();

  return EXIT_SUCCESS;
}
