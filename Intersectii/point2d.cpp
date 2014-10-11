#include "point2d.h"

bool Point2D::operator <(const Point2D & other) const
{
	return (this->X < other.X || (this -> X == other.X && this->Y < other.Y));
}

bool Point2D::operator ==(const Point2D & other) const
{
	return (this->X == other.X && this->Y == other.Y);
}
