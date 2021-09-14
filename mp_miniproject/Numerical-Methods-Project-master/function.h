#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <cmath>
typedef std::pair<std::string,double> VarPair;
typedef std::pair<double,double> boundPair;

class Expression{
 protected:
   double value;
 public:
   Expression(): value(0) {}
   Expression(double val): value(val) {}
   virtual std::string toString() const = 0; //abstract method  
   virtual double evaluate() = 0; //abstract method
   virtual double evaluate(std::vector<VarPair> & values) const = 0; //abstract method
   virtual ~Expression() {}
};

class Function: public Expression{
private:
   std::vector<VarPair> vars;
   Expression * expr;
public:
   Function(): expr(NULL){}
   Function(std::vector<VarPair> & v): vars(v), expr(NULL){}
   Function(std::vector<VarPair> & v, Expression * e): vars(v), expr(e){}
   std::string printVars() const{
      std::stringstream ss;
      if(!vars.empty()){
         std::vector<VarPair>::const_iterator it = vars.begin();
         while(it != vars.end()){
            ss << " " << (*it).first;
            ++it;
         }
      }
      return ss.str();
   }
   virtual std::string toString() const{
   //Redundant Consider deleting Print Vars
      std::stringstream ss;
      if(expr != NULL){
         ss << expr->toString();
      }
      return ss.str();
   }
   unsigned VarSize() const{return vars.size();}
   virtual double evaluate(std::vector<VarPair> & values) const {
      assert(values.size() == vars.size());
      return expr->evaluate(values);
   }
   virtual double evaluate(){
      //Assign Variable Values
      return expr->evaluate(vars);
   }
   void addExpression(Expression * e){
      expr = e;
   }
   Expression * getExpression(){return expr;}

   std::vector<VarPair> getVector() const{return vars;}

   void assignValues(std::vector<double> vec){
      if(vec.size() != vars.size()){
      //if(vec.size() < vars.size()){
         //throw "Vectors must be the same size";
         /*with this conditional if you pass in too few args
         then you wont be able to evaluate but if you have enough
         of extra values doesnt stop the evaluation */
         throw "Vector not a valid size";
      }
      for(unsigned i = 0; i < vars.size(); i++){
         vars[i].second = vec[i];
      }
      //return vars;
   }
   bool isVar(const std::string s){
      std::vector<VarPair>::const_iterator it =vars.begin();
      while(it != vars.end()){
         if(s == (*it).first){return true;}
         ++it;
      }
      return false;
   }
   virtual ~Function(){
      delete expr;
   }
};

typedef std::pair<std::string,Function*> FuncPair;


class CallExpression: public Expression{
 private:
   std::string name;
   Function * f;
   std::vector<Expression *> args; //This hold the arguments passed into a function to evaluate
 public:
   CallExpression(): name(NULL),f(NULL) {}
   CallExpression(std::string & s, Function * fun, std::vector<Expression *> & e): name(s), f(fun), args(e){}
   virtual std::string toString() const {
      std::stringstream ss;
      ss << name;
      if(!args.empty()){
         ss << "(";
         for(unsigned i = 0; i < args.size(); i++){
            ss << args[i]->toString();
            if(i < args.size() - 1){
               ss << ", ";
            }
         }
         ss << ")";
      }
      return ss.str();
   }
   virtual double evaluate(std::vector<VarPair> & values) const{
      //WRITE THIS***
      // 1. Evaluate the Expressions in args w/ values
      std::vector<Expression*>::const_iterator it = args.begin();
      double ans;
      std::vector<double> temp;
      while(it != args.end()){
         ans = (*it)->evaluate(values);
         temp.push_back(ans);
         ++it;
      }
      // 2. Use vector of doubles to pass to Function f
      f->assignValues(temp);
      // 3. Return result
      return f->evaluate();
   }
   virtual double evaluate(){return 0;}
   virtual ~CallExpression(){
      std::vector<Expression*>::iterator it = args.begin();
      while(it != args.end()){
         delete *it;
         ++it;
      }
   }
};

class NumExpression: public Expression{
 public:
   NumExpression(double val): Expression(val){}
   virtual std::string toString() const {
      //Implement this
      std::stringstream ss;
      ss << value;
      return ss.str();
   }
   virtual double evaluate(std::vector<VarPair> & values) const{return value;}
   virtual double evaluate() {
      return value;
   }
   virtual ~NumExpression() {}
};

