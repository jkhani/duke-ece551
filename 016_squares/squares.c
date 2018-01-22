int max (int num1, int num2) {
  //check if num1 is greater than num2
  if (num1 > num2) {
    //if so, your answer is num1
    return num1;
  }
  else {
    //otherwise, your answer is num2
    return num2;
  }
}

void squares(int size1, int x_offset, int y_offset, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1,(x_offset + size2));  

  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1,(y_offset + size2));
  
  //count from 0 to h. Call the number you count with y
  for (int y = 0; y < h; y++) {

    //count from 0 to w. Call the number you count with x
    for (int x = 0; x < w; x++) {

      //check if  EITHER
      if (
	  (
      //    ((x is between x_offset  and x_offset +size2) AND 
	   ((x <= x_offset) && (x < (x_offset + size2))) &&
	   
      //     y is equal to either y_offset OR y_offset + size2 - 1 )
	   ((y == y_offset) || (y == (y_offset + size2 - 1)))
	   )
      // OR
	  ||
      	  (
      //    ((y is between y_offset and y_offset + size2) AND
	   ((y <= y_offset) && (y < (y_offset + size2))) &&
      //     x is equal to either x_offset OR x_offset + size2 -1)
	   ((x == x_offset) || (x == (x_offset + size2 - 1)))
	   )
	  )
	{
      // if so, print a *
	    printf("*");
	}

      //if not,
      else {	
      // check if EITHER
	if (
      //    x is less than size1 AND (y is either 0 or size1-1)
	    (x < size1 && (y == 0 || y == (size1 - 1)))
      // OR
	    ||	    
      //    y is less than size1 AND (x is either 0 or size1-1)
	    (y < size1 && (x == 0 || x == (size1 - 1)))
	    )
	  {	    
      //if so, print a #
	    printf("#");
	  }
      //else print a space
	else {
	  printf(" ");
	}
    //when you finish counting x from 0 to w, 
    //print a newline
      }
    }
    printf("\n");
  }

  return 0
}
