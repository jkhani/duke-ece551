#include "circle.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Circle::move(double dx, double dy){
  center.move(dx,dy);
}

double Circle::intersectionArea(const Circle & otherCircle){
  double R = otherCircle.radius;
  double r = radius;
  double d = center.distanceFrom(otherCircle.center);
  
  if (d >= (r+R)){
    return 0;
  }

  if (d <= abs(r-R)){
    if (R > r){
      R = r;
    }
    return R*R*3.1415926535;
  }

  double a = r*r;
  double b = R*R;

  double x = (a - b + (d*d))/(2*d);
  double z = x*x;
  double y = sqrt(a - z);

  return a*atan2(y,x) + b *atan2(y,(d-x)) - d*y;
}
