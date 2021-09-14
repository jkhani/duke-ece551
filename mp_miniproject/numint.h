#ifndef __NUMINT_H__
#define __NUMINT_H__
#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include "function.h"
#include "helper.h"
#include <ctime>
#define STEPSIZE 100

double numRectangles(boundPair & bounds, double step){
  return (bounds.second - bounds.first)/step;
}

double getTableSize(std::vector<boundPair> & bounds, double step){
  std::vector<boundPair>::iterator it = bounds.begin();
  double size = 1;
  while(it != bounds.end()){
    //size *= ((*it).second - (*it).first)/step;
    size *= numRectangles(*it,step);
    ++it;
  }
  return ceil(size);
}

double getAreaSize(std::vector<boundPair> & bounds){
  std::vector<boundPair>::iterator it = bounds.begin();
  double size = 1;
  while(it != bounds.end()){
    size *= (*it).second - (*it).first;
    ++it;
  }
  return ceil(size);
}

double sumVector(std::vector<double> & vec){
  double result = 0;
  std::vector<double>::iterator it = vec.begin();
  while(it != vec.end()){
    result += *it;
    ++it;
  }
  return result;
}

std::vector<double> numRecVec(std::vector<boundPair> & b, double step){
  std::vector<double> temp;
  double num = 1;
  for(unsigned i =0; i < b.size(); i++){
    num *= numRectangles(b[i],step);
    // std::cout << "num rectangles: " <<num <<std::endl;
    temp.push_back(num);
  }
  return temp;
}

std::vector<double> baseVector(std::vector<boundPair> & b, double step){
  std::vector<double> temp;
  for(unsigned i = 0; i < b.size(); i++){
    temp.push_back((b[i].first + (b[i].first + step))/2);
  }
  return temp;
}

std::vector<double> tempVector(std::vector<double> & base, double step){
  std::vector<double> temp;
  for(unsigned i = 0; i <base.size(); i++){
    temp.push_back(base[i]-step);
  }
  return temp;
}

double integrate(Function *f, std::vector<boundPair> & bounds, double step){
  double size = getTableSize(bounds,step);
  //std::cout << "size is: " << size << " x " <<bounds.size() << std::endl;
  if(isnan(size)||(size<=0)){
    throw "Invalid size of matrix to evaluate";
  }
  std::vector<double> numRecs = numRecVec(bounds,step);
  std::vector<double> base = baseVector(bounds,step);
  std::vector<double> temp = tempVector(base,step);
  //Our goal is to set up the combinations of the points to follow the form like:
  /* 000
         001
         010
         011 etc..
         Previously store all the values in a matrix (vector of vectors) but for efficiency have tried to
         strip this away since we dont need to reuse these points
  */
  double result = 0;
  for(unsigned p = 0; p < (unsigned)size; ++p){
    for(unsigned m = 0; m < bounds.size(); ++m){
      if((p % (unsigned)(size/numRecs[m])) == 0){
	//Now we will increment our value to put in our vector
	temp[m] += step;
	if(temp[m] > bounds[m].second){
	  temp[m] = base[m];
	}
      }
    }
    //printVector(temp);
    //std::cout << std::endl;
    f->assignValues(temp);
    result += f->evaluate();
  }
  return pow(step,bounds.size())*result;
}

double MAX(std::vector<double> & vec){
  std::vector<double>::iterator it = vec.begin();
  double max = *it;
  while(it != vec.end()){
    if(*it > max){
      max = *it;
    }
    ++it;
  }
  return max;
}

double MIN(std::vector<double> & vec){
  std::vector<double>::iterator it = vec.begin();
  double min = *it;
  while(it != vec.end()){
    if(*it < min){
      min = *it;
    }
    ++it;
  }
  return min;
}

double genRandom(double high, double low){
  /*Generate a random float form [low to high] */
  return low + (double)(rand()) / (RAND_MAX/(high - low));
}

void printCoordinate(std::vector<double> & cord){
  std::cout << "at point: ";
  for(unsigned i = 0; i < cord.size(); ++i){
    std::cout << cord[i] << " ";
  }
  std::cout <<std::endl;
}

std::vector<double> randomPoints(std::vector<boundPair> & bounds){
  std::vector<double> temp;
  for(unsigned i = 0; i < bounds.size(); ++i){
    temp.push_back(genRandom(bounds[i].second, bounds[i].first));
    //std::cout << "random number is "<< temp[i] << std::endl;
  }
  return temp;
}

double findMinStep(std::vector<boundPair> & bounds){
  double min = bounds[0].second - bounds[0].first;
  double temp;
  for(unsigned i = 1; i < bounds.size(); i++){
    temp = bounds[i].second - bounds[i].first;
    if(temp < min){
      min = temp;
    }
  }
  return temp/STEPSIZE;
}

double mcintegrate(Function *f, std::vector<boundPair> & bounds, double trials){
  // 1. We're going to get out max and min probablistically. When we see the evaluate is greater or
  // Less than the current max or min we will update apporpriately to continue getting random values.
  double max = 0;
  double min = 0;
  double result = 0; //store result of eval at random pt
  double mc = 0; // Count for the monte carlo
  double r = 0; // The random number to compare to result
  srand(time(NULL));
  std::vector<double> randPts (bounds.size(),0);
  for(unsigned i = 0; i < trials; ++i){
    // 2. Make vector of random points
    randPts = randomPoints(bounds);
    f->assignValues(randPts);
    result = f->evaluate();
    if(result > max){max = result;}
    if(result < min){min = result;}
    /*std::cout << "================\n";
      std::cout << "Trial Number: "<<i<<std::endl;
      printCoordinate(randPts);*/
    // 3. create random # to compare with f
    r = genRandom(max,min);
    /*std::cout << "random value: "<< r << std::endl;
      std::cout << "function value: " << result << std::endl;*/
    // 4. Evaluate @ all the random points and compare values with vector of random #'s
    if(result >= 0 && (r <= result && r >= 0)){
      //std::cout << "Increment by 1..\n";
      mc += 1;
    }
    else if(result < 0 && (r > result && r<= 0)){
      //std::cout << "Decrement by 1..\n";
      mc -= 1;
    }
    else{
      //std::cout << "Do nothing...\n";
      //Do Nothing
    }
  }
  //std::cout << "(" << mc << "/" << trials << ") * " << (getAreaSize(bounds)*(max-min)) << std::endl;
  return (mc/trials)*(getAreaSize(bounds)*(max-min));
}

#endif
