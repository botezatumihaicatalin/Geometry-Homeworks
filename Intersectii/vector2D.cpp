/*
 * vector2D.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: mihai
 */

#include "vector2D.h"

bool Vector2D::IsLeftTurn(const Vector2D & other) const
{
	return (this->XVect * other.YVect - this->YVect * other.XVect) < 0.0f;
}
