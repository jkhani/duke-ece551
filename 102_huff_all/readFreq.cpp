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
  uint64_t *freqs = new uint64_t[257] ();
  
  std::ifstream ifs (fname);
  unsigned char currChar;

  if(ifs.is_open() && ifs.good()){
    while(!ifs.eof()){
      currChar = ifs.get();
      if (currChar == 255){
	continue;
      }
      freqs[currChar] += 1;
    }
  }

  freqs[256] = 1;

  ifs.close();

  return freqs;
  
}
