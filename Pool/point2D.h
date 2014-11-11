#ifndef POINT2D_H
#define POINT2D_H

class Point2D {

public:
	Point2D(const double & x = 0.0, const double & y = 0.0) :
			X(x), Y(y) {
	}
	double X;
	double Y;
	bool operator==(const Point2D & other) const;
	bool operator<(const Point2D & other) const;
	bool operator>(const Point2D & other) const;
	bool operator<=(const Point2D & other) const;
	bool operator>=(const Point2D & other) const;
	bool operator!=(const Point2D & other) const;
	double Distance(const Point2D & other) const;

};

#endif
