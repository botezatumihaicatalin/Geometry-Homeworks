#include "point2D.h"

#include <math.h>

bool Point2D::operator <(const Point2D & other) const {
	return (this->X < other.X || (this->X == other.X && this->Y < other.Y));
}

bool Point2D::operator ==(const Point2D & other) const {
	return (this->X == other.X && this->Y == other.Y);
}

bool Point2D::operator >(const Point2D & other) const {
	return !(*this < other);
}

bool Point2D::operator <=(const Point2D & other) const {
	return (*this < other) || (*this == other);
}

bool Point2D::operator >=(const Point2D & other) const {
	return (!(*this < other)) || (*this == other);
}

bool Point2D::operator !=(const Point2D & other) const {
	return !(*this == other);
}

double Point2D::Distance(const Point2D & other) const {
	double deltaX = this->X - other.X;
	double deltaY = this->Y - other.Y;
	return sqrt(deltaX * deltaX + deltaY * deltaY);
}
