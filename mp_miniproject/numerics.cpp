#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include "expr.h"
#include "function.h"
#include "commands.h"
#include "common.h"

/*
main() runs the numerics program; it opens a file given as command
argument, reads each line of the input file one at a time, parses
the command, then passes the command and each line input to another
function to carry out the commands.
*/
int main(int argc, char** argv){

  if (argc == 1) {
    // consider just using stdin if no file is given
    std::cout << "Expected usage: ./numerics [filename].txt\n";
    return EXIT_FAILURE;
  }
  else {
    std::ifstream ifs(argv[1]);

    if(ifs.is_open() && ifs.good()) {
      std::string inputStr;

      // map object to hold all defined functions <key = functionName, value = functionObject>
      std::map<std::string, Function *> fMap;

      // parse one line at a time
      while(std::getline(ifs,inputStr) && !ifs.eof()){
	std::stringstream ss(inputStr);
	std::string command;
	// parse 1st word to get command
	ss >> command;

	// parse remaining line following the command
	std::string lineToParse(inputStr,inputStr.find(command) + command.size(), std::string::npos);
	// standardize line by removing extra spaces between ids
	lineToParse = removeSpaces(lineToParse);
	
	try{evalCommand(command, lineToParse, fMap);}
	catch(...){}

      }

      printFMap(fMap);
      deleteFMap(&fMap);
      fMap.clear();
    }
    else {
      std::cerr << "Error opening file\n";
      return EXIT_FAILURE;
    }

    ifs.close();
  }

  return EXIT_SUCCESS;
}
