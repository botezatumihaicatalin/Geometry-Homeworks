#include "segment.h"

double Segment::PointOnSegment(const Point2D & point) const {
	double deltaX = LeftPoint.X - RightPoint.X;
	double deltaY = LeftPoint.Y - RightPoint.Y;
	return (-1 * point.X * deltaY + point.Y * deltaX + LeftPoint.X * deltaY - LeftPoint.Y * deltaX);
}

bool Segment::Intersects(const Segment & otherSegment) const {
	double leftPositionCurrent = this->PointOnSegment(otherSegment.LeftPoint);
	double rightPositionCurrent = this->PointOnSegment(otherSegment.RightPoint);
	double leftPositionOther = otherSegment.PointOnSegment(LeftPoint);
	double rightPositionOther = otherSegment.PointOnSegment(RightPoint);
	return (leftPositionCurrent * rightPositionCurrent <= 0 && leftPositionOther * rightPositionOther < 0) || (leftPositionCurrent * rightPositionCurrent < 0 && leftPositionOther * rightPositionOther <= 0);
}

Point2D Segment::IntersectionPoint(const Segment & otherSegment) const {
	// AB = this
	// CD = otherSegment
	//     (yc - ya)(xb - xa) - (xc - xa)(yb - ya)
	// q = --------------------------------------
	//	   (xd - xc)(yb - ya) - (yd - yc)(xb - xa)

	double deltaX = LeftPoint.X - RightPoint.X;
	double deltaY = LeftPoint.Y - RightPoint.Y;
	double topRatio = (otherSegment.LeftPoint.X - this->LeftPoint.X) * deltaY - (otherSegment.LeftPoint.Y - this->LeftPoint.Y) * deltaX;
	double bottomRatio = (otherSegment.RightPoint.Y - otherSegment.LeftPoint.Y) * deltaX - (otherSegment.RightPoint.X - otherSegment.LeftPoint.X) * deltaY;

	// P = (1 - q) * C + q * D

	double intersectionX = (otherSegment.LeftPoint.X * (bottomRatio - topRatio) + otherSegment.RightPoint.X * topRatio) / bottomRatio;
	double intersectionY = (otherSegment.LeftPoint.Y * (bottomRatio - topRatio) + otherSegment.RightPoint.Y * topRatio) / bottomRatio;

	return Point2D(intersectionX, intersectionY);
}

Vertex2 Segment::GetLeftNormal() const {
    Vertex2 normal(this->LeftPoint, this->RightPoint);
    return Vertex2(-1 * normal.Y , normal.X);
}

Vertex2 Segment::GetRightNormal() const {
    Vertex2 normal(this->LeftPoint, this->RightPoint);
    return Vertex2(normal.Y, -1 * normal.X);
}
