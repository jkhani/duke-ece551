#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "readFreq.h"

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  static uint64_t freqs[257];
  
  std::ifstream ifs (fname);
  char currChar;

  if(ifs.is_open() && ifs.good()){
    while(!ifs.eof()){
      currChar = ifs.get();
      freqs[(int) currChar] += 1;
    }
  }

  ifs.close();

  return freqs;
  
}
