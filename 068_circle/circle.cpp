#include "circle.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Circle::move(double dx, double dy){
  center.move(dx,dy);
}

double Circle::intersectionArea(const Circle & otherCircle){
  double R = otherCircle.radius;
  double dist = center.distanceFrom(otherCircle.center);
  double area1 = radius*radius*acos(((dist*dist)+(radius*radius)-(R*R))/(2*dist*radius));
  double area2 = R*R*acos(((dist*dist)+(R*R)-(radius*radius))/(2*dist*R));
  double area3 = pow(((-dist+radius+R)*(dist+radius-R)*(dist-radius+R)*(dist+radius+R)),.5);

  return area1+area2-((1/2)*area3);
}
