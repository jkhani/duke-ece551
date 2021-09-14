class Point{
 private:
  double x;
  double y;
 public:
  Point() : x(0), y(0) {
  }
  Point(double x_int, double y_int) {
    x = x_int;
    y = y_int;
  }
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
};
