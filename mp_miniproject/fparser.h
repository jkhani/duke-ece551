#ifndef __PARSE_H__
#define __PARSE_H__
#include <cstdio>
#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include "function.h"
#include "numint.h"
#include "gradient.h"
#include "helper.h"
#include <map>
#include <cerrno>
#include <math.h>
#define ASCENT 1010  // :)
#define DESCENT 1101
#define BOO 1011

Expression * exprParse(std::string::iterator & it, std::map<std::string,Function*> & m, Function * f);
double parseFunction(std::string::iterator & it, std::map<std::string,Function*> &m);

std::string getIdString(const std::string & strp){
  std::string temp;
  std::size_t startDef = strp.find("(",0);
  if(startDef == std::string::npos){
    throw "Invalid Id string";
  }
  std::size_t endDef = strp.find(")",0);
  if(endDef == std::string::npos){
    throw "Invalid Id string";
  }
  std::size_t length =endDef - startDef +1;
  temp = strp.substr(startDef,length);
  return temp;
}

std::string getExprString(const std::string & strp){
  std::string temp;
  temp = strp.substr(strp.find_first_of("=")+1);
  return temp;
}

bool containsNumber(std::string & str){
  //For the id's that aren't allowed to contain numbers use this function
  std::string::iterator it = str.begin();
  while(it != str.end()){
    if(isdigit(*it)){
      std::cerr << "This string contains a number. Invalid Id.\n";
      return true;
    }
    ++it;
  }
  return false;
}

bool containsChar(std::string & str){
  std::string::iterator it = str.begin();
  while(it != str.end()){
    if(isalpha(*it)){
      return true;
    }
    ++it;
  }
  return false;
}

Expression * makeExpr(std::string & op, Expression * lhs, Expression * rhs){
  if(op[0] == '+'){return new PlusExpression(lhs,rhs);}
  else if(op[0] == '-'){return new MinusExpression(lhs,rhs);}
  else if(op[0] == '*'){return new TimesExpression(lhs,rhs);}
  else if(op[0] == '/'){return new DivExpression(lhs,rhs);}
  else if(op == "pow"){return new PowExpression(lhs,rhs);}
  else if(op == "sqrt"){return new SqrtExpression(lhs,rhs);}
  else{
    std::cout << "Impossible Case" << std::endl;
    //std::cerr << "What the hell happend!? Invalid op\n";
  }
  return NULL;
}

bool isValidOp(std::string & op){
  std::string validOps ("+-*/ pow sqrt");
  std::size_t found = validOps.find(op);
  if(found != std::string::npos){
    return true;
  }
  return false;
}

bool isFunction(std::string & s, std::map<std::string,Function*> & m){
  std::map<std::string,Function*>::iterator it = m.find(s);
  if(it != m.end()){return true;}
  return false;
}

Expression * parseOp(std::string::iterator & it, std::map<std::string,Function*> & m, Function *f){
  //std::cout << "parsing op..\n";
  skipSpaces(it);
  std::string op = getStringBeforeSpace(it);
  //std::cout << op << std::endl;
  if(isFunction(op, m)){
    //Create a pointer to a new function
    //std::cout<<"Found another function\n";
    std::vector<Expression *> args;
    while(*it != ')'){
      Expression * exp = exprParse(it,m,f);
      if(exp != NULL){
	args.push_back(exp);
      }
      //else{return NULL;}
    }
    std::map<std::string,Function*>::iterator mapit = m.find(op);
    if(args.size() < (*mapit).second->VarSize()){
      //std::cout << "HERE!" <<std::endl;
      if(args.size() > 0){
	for(unsigned i = 0; i < args.size(); ++i){
	  delete args[i];
	  ++it;
	}
      }
      return NULL;
    }
    ++it;
    return new CallExpression(op,(*mapit).second, args);
  }
  else if(!isValidOp(op)){
    //Not a valid operation
    /*
      //This could be a constant of a variable, Lets check...
      if(f->isVar(op) && (*(it+1) == ')')){
         ++it;
         return new VarExpression(op);
      }
      else{
         double num = getDoubleVal(tempIt);
         if(isnan(num)){
            std::cerr << "Invalid op: " << op<< std::endl;
            return NULL;
         }
         else{
            return new NumExpression(num);
         }
	 }*/
    std::cerr << "Invalid op: " << op << std::endl;
    return NULL;
  }
  //What if the valid op is actually a function -_-
  if(f->isVar(op) && (*(it+1)==')')){
    return new VarExpression(op);
  }
  Expression * lhs = exprParse(it, m, f);
  if(lhs == NULL){return NULL;}
  Expression * rhs = exprParse(it, m, f);
  if(rhs == NULL && op != "sqrt"){
    delete lhs;
    return NULL;
  }
  skipSpaces(it); //Check this out deeper
  if(*it == ')'){
    it++;
    return makeExpr(op, lhs, rhs);
  }
  std::cerr <<"Expected ) but found " << *it << std::endl;
  delete lhs;
  delete rhs;
  return NULL;
}


