#include "point2d.h"

#ifndef SOURCES_SEGMENT_H_
#define SOURCES_SEGMENT_H_

class Segment {
public :
	Point2D LeftPoint;
	Point2D RightPoint;
	Segment(const Point2D & leftPoint, const Point2D & rightPoint) : LeftPoint(leftPoint), RightPoint(rightPoint) {}
	bool Intersects(const Segment & otherSegment) const;
	Point2D IntersectionPoint(const Segment & otherSegment) const;
	float PointOnSegment(const Point2D & point) const;
};


#endif /* SOURCES_SEGMENT_H_ */
