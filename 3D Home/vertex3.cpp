#include "vertex3.h"
#include "math.h"

Vertex3 Vertex3::Normalize() {
	double length = Length();
	return Vertex3(X / length , Y / length , Z / length);
}

double Vertex3::Length() {
	return sqrt(X * X + Y * Y + Z * Z);
}
