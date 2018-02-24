#include "point.h"

class Circle{
 private:
  Point center;
  const double radius;

 public:
  Circle() : center(), radius(0){}
 Circle(Point c, const double r) : center(c), radius(r) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
