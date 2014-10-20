#include "segment.h"

float Segment::PointOnSegment(const Point2D & point) const
{
	float deltaX = LeftPoint.X - RightPoint.X;
	float deltaY = LeftPoint.Y - RightPoint.Y;
	return (-1 * point.X * deltaY + point.Y * deltaX + LeftPoint.X * deltaY - LeftPoint.Y * deltaX);
}

bool Segment::Intersects(const Segment & otherSegment) const
{
	float leftPositionCurrent = this->PointOnSegment(otherSegment.LeftPoint);
	float rightPositionCurrent = this->PointOnSegment(otherSegment.RightPoint);
	float leftPositionOther = otherSegment.PointOnSegment(LeftPoint);
	float rightPositionOther = otherSegment.PointOnSegment(RightPoint);
	return (leftPositionCurrent * rightPositionCurrent <= 0 && leftPositionOther * rightPositionOther < 0) ||
		   (leftPositionCurrent * rightPositionCurrent < 0 && leftPositionOther * rightPositionOther <= 0);
}

Point2D Segment::IntersectionPoint(const Segment & otherSegment) const
{
	// AB = this
	// CD = otherSegment
	//     (yc - ya)(xb - xa) - (xc - xa)(yb - ya)
	// q = --------------------------------------
	//	   (xd - xc)(yb - ya) - (yd - yc)(xb - xa)

	float deltaX = LeftPoint.X - RightPoint.X;
	float deltaY = LeftPoint.Y - RightPoint.Y;
	float topRatio = (otherSegment.LeftPoint.X - this->LeftPoint.X) * deltaY - (otherSegment.LeftPoint.Y - this->LeftPoint.Y) * deltaX;
	float bottomRatio = (otherSegment.RightPoint.Y - otherSegment.LeftPoint.Y) * deltaX - (otherSegment.RightPoint.X - otherSegment.LeftPoint.X) * deltaY;

	// P = (1 - q) * C + q * D

	float intersectionX = (otherSegment.LeftPoint.X  * (bottomRatio - topRatio) + otherSegment.RightPoint.X * topRatio) / bottomRatio;
	float intersectionY = (otherSegment.LeftPoint.Y  * (bottomRatio - topRatio) + otherSegment.RightPoint.Y * topRatio) / bottomRatio;

	return Point2D(intersectionX , intersectionY);
}
