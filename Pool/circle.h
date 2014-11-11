/*
 * circle.h
 *
 *  Created on: Nov 11, 2014
 *      Author: mihai
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "point2D.h"

class Circle {
public:
	Point2D Center;
	double Radius;
	Circle(const double & x = 0.0 , const double & y = 0.0, const double & radius = 0.0) {
		Center.X = x;
		Center.Y = y;
		Radius = radius;
	}
	Circle(const Point2D & centerPoint , const double & radius = 0.0) {
		Center = centerPoint;
		Radius = radius;
	}
};

#endif /* CIRCLE_H_ */
