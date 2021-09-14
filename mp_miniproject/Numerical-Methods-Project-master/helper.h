#ifndef __HELPER_H__
#define __HELPER_H__
#include <cstdio>
#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <map>
#include <cerrno>
#include <string>

void stripSpaces(std::string & strp, std::string::iterator & it){
   while(*it == ' '){
      strp.erase(it);
   }
}

void skipSpaces(std::string::iterator & it){
   //Eliminates Leading Whitespaces
   while(*it == ' '){
      ++it;
   }
}
void skipSpaces(std::string::const_iterator & it){
   //Eliminates Leading Whitespaces
   while(*it == ' '){
      ++it;
   }
}


std::string getStringBeforeSpace(std::string::const_iterator & it){
   skipSpaces(it);
   std::string temp;
   while(*it != ' '){
      if( it[1] == '(' || it[1] == ')' || it[1] == '\0'){
         return temp + *it;   
      }
      temp = temp + *it;
      ++it;
   }
   return temp;
}

std::string getStringBeforeSpace(std::string::iterator & it){
   skipSpaces(it);
   std::string temp;
   while(*it != ' '){
      //if( it[1] == '(' || it[1] == ')'){
      if( it[1] == '(' || it[1] == ')' || it[1] == '\0'){
         return temp + *it;   
      }
      temp = temp + *it;
      ++it;
   }
   return temp;
}
double getDoubleVal(std::string::iterator & it) {
   std::string val;
   val = getStringBeforeSpace(it);
   char * end;
   //double num = atof(val.c_str());
   double num = strtod(val.c_str(),&end); 
   //std::cout << "val string: " << val << std::endl;
   if(*end == ' ' || *end == '\0'){
      ++it;
      return num;
   }
   else{
      //std::cerr << "Invalid Number entered.\n";
      return NAN;
   }
}

void printVector(std::vector<double> & v){
   for(unsigned i = 0; i < v.size(); i++){
      std::cout << v[i] << " ";
   }
}
#endif
