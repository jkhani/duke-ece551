#ifndef __INTEGRATE_H__
#define __INTEGRATE_H__
#include <cstdlib>
#include <random>
#include <ctime>
#include <cmath>
#include "common.h"
#include "expr.h"
#include "function.h"
#include "parseExpr.h"

/*
numIterations determines the total number of rectangular prisms will be summed over.
*/
size_t numIterations(double &stepSize, std::vector<double> &lowBounds, std::vector<double> &highBounds){
  size_t iters = 1;
  for(size_t i = 0; i < lowBounds.size(); ++i){
    iters *= ((highBounds[i] - lowBounds[i])/stepSize);
  }
  iters = ceil(iters);

  return iters;
}

/*
itersPerDimension returns a vector where each value is the number of times each dimension will
be iterated over.
*/
std::vector<size_t> itersPerDimension(double &stepSize, std::vector<double> &lowBounds, std::vector<double> &highBounds){
  std::vector<size_t> rects;
  size_t numRects = 1;
  for(size_t i = 0; i < lowBounds.size(); ++i){
    numRects *= ((highBounds[i] - lowBounds[i])/stepSize);
    rects.push_back(numRects);
  }

  return rects;
}

/*
initialBaseVec returns a vector where each value is midpoint for the first rectangle
in each dimension.
*/
std::vector<double> initialBaseVec(double &stepSize, std::vector<double> &lowBounds){
  std::vector<double> base;
  for(size_t i = 0; i < lowBounds.size(); ++i){
    double baseMidpoint = (lowBounds[i] + (lowBounds[i] + stepSize))/2;

    base.push_back(baseMidpoint);
  }

  return base;
}

/*
numIntegrate returns the computed integral for the given function using the mid-point
rectangle method.
*/
double numIntegrate(Function * f, double &stepSize, std::vector<double> &lowBounds, std::vector<double> &highBounds){
  double result = 0;
  std::vector<std::string> pv = f->getPV();

  size_t numIters = numIterations(stepSize, lowBounds, highBounds);
  if(numIters < 1){
    std::cerr << "Numint requires at least 1 step to get an approximation of the integral!\n";
    return result;
  }

  std::vector<size_t> itersPerDim = itersPerDimension(stepSize, lowBounds, highBounds);
  // intialize each coordinate to be at the midpoint of the first rectangle in respective dimension
  std::vector<double> baseVec = initialBaseVec(stepSize, lowBounds);
  // create vector to store inputs to the function, initialize at first midpoint
  std::vector<double> inputVec = baseVec;

  
  for(size_t i = 0; i < numIters; ++i){
    // iterate over each dimension
    for(size_t j = 0; j < lowBounds.size(); ++j){
      // whenver this  returns true, increment the appropriate dimension by step size
      if((i % (numIters/itersPerDim[j])) == 0){
	inputVec[j] += stepSize;
	if(inputVec[j] > highBounds[j]){
	  // reset once argument once the dimension reaches the upper range boundary
	  inputVec[j] = baseVec[j];
	}
      }
    }

    // must be multiplied by the stepsize raised to the power of the dimension of the volume
    result += (f->evaluate(pv,inputVec)*pow(stepSize,lowBounds.size()));
  }
	
  return result;
}

/*
randVector uses the random number generator engine provided by C++11 to generate a random point for each
dimension given their respective bounds.
*/
std::vector<double> randVector(std::vector<double> &lowBounds, std::vector<double> &highBounds){
  std::vector<double> randPoints;
  for(size_t i = 0; i < lowBounds.size(); ++i){
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(lowBounds[i],highBounds[i]);
    double point = distribution(generator);

    randPoints.push_back(point);
  }

  return randPoints;
}

/*
getVolume
*/
double getTargetArea(std::vector<double> &lowBounds, std::vector<double> &highBounds){
  double volume = 1;
  for(size_t i = 0; i < lowBounds.size(); ++i){
    volume *= (highBounds[i] - lowBounds[i]);
  }

  return volume;
}


/*
mcIntegrate returns the computed integral using the Monte Carlo integration method
*/
double mcIntegrate(Function * f, double &numTrials, std::vector<double> &lowBounds, std::vector<double> &highBounds){
  double resultSum = 0;
  std::vector<std::string> pv = f->getPV();

  std::vector<double> inputVec;
  for(double i = 0; i < numTrials; ++i){
    inputVec = randVector(lowBounds, highBounds);
    resultSum += f->evaluate(pv,inputVec);    
  }

  double resultAvg = resultSum/numTrials;
  double result = resultAvg*getTargetArea(lowBounds,highBounds);  

  return result;
}

#endif
