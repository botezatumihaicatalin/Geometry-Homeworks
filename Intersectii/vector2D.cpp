/*
 * vector2D.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: mihai
 */

#include "vector2D.h"

float Vector2D::CrossProduct(const Vector2D & other) const
{
	return (this->XVect * other.YVect - this->YVect * other.XVect);
}
