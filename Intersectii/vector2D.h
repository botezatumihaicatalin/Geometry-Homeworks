#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "point2D.h"

class Vector2D {
public:
	double X, Y;
	Vector2D(const double & xVect , const double & yVect) : X(xVect) , Y(yVect) {};
	Vector2D(const Point2D & point) : Vector2D(point.X , point.Y) {};
	Vector2D(const Point2D & point1 , const Point2D & point2) : X(point2.X - point1.X) , Y(point2.Y - point1.Y) {};
	double CrossProduct(const Vector2D & other) const;
};

#endif /* VECTOR2D_H */
