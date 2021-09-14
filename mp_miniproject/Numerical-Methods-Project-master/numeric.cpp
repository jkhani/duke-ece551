#include <iostream>
#include "function.h"
#include "parse.h"
#include <ctype.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstdio>

void destructMap(std::map<std::string,Function*> & m){
   std::map<std::string,Function*>::iterator it = m.begin();
   while(it != m.end()){
      //std::cout << "deleting function " << (*it).first << std::endl;
      delete (*it).second;
      ++it;
   }
}

int main(int argc, char **argv) {
   //Error Check System for number of inputs
   if(argc <= 1){
      std::cout << "Usage: ./numeric filename[s]\n";
      return EXIT_FAILURE;
   }
   else{
      for(int i =1; i < argc; ++i){
         std::ifstream f;
         f.open(argv[i]);
         std::cout << "======================"<<std::endl;
         std::cout << "\nReading file "<<argv[i] << "..." <<std::endl;
         std::cout << "======================"<<std::endl;
         std::string line;
         if(!f.good()){std::cerr << "file doesn't exists\n";}
         //Create Map to hold all functions
         std::map<std::string,Function*> funcMap;
         //Parse by Line (args string&, map&)
         while(std::getline (f, line)){ 
            std::string temp = line;
            try{parse(temp,funcMap);}
            catch(...){
            }
            std::cout<< std::endl;
         }
         f.close();
         destructMap(funcMap);
      }
   }
   return EXIT_SUCCESS;
}
