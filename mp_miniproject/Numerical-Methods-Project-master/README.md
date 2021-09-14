/**********************************************************************************************

Jonathan Buie (jab165) Final Project: Numerical Integration
Due: 12/7/2015 11:59:59 pm


**********************************************************************************************/

Description of Code:
   Files included: MAKEFILE numeric.cpp helper.h parse.h function.h numint.h gradient.h

      numeric.cpp -> MAIN: reads in files and pass line by line be parsed.

      helper.h -> header with functions that made parsing and obtaining strings and numbers easier
                  across all header files

      parse.h -> Hold subroutines for parsing. Differnt subroutines for parsing of entire lines,
                 expressions, integration lines, etc. Called by numeric.cpp
                 We create, evaluate, integrate, etc. The function trees here and print to std::cout

      function.h -> Holds the Expression and function classes. These are used to define how expressions,
                    functions and callExpression classes properly evaluate to return answers.
                    
      numint.h -> Numerical Integration.  The code to successfully do numerical and monte-carlo
                  integration are here.  Called by parse.h

      gradient.h -> The code for gradient ascent and descent are here.  As well as the functions that
                    make this possible, such as derivative, gradients, and vector arithmetic functions.
      
      Makefile -> To compile code to an executable called "numeric"
            TO RUN:
                  ./numeric [filenames]

Functionality:
   For this project I was able to accomplish a working version of Steps 1 - 4. The hardest hurdle to get
   across was Step 1, becuase without the ability to properly define and evaluate function (especially 
   nested functions within functions!) the other steps were'nt possible.

   Step 1, When parsing lines for functions one major corner case that was checked was if you have function
      declaration in which the variables are operators.  (ie. define (f *) = (+ * 2)).  This was tested 
      and handled.  Also when parsing of functions the fact that the lines are space delimited was critical
      and in cases which spaces don't occur after the operator the code returns an invalid expression and 
      parses the rest of the file.
   Step 2, For the midpoint-rectangle approx method for integration the results seem accurate.  Verified by
      that for decreasing rectangle widths the area becomes more accurate.  Initial design included a matrix
      with all the combinations of points to evaluate, but this proved to be inefficient. Final Design has
      only one vector with the point to be evaluated and an algorithm to update it appropriatly.
   Step 3, MonteCarlo Integration is implemented by finding the random values within the area of integration
      of the function, f, probabilistically.  As we evaluate the random points selected the max and min are
      also adjusted to select random output values within the bounds.
   Step 4, For the maximum and minimum values, I was able to implement two seperate functions that can do 
      gradient Ascent, and gradient Descent. Some assistance was from AoP when it came to writing code for
      derivatives but similar to the methodolgy for steps 2 & 3, many of the compuations were with vectors
      of doubles to account for the dimensions of the functions.
      During testing the Descent fuction seemed to perform better, but for functions where the answer should
      should be inf & -inf I return a very large or very small (ie e+19 or e-19) value.
      Also when dealing with multidimenstional cases my code seemed to hang and I wasn't sure if this was a 
      result of improperly setting up a max/min expression for very large functions.
      Ex.
               define (g x y) = (+ (* 2 x) y)
               min g .1 .05 1 2
               max g .1 .05 1 2

Testing Framework:
   Suggested test string:
      ./numeric define.txt integrate.txt mcint.txt grad.txt breakMyCode.txt
      
    Each of the these files has cases to tests the respective steps 1-4.  The additional breakMyCode.txt
    file was just a bunch of wacky stuff that was thought up to see if the code could be broke. Please 
    contribute I'd love to see what you could think of ;) . Plus it would be a great way to see where I 
    can improve.
    Note: **Each file has its own map of functions so f can be defined once in file1 and once in file2,
    but never multiple times in the same file.

Additional Notes:
   In all, this has been a very challenging, yet rewarding project. My code has gone through several interations as 
   I learned new things as this process went on.  I can even see the differences from code that I wrote when first 
   starting compared to near the end.  
   Some improvements that I've noticed could be the use of the gradient descent and ascent in my Step 3 code as a way
   to find the max and min to help with the monte carlo method.  In addition, the use of maps was useful when 
   considering that a large number of functions could be defined in one file.  With more domain knowledge on some of
   the mathematic principals behind some of these concepts I feel that would help me improve results especially in
   the case of Step 4, but in all I feel that I've improved my design, data structure and algorithm skills greatly.