Expression * exprParse(std::string::iterator & it, std::map<std::string,Function*> & m, Function *f){
  // This is implemented recursively to parse through expression, similar
  // to C14, p4
  skipSpaces(it);
  if(*it == '\0'){
    std::cerr << "End of line found mid expression!\n";
    return NULL;
  }
  else if(*it == '('){
    ++it;
    return parseOp(it,m,f);
  }
  else if(isdigit(*it)||*it=='.'||*it=='-'){
    // we assume we've found a number
    // There is the case where we have a variable named with a '.' or '-' (i.e -_-)
    std::string::iterator temp = it;
    double num = getDoubleVal(it);
    if(isnan(num)){
      //Make sure not a variable
      std::string check = getStringBeforeSpace(temp);
      //if(num == 0 && f->isVar(check)){
      if(f->isVar(check)){
	//Assumed wrong this is a variable
	++it;
	return new VarExpression(check);
      }
      else{return NULL;}
    }
    else{
      return new NumExpression(num);
    }
  }
  else{
    // Variable
    //while(*it == ' ' || isdigit(*it)){
    /*while(*it == ' '){
         ++it;
	 }*/
    skipSpaces(it);
    if(*it == ')'){return NULL;} //this added as a check for the sqrt in which theres only 1 param
    std::string var = getStringBeforeSpace(it);
    if(containsNumber(var)){return NULL;}
    ++it;
    if(f->isVar(var)){
      return new VarExpression(var);
    }
    else{
      //delete f;
      std::cerr << "Variable not defined in definition\n";
      return NULL;
    }
  }
  return NULL;
}

void makeValVec(std::string::iterator & it, std::map<std::string,Function*> &m, std::vector<double> & temp){
  double val;
  while(*it != ')'){
    skipSpaces(it);
    if(*it == '('){
      ++it;
      val = parseFunction(it,m);
      if(val == NAN){
	return;
      }
    }
    else if(*it =='\0'){
      std::cerr << "End of line found mid evaluation!\n";
    }
    else{
      val = getDoubleVal(it);
      if(isnan(val)){
	return;
      }
    }
    temp.push_back(val);
  }
  ++it;
}
void getBoundPairs(std::string::iterator & it, std::vector<boundPair> & vec){
  skipSpaces(it);
  while(*it != '\0'){
    double low = getDoubleVal(it);
    //std::cout << "low: " << low << std::endl;
    if(isnan(low)||*it == '\0'){
      throw "Invalid input for bounds";
    }
    double high = getDoubleVal(it);
    //std::cout << "high: " << high << std::endl;
    if(isnan(high) || low >= high){
      throw "Invalid input for bounds";
    }
    vec.push_back(std::make_pair(low,high));
    skipSpaces(it);
  }
}

double numintParse(std::string::iterator & it, std::map<std::string,Function*> &m){
  // STEP 2.
  // 1. Get function name and verify it exists in our map
  std::string fname = getStringBeforeSpace(it);
  //std::cout << "fname: " << fname << std::endl;
  if(isFunction(fname,m)){
    std::map<std::string,Function*>::iterator mapIt = m.find(fname);
    // 2. Get the double value for our step size.
    double stepSz = getDoubleVal(it);
    if(isnan(stepSz) || *it == '\0' || (stepSz <= 0)){
      throw "Invalid numint Expression";
    }
    //std::cout << "step: " << stepSz << std::endl;
    // 3. Get the pairs of bounds
    std::vector<boundPair> vecbounds;
    try{getBoundPairs(it,vecbounds);
    }catch(const char * msg){
      throw msg;
    }
    //std::cout <<"vector created of size: "<<vecbounds.size()<<std::endl;
    // 4. Integrate
    if(vecbounds.size() != (*mapIt).second->VarSize()){
      throw "Vectors must be of matching sizes";
    }
    double result;
    try{result = integrate((*mapIt).second, vecbounds, stepSz);}
    catch(const char *msg){
      //std::cerr << msg << std::endl;
      throw msg;
    }
    return result;
  }
  else{
    std::cerr << "Not a valid function. Cannot Integrate...\n";
    return NAN;
  }
}

