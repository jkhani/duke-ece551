#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char ** argv) {
    std::string str;
    std::vector<std::string> str_vec;

  // If no input file provided, use standard input
  if (argc ==1) {
    if(std::cin.good()){
      while(std::getline(std::cin,str) && !std::cin.eof()){
	str_vec.push_back(str);
      }
      
      std::sort(str_vec.begin(), str_vec.end());

      for (std::vector<std::string>::const_iterator i = str_vec.begin(); i != str_vec.end(); ++i){
	std::cout << *i << "\n";
      }
    }
    else {
      std::cerr << "Detected error\n";
	return EXIT_FAILURE;
    }
  }
  else {
    for( int i=1; i<argc; ++i){
      std::ifstream ifs (argv[i]);

      if (ifs.is_open() && ifs.good()){
	while(std::getline(ifs,str) && !ifs.eof()){
	  str_vec.push_back(str);
	}
      }
      else {
	std::cout << "Error opening file\n";
	return EXIT_FAILURE;
      }

      std::sort(str_vec.begin(),str_vec.end());
      for (std::vector<std::string>::const_iterator i = str_vec.begin(); i != str_vec.end(); ++i){
	std::cout << *i << "\n";
      }

      str_vec.clear();
      ifs.close();

    }
  }     
  
  return EXIT_SUCCESS;
}
