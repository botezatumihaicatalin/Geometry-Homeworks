#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "point2D.h"

class Vertex2 {
public:
	double X, Y;
	Vertex2(const double & xVect , const double & yVect) : X(xVect) , Y(yVect) {};
	Vertex2(const Point2D & point) : Vertex2(point.X , point.Y) {};
	Vertex2(const Point2D & point1 , const Point2D & point2) : X(point2.X - point1.X) , Y(point2.Y - point1.Y) {};

	friend Vertex2 operator+(const Vertex2 & v1 , const Vertex2 & v2);
	friend Vertex2 operator-(const Vertex2 & v1 , const Vertex2 & v2);
	friend Vertex2 operator*(const Vertex2 & v1 , const double & scalar);
    friend Vertex2 operator*(const double & scalar , const Vertex2 & v1);
    friend Vertex2 operator/(const Vertex2 & v1 , const double & scalar);

	void operator+=(const Vertex2 & other);
	void operator-=(const Vertex2 & other);
	void operator*=(const double & scalar);
	void operator/=(const double & scalar);

	double Length() const;
	Vertex2 Normalize() const;
	double CrossProduct(const Vertex2 & other) const;
	double DotProduct(const Vertex2 & other) const;
};

#endif /* VECTOR2D_H */
