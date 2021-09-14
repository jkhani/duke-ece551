#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  return pow((((x-p.x)*(x-p.x))+((y-p.y)*(y-p.y))),.5);
}
