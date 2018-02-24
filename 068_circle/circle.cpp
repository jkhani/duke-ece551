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
  
  if (dist > (radius+R)){
    return 0;
  }

  if ((dist < abs(radius - R)) || (dist == 0)){
    if (R > radius){
      R = radius;
    }
    return R*R*3.1415926535897;
  }
  
  double area1 = radius*radius*acos(((dist*dist)+(radius*radius)-(R*R))/(2*dist*radius));
  printf("area1 = %g ",area1);
  double area2 = R*R*acos(((dist*dist)+(R*R)-(radius*radius))/(2*dist*R));
  printf("area2 = %g ",area2);
  double area3 = pow(((-dist+radius+R)*(dist+radius-R)*(dist-radius+R)*(dist+radius+R)),.5);
  printf("area3 = %g\n",area3);

  return area1+area2-((1/2)*area3);
}
