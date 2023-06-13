#include <cmath>

#ifndef VEC2
#define VEC2

class Vec2 {

public:
   Vec2():x(0), y(0){}
   Vec2(double x, double y):x(x), y(y){}

   Vec2 operator+ (const Vec2 &other) const {return Vec2(x + other.x, y + other.y);}
   Vec2 operator- (const Vec2 &other) const {return Vec2(x - other.x, y - other.y);}
   Vec2 operator+= (const Vec2 &other)  {x += other.x; y += other.y;return *this;}
   Vec2 operator* (double c){return Vec2(c * x, c * y);}
   Vec2 operator/ ( double c){return Vec2(x / c, y / c);}

   Vec2 rotate(double angle) const {return Vec2(x * cos(angle) + y * sin(angle), - x * sin(angle) + y * cos(angle));}
   
   bool operator==(const Vec2& other) const {return (x == other.x) && (y == other.y);}
   
   double length() const {return sqrt(x * x + y * y);}
   Vec2 normalize(){return Vec2(x / length(), y / length());}

   double x;
   double y;
};

#endif
