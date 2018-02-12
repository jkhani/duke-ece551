#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}


//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);

}

// this function reads and stores the lines from file into array of strings
void readData(FILE * f){
  char **lines = NULL;
  char *curr = NULL;
  size_t linecap;
  size_t i = 0;
  while (getline(&curr, &linecap, f) >= 0){
    lines = realloc(lines, (i+1) *sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  
  sortData(lines,i);
  for (size_t j = 0; j < i; j++){
    printf("%s", lines[j]);
  }

  free(lines);
}

int main(int argc, char ** argv) {
  
  //WRITE YOUR CODE HERE!
  // If no input file provided, use stdin
  if (argc ==1) {
    printf("No input file provided.\nType strings to be sorted.\nPress CTRL+d to indicate EOF.\n");
    readData(stdin);
  }
  else {
    int i;
    for(i = 1; i < argc; i++){
      FILE * f = fopen(argv[i],"r");
      if (f == NULL) {
	fprintf(stderr, "Could not open file");
	return EXIT_FAILURE;
      }

      readData(f);

      if (fclose(f) != 0) {
	fprintf(stderr,"Failed to close the input file!");
	return EXIT_FAILURE;
      }
    }
  }
  
  return EXIT_SUCCESS;
}
