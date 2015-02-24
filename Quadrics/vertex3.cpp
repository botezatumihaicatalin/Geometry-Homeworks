/*
 * vertex3.cpp
 *
 *  Created on: 24 feb. 2015
 *      Author: Botezatu
 */
#include "vertex3.h"
#include "math.h"

Vertex3 Vertex3::Cross(const Vertex3 & u , const Vertex3 & v) {
	Vertex3 result;
	result.x = u.y * v.z - u.z * v.y;
	result.y = u.z * v.x - v.z * u.x;
	result.z = u.x * v.y - u.y * v.x;
	return result;
}

Vertex3 Vertex3::Normalize(const Vertex3 & u) {
	Vertex3 result;
	double length = sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
	result.x = u.x / length;
	result.y = u.y / length;
	result.z = u.z / length;
	return result;
}

double Vertex3::Dot(const Vertex3 & u , const Vertex3 & v) {
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vertex3 operator -(const Vertex3 & u , const Vertex3 & v) {
	Vertex3 result;
	result.x = u.x - v.x;
	result.y = u.y - v.y;
	result.z = u.z - v.z;
	return result;
}

Vertex3 operator +(const Vertex3 & u , const Vertex3 & v) {
	Vertex3 result;
	result.x = u.x + v.x;
	result.y = u.y + v.y;
	result.z = u.z + v.z;
	return result;
}