double mcintParse(std::string::iterator & it, std::map<std::string,Function*> &m){
  // STEP 3.
  // 1. Get function and verify in map
  std::string fname = getStringBeforeSpace(it);
  //std::cout << "fname: " << fname << std::endl;
  if(!isFunction(fname,m)){
    std::cerr << "Not a valid function. No Monte Carlo integration...\n";
    return NAN;
  }
  std::map<std::string,Function*>::iterator mapIt = m.find(fname);
  // 2. Get number of trials to perform
  double trials = getDoubleVal(it);
  if(isnan(trials) || trials < 1){
    throw "Invalid number of Trials";
  }
  else if(*it == '\0'){
    throw "Invalid mcint Expression";
  }
  // 3. Get the pairs of bounds
  std::vector<boundPair> bounds;
  try{getBoundPairs(it,bounds);
  }catch(const char * msg){
    throw msg;
  }
  // 4. Monte Carlo Integration
  double result;
  try{result = mcintegrate((*mapIt).second, bounds, trials);}
  catch(const char * msg){
    throw msg;
  }
  return result;
}

double parseFunction(std::string::iterator & it, std::map<std::string,Function*> &m){
  skipSpaces(it);
  std::vector<double> valVec;
  std::string func = getStringBeforeSpace(it);
  std::map<std::string,Function*>::iterator mapIt = m.find(func);
  if(mapIt == m.end()){
    std::cerr << "Not a valid function...\n";
    return NAN;
  }
  makeValVec(it,m,valVec);
  std::vector<VarPair> vals;
  try{
    //vals = (*mapIt).second->assignValues(valVec);
    (*mapIt).second->assignValues(valVec);
  }catch (const char * msg){
    std::cerr << msg << std::endl;
    return NAN;
  }
  //std::cout << "Done assigning values to function: " << (*mapIt).first << std::endl;
  //return (*mapIt).second->evaluate(vals);
  return (*mapIt).second->evaluate();
}

int maxOrMin(std::string::iterator & it){
  std::string type = getStringBeforeSpace(it);
  if(type.compare(0,3,"max") == 0){return ASCENT;}
  else if(type.compare(0,3,"min") == 0){return DESCENT;}
  else{return BOO;}
}

