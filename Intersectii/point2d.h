class Point2D {

public :
	Point2D(const float & x = 0.0, const float & y = 0.0) :
		X(x), Y(y) {}
	float X;
	float Y;
	bool operator==(const Point2D & other) const;
	bool operator<(const Point2D & other) const;
	bool operator>(const Point2D & other) const;
	bool operator<=(const Point2D & other) const;
	bool operator>=(const Point2D & other) const;
	bool operator!=(const Point2D & other) const;

};