class VarExpression: public Expression{
 private:
   std::string name;
 public:
   VarExpression(std::string n): Expression(0), name(n) {}
   virtual std::string toString() const {
      std::stringstream ss;
      ss << name;
      return ss.str();
   }
   virtual double evaluate(std::vector<VarPair> & values) const{
      std::vector<VarPair>::iterator it = values.begin();
      while(it != values.end()){
         if((*it).first == name){
            return (*it).second;      
         }
         ++it;
      }
      std::cerr<< "Didnt find name in value vector\n";
      return value;
   }
   virtual double evaluate() {
      return value;
   }
   virtual ~VarExpression() {} //Make sure we dont have to kill the string, but it does have a defualt destructor
};

class PlusExpression: public Expression{
 private:
   Expression * left;
   Expression * right; 
 public:
   virtual std::string toString() const{
      std::stringstream ss;
      ss << "(" << left->toString() << " + " <<right->toString() << ")";
      return ss.str();
   }
   PlusExpression(Expression *lhs, Expression *rhs): left(lhs), right(rhs){}
   virtual ~PlusExpression(){
      delete left;
      delete right;
   }
   virtual double evaluate() {
      return left->evaluate() + right->evaluate();
   }
   virtual double evaluate(std::vector<VarPair> & values) const {
      return left->evaluate(values) + right->evaluate(values);
   }
};

class MinusExpression: public Expression{
 private:
   Expression * left;
   Expression * right; 
 public:
   virtual std::string toString() const{
      std::stringstream ss;
      ss << "(" << left->toString() << " - " <<right->toString() << ")";
      return ss.str();
   }
   MinusExpression(Expression *lhs, Expression *rhs): left(lhs), right(rhs){}
   virtual double evaluate() {
      return left->evaluate() - right->evaluate();
   }
   virtual double evaluate(std::vector<VarPair> & values)const {
      return left->evaluate(values) - right->evaluate(values);
   }
   virtual ~MinusExpression(){
      delete left;
      delete right;
   }
};

class TimesExpression: public Expression{
 private:
   Expression * left;
   Expression * right; 
 public:
   virtual std::string toString() const{
      std::stringstream ss;
      ss << "(" << left->toString() << " * " <<right->toString() << ")";
      return ss.str();
   }
   TimesExpression(Expression *lhs, Expression *rhs): left(lhs), right(rhs){}
   virtual double evaluate() {
      return left->evaluate() * right->evaluate();
   }
   virtual double evaluate(std::vector<VarPair> & values) const{
      return left->evaluate(values) * right->evaluate(values);
   }
   virtual ~TimesExpression(){
      delete left;
      delete right;
   }
};

class DivExpression: public Expression{
 private:
   Expression * left;
   Expression * right; 
 public:
   virtual std::string toString() const{
      std::stringstream ss;
      ss << "(" << left->toString() << " / " <<right->toString() << ")";
      return ss.str();
   }
   DivExpression(Expression *lhs, Expression *rhs): left(lhs), right(rhs){}
   virtual double evaluate() {
      return left->evaluate() / right->evaluate();
   }
   virtual double evaluate(std::vector<VarPair> & values) const{
      return left->evaluate(values) / right->evaluate(values);
   }
   virtual ~DivExpression(){
      delete left;
      delete right;
   }
};

class PowExpression: public Expression{
 private:
   Expression * left;
   Expression * right; 
 public:
   virtual std::string toString() const{
      std::stringstream ss;
      ss << "(" << left->toString() << " ^ " <<right->toString() << ")";
      return ss.str();
   }
   PowExpression(Expression *lhs, Expression *rhs): left(lhs), right(rhs){}
   virtual double evaluate() {
      return pow(left->evaluate(), right->evaluate());
   }
   virtual double evaluate(std::vector<VarPair> & values) const{
      return pow(left->evaluate(values), right->evaluate(values));
   }
   virtual ~PowExpression(){
      delete left;
      delete right;
   }
};

class SqrtExpression: public Expression{
 private:
   Expression * left;
   Expression * right; // Is this necessary? Should I only have one expression side
 public:
   virtual std::string toString() const{
      std::stringstream ss;
      ss << "sqrt (" << left->toString() <<")";
      return ss.str();
   }
   SqrtExpression(Expression *lhs, Expression *rhs): left(lhs), right(rhs){}
   virtual double evaluate() {
      return sqrt(left->evaluate()); 
   }
   virtual double evaluate(std::vector<VarPair> & values)const{
      return sqrt(left->evaluate(values));
   }
   virtual ~SqrtExpression(){
      delete left;
   }
};

#endif
