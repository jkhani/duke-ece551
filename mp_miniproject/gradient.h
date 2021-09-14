#ifndef __GRADIENT_H__
#define __GRADIENT_H__
#include "function.h"
#include "expr.h"
#include "common.h"

/*
weightGradient multiples the gradient of pcurr by gamma to get the weigthed vector
pointing in the direction with the greatest slope.
*/
std::vector<double> weightGradient(std::vector<double> gradient, double gamma){
  std::vector<double> step;
  for(size_t i = 0; i < gradient.size(); ++i){
    step.push_back(gradient[i]*gamma);
  }

  return step;
}

/*
partialDerivative computes the derivative for a given dimension for the Function f.
(adapted from AOP 10.10)
*/
double partialDerivative(Function *f, std::vector<double> &points, size_t dim){
  std::vector<std::string> pv = f->getPV();
  double h = 0.0000000000001;
  std::vector<double> input = points;
  input[dim] += h;
  double f_xh = f->evaluate(pv, input);
  double f_x = f->evaluate(pv, points);

  double derivative = (f_xh-f_x)/h;

  return derivative;
}

/*
getGradient computes the gradient at a given point (pcurr) for Function f. That is
the direction of graph with the greatest magnitude for the slope.
*/
std::vector<double> getGradient(Function * f, std::vector<double> &pcurr){
  std::vector<double> gradient;
  double derivative;
  for(size_t i = 0; i < pcurr.size(); ++i){
    derivative = partialDerivative(f, pcurr, i);
    gradient.push_back(derivative);
  }

  return gradient;
}

/*
getDist calculates the Euclidean distance between two vectors. In this case, we are 
interested in (pnew - pcurr) which is equal to gamma*gradient(pcurr).
*/
double getDist(std::vector<double> &weightedGradient){
  double distance = 0;
  for(size_t i = 0; i < weightedGradient.size(); ++i){
    distance += pow(weightedGradient[i],2);
  }
  distance = sqrt(distance);

  return distance;
}

/*
getPNew returns the new positing in the graph (pnew). Step is the weighted gradient
which is the magnitude of the direction of the step. For gradient descent, the step
vector has been multiplied by -1 so adding still works.
*/
std::vector<double> getPNew(std::vector<double> &pcurr, std::vector<double> &step){
  std::vector<double> pnew;
  for(size_t i = 0; i < pcurr.size(); ++i){
    pnew.push_back(pcurr[i]+step[i]);
  }

  return pnew;
}

/*
ascent finds the max value for the Function f using gradient ascent.
*/
double ascent(Function * f, double gamma, double converge, std::vector<double> & pcurr, double steps){
  std::vector<std::string> pv = f->getPV();
  std::vector<double> gradient = getGradient(f,pcurr);
  std::vector<double> slope = weightGradient(gradient, gamma);
  std::vector<double> pnew;

  double stepsTaken = 0;
  while(getDist(slope) > converge){
    pnew = getPNew(pcurr, slope);
    pcurr = pnew;

    gradient = getGradient(f,pcurr);
    slope = weightGradient(gradient, gamma);
    ++stepsTaken;
    if(stepsTaken > steps){
      std::cout << f->getFName() << " failed to converge..\n";
      break;
    }    
  }
  
  double max = f->evaluate(pv, pnew);
  return max;
}

/*
descent finds the min value for the Function f using gradient descent.
*/
double descent(Function * f, double gamma, double converge, std::vector<double> & pcurr, double steps){
  std::vector<std::string> pv = f->getPV();
  std::vector<double> gradient = getGradient(f,pcurr);
  // multiplying gamme by -1 so no need for a specific function for subtracting, won't affect distance measure
  std::vector<double> slope = weightGradient(gradient, (-1*gamma));
  std::vector<double> pnew;

  double stepsTaken = 0;
  while(getDist(slope) > converge){
    pnew = getPNew(pcurr, slope);
    pcurr = pnew;

    gradient = getGradient(f,pcurr);
    slope = weightGradient(gradient, (-1*gamma));
    ++stepsTaken;
    if(stepsTaken > steps){
      std::cout << f->getFName() << " failed to converge..\n";
      break;
    }    
  }
  
  double min = f->evaluate(pv, pnew);
  return min;
}

#endif
