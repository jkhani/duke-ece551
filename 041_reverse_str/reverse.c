#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// takes a string and reverses it
void reverse(char * str) {
  // create variable to store length of string
  int len = 0;
  // determine the size of the string
  while(*str != '\0'){
    len++;
    str++;
  }
  // pointer to original string will now be pointing to NULL value

  if (len > 0){
  // create copy of string
  char str_cp[len];

  // loop through string starting from the end, b for backward indexing
  for(int b = 0; b< len; b++){
    str--; // start from the first value before the NULL
    str_cp[b] = *str; // set the ith value of the copy to the value str is pointing to
  }
  // string copy will be the reverse of original string

  // loop through copy and change original string value to that of copy
  for(int f = 0; f <len; f++){
    *str = str_cp[f];
    str++;
  }
  }
  else{
    str--;
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
