/*
 * vector2D.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: mihai
 */

#include "vector2D.h"
#include "math.h"

double Vector2D::CrossProduct(const Vector2D & other) const {
    return (this->XVect * other.YVect - this->YVect * other.XVect);
}

double Vector2D::DotProduct(const Vector2D & other) const {
    return (this->XVect * other.XVect + this->YVect * other.YVect);
}

Vector2D operator+(const Vector2D & v1, const Vector2D & v2) {
    return Vector2D(v1.XVect + v2.XVect, v1.YVect + v2.YVect);
}

Vector2D operator-(const Vector2D & v1, const Vector2D & v2) {
    return Vector2D(v1.XVect - v2.XVect, v1.YVect - v2.YVect);
}

Vector2D operator*(const Vector2D & v1 , const double & scalar) {
    return Vector2D(v1.XVect * scalar , v1.YVect * scalar);
}

Vector2D operator*(const double & scalar , const Vector2D & v1) {
    return v1 * scalar;
}

void Vector2D::operator+=(const Vector2D & other) {
    this->XVect += other.XVect;
    this->YVect += other.YVect;
}

void Vector2D::operator-=(const Vector2D & other) {
    this->XVect -= other.XVect;
    this->YVect -= other.YVect;
}

void Vector2D::operator *=(const double & scalar) {
    this->XVect *= scalar;
    this->YVect *= scalar;
}

double Vector2D::Length() const {
    double squareX = this->XVect * this->XVect;
    double squareY = this->YVect * this->YVect;
    return sqrt(squareX + squareY);
}

Vector2D Vector2D::Normalize() const {
    double length = this->Length();
    return Vector2D(this->XVect / length, this->YVect / length);
}