void parse(const std::string & strp, std::map<std::string,Function*> & m) {
  //Define Mode or Evaluate Mode
  std::string string = strp;
  std::string::iterator it = string.begin();
  if(*it == '\0'){return;}
  //std::cout<<"\nStarting line Parse...\n";
  std::cout<<"expression: "<<strp<<std::endl;
  //We need to strip any leading spaces
  stripSpaces(string,it);
  //std::cout << "after removing spaces: " << strp << std::endl;
  if((string.compare(0,6,"define")) == 0){
    //Define:
    // 1.split strings rhs & lhs
    //std::cout<< strp << std::endl;
    std::string idStr;
    try{idStr = getIdString(strp);}
    catch(const char * msg){
      std::cerr << msg << std::endl;
      return;
    }
    //std::cout<< "idString: "<<idStr << std::endl;
    std::string exprStr = getExprString(strp);
    //std::cout<< "exprString: "<<exprStr<< std::endl;
    // 2. get function pair first string is the name
    std::string::iterator idIt = idStr.begin();
    std::string fname;
    skipSpaces(idIt);
    if((idStr[0] = '(')){
      ++idIt;
      //Lets get the name
      fname = getStringBeforeSpace(idIt);
      ++idIt;
      if(containsNumber(fname)){return;}
      //std::cout << "Name of func: " <<fname<< std::endl;
    }
    if(m.find(fname) != m.end()){
      std::cerr << "Name already exists in map. Ignoring this function definition\n";
      return;
    }
    // 3. Make vector for the variables w/default value
    std::vector<VarPair> temp;
    std::string name;
    while(*idIt != ')'){
      name = getStringBeforeSpace(idIt);
      if(containsNumber(name)){return;}
      //std::cout << "Adding String: " <<name << std::endl;
      temp.push_back(std::make_pair(name,0));
      ++idIt;
    }
    /*std::cout << "Checking values in vector...\n";
      for(unsigned i = 0; i < temp.size(); i++){
         std::cout<<"Variable: "<< temp[i].first <<" value: "<<temp[i].second<<std::endl;
	 }*/
    // 4. Create a function class for the value
    Function * f = new Function(temp);
    // 5. BUILD THE FUNCTION (rhs)
    std::string::iterator exprIt = exprStr.begin();
    //std::cout<< "Begin Parsing exp: "<<exprStr << std::endl;
    Expression * expr = exprParse(exprIt, m, f);
    if(expr == NULL){
      std::cerr << "Invalid Expression\n";
      delete f;
      return;
    }
    // 6. Assign Expression Tree to function and add to Map (return)
    f->addExpression(expr);
    std::cout << "defined ("<< fname << f->printVars() <<")\n";
    //std::cout << f->toString() << std::endl;
    m.insert( FuncPair(fname, f) );
    return;
  }
  else if((string.compare(0,8,"evaluate")) == 0){
    //std::cout<< "Evaluate This" << std::endl;
    string.erase(0,string.find('('));
    std::string::iterator temp;
    std::string fname;
    double ans;
    //1. Figure out which function we are evaluating
    if(*it == '('){
      ++it;
      temp = it;
      fname = getStringBeforeSpace(temp);
      ans = parseFunction(it,m);
      if(isnan(ans)){
	std::cout<<"Function not evaluated\n";
	return;
      }
      std::cout << string << " = " << ans << std::endl;
    }
    else{
      std::cerr << "Invalid Evaluation String\n";
    }
  }
  else if((string.compare(0,6,"numint") == 0)){
    //std::cout << "Numerical Integration...\n";
    string.erase(0,6);
    skipSpaces(it);
    double value;
    try{value = numintParse(it,m);
    }catch(const char* msg){
      std::cerr << msg << std::endl;
      return;
    }
    std::cout << "numint result = " << value << std::endl;
  }
  else if((string.compare(0,5,"mcint") == 0)){
    //std::cout << "Monte Carlo Integration...\n";
    string.erase(0,6);
    skipSpaces(it);
    double value;
    try{value = mcintParse(it,m);
    }catch(const char * msg){
      std::cerr << msg << std::endl;
      return;
    }
    std::cout << "mc result: " << value << std::endl;
  }
  else if((string.compare(0,3,"max") == 0) || (string.compare(0,3,"min")==0)){
    int type = maxOrMin(it);
    std::string fname = getStringBeforeSpace(it);
    //std::cout << "function: " << fname << std::endl;
    std::map<std::string,Function*>::iterator mapIt = m.find(fname);
    if(mapIt == m.end()){
      std::cerr << "Function not in the map. Duh...\n";
      return;
    }
    double gamma = getDoubleVal(it);
    //std::cout << "gamma: " << gamma << std::endl;
    if(isnan(gamma) || gamma <= 0){
      std::cerr << "Invalid Gamma value\n";
      return;
    }
    else if(*it == '\0'){
      std::cerr << "Invalid min/max expression\n";
      return;
    }
    double convg = getDoubleVal(it);
    //std::cout << "convg: " << convg << std::endl;
    if(isnan(convg) || convg <= 0){
      std::cerr << "Invalid convergence value\n";
      return;
    }
    std::vector<double> strtpts;
    try{strtpts = getVector(it,(*mapIt).second);}
    catch(const char * msg){
      std::cerr << msg << std::endl;
      return;
    }
    if(type == ASCENT){
      double max = gradAscent(gamma,convg,strtpts,(*mapIt).second);
      std::cout << "Max value: " << max << std::endl;
    }
    else if(type == DESCENT){
      double min = gradDescent(gamma,convg,strtpts,(*mapIt).second);
      std::cout << "Min value: " << min << std::endl;
    }
    else{
      std::cerr << "Whats going on here???\nNot evaluating\n";
      return;
    }
  }
  else if(*it == '\0'){
    return;
  }
  else{
    std::cout<< "I don't know what to do here bro\n";
  }
}

#endif
