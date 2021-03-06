#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <map>
#include <queue>
#include <assert.h>
#include <functional>
#include <stdlib.h>
#include "readFreq.h"
#include "node.h"


void writeHeader(BitFileWriter * bfw, const std::map<unsigned,BitString> &theMap) {
  for (int i =0 ; i < 257; i++) {
    std::map<unsigned,BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char* inFile,
			   const char *outFile,
			   const std::map<unsigned,BitString> &theMap ){

  BitFileWriter bfw(outFile);
  writeHeader(&bfw,theMap);

  FILE * fr = fopen(inFile,"r");
  int c;

  std::map<unsigned, BitString>::const_iterator it;

  while((c = fgetc(fr)) != EOF){
    it = theMap.find((unsigned)c);
    if (it == theMap.end()){
      perror("Some errors happened before!");
    }

    else{
      bfw.writeBitString(it->second);
    }
  }

  it = theMap.find(256);

  bfw.writeBitString(it->second);
  fclose(fr);
}


int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr,"Usage: compress input output\n");
    return EXIT_FAILURE;
  }

  uint64_t * input = readFrequencies(argv[1]);

  std::map<unsigned,BitString> theMap;
  BitString b;

  Node * node = buildTree(input);

  node->buildMap(b, theMap);

  writeCompressedOutput(argv[1], argv[2], theMap);

  delete[] input;
  delete node;

  return EXIT_SUCCESS;

}
