/*
 * vector3D.h
 *
 *  Created on: Dec 27, 2014
 *      Author: mihai
 */

#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vertex3 {
public:
	double X, Y, Z;
	Vertex3(const double & x = 0.0, const double & y = 0.0, const double & z =
			0.0) :
			X(x), Y(y), Z(z) {
	}
	Vertex3(const Vertex3 & pointLeft, const Vertex3 & pointRight) :
			X(pointRight.X - pointLeft.X), Y(pointRight.Y - pointLeft.Y), Z(
					pointRight.Z - pointLeft.Z) {

	}
	Vertex3 Normalize();
	double Length();
};

#endif /* VECTOR3D_H */
