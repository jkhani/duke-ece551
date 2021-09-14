#ifndef __GRADIENT_H__
#define __GRADIENT_H__
#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include "function.h"
#include "helper.h"

std::vector<double> getVector(std::string::iterator & it, Function * f){
   std::vector<double> temp;
   while(*it != '\0'){
      double num = getDoubleVal(it);
      if(isnan(num)){throw "Invalid number for starting point...";}
      temp.push_back(num);
      //++it;
   }
   if(f->VarSize() != temp.size()){throw "Invalid number of starting points...";}
   return temp;
}

std::vector<double> multVector(std::vector<double> & v, double by){
   std::vector<double> temp (v.size(),0);
   for(unsigned i = 0; i < v.size(); ++i){
      temp[i] = v[i]*by;
   }
   return temp;
}

std::vector<double> addVector(std::vector<double> & a, std::vector<double> & b){
   assert(a.size() == b.size());
   std::vector<double> temp(a.size(),0);
   for(unsigned i = 0; i < a.size(); ++i){
      temp[i] = a[i]+b[i];
   }
   return temp;
}

std::vector<double> subVector(std::vector<double> & a, std::vector<double> & b){
   assert(a.size() == b.size());
   std::vector<double> temp(a.size(),0);
   for(unsigned i = 0; i < a.size(); ++i){
      temp[i] = a[i]-b[i];
   }
   return temp;
}

double derivative(Function *f, std::vector<double> & val, unsigned dim){
   double h = 0.0000001;
   std::vector<double> toEval (val);
   toEval[dim] += h;
   f->assignValues(toEval);
   double fxh = f->evaluate();
   f->assignValues(val);
   double fx = f->evaluate();
   return (fxh-fx) / h;
}

std::vector<double> gradient(Function * f, std::vector<double> & val){
   std::vector<double> temp;
   for(unsigned dim = 0; dim < val.size(); dim++){
      temp.push_back(derivative(f,val,dim));
   }
   return temp;
}

double dist(std::vector<double> &v){
   std::vector<double>::iterator it = v.begin();
   double d = 0;
   while(it != v.end()){
      d += pow(*it,2);
      ++it;
   }
   return sqrt(d);
}

double gradAscent(double gamma, double conv, std::vector<double> & pcurr, Function *f){
   std::vector<double> pnew (pcurr.size(),0);
   std::vector<double> grad = gradient(f,pcurr);
   std::vector<double> step = multVector(grad,gamma);
   while( dist(step) > conv){
      // pnew = pcurr + gamma*gradient(f,pcurr)
      pnew = addVector(pcurr,step);
      pcurr = pnew; 
      //step= gamma * gradient(f,s);
      grad = gradient(f,pcurr);
      step = multVector(grad,gamma);
   }
   f->assignValues(pnew);
   return f->evaluate();
}


double gradDescent(double gamma, double conv, std::vector<double> & pcurr, Function *f){
   std::vector<double> pnew (pcurr.size(),0);
   std::vector<double> grad = gradient(f,pcurr);
   std::vector<double> step = multVector(grad,gamma);
   while( dist(step) > conv){
      // pnew = pcurr + gamma*gradient(f,pcurr)
      pnew = subVector(pcurr,step);
      pcurr = pnew; 
      //step= gamma * gradient(f,s);
      grad = gradient(f,pcurr);
      step = multVector(grad,gamma);
   }
   f->assignValues(pnew);
   return f->evaluate();
}

#endif
