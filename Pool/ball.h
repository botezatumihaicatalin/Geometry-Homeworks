#ifndef BALL_H
#define BALL_H

#include "circle.h"

class Ball: public Circle {
public:
	Vector2D Direction;
	Ball(const Vector2D & direction , const double & x , const double & y , const double & radius) : Direction(direction) , Circle(x , y , radius) {}
	Ball(const Vector2D & direction , const Point2D & center , const double & radius) : Direction(direction) , Circle(center , radius) {}
};

#endif
